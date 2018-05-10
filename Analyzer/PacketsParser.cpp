#include "PacketsParser.h"

void PacketsParser::parsePackets() {
	int c;

	while ((c = file.get()) != EOF) {
		std::vector<char> buf;
		std::vector<AnalyzerField> parsedFields;

		file.unget();
		getBytes(buf, pidOffset);

		// now read pid
		getBytes(buf, pidLength);

		uint64_t pid = parseUInt(buf.data() + pidOffset, pidLength);

		auto it = pidMap.find(pid);

		if (it == pidMap.end()) {
			std::cout << "Unknown packet encountered\n";
			return;
		}

		parsedFields.push_back(AnalyzerField("pid", UINT_TYPE, pidLength));
		parsedFields.back().uintVal = pid;

		// TODO: parse fields before pid

		// parse fields

		unsigned int currentOffset = pidOffset + pidLength;
		std::vector<std::unique_ptr<Field>> &fields = it->second->fields;

		for (unsigned int i = 1; i < fields.size(); i++) {
			std::vector<char> fieldBuf;
			unsigned int fieldLength = evaluateFieldLength(parsedFields, fields[i]);

			// add a new field
			parsedFields.push_back(AnalyzerField(fields[i]->name,
			                                     fields[i]->type->type,
			                                     fieldLength));

			// parse field
			getBytes(fieldBuf, fieldLength);

			switch (fields[i]->type->type) {
				case BYTES_TYPE:
					parsedFields.back().bytes = fieldBuf;
					break;
				case STRING_TYPE:
					parsedFields.back().strValue = std::string(fieldBuf.data());
					break;
				case INT_TYPE:
					parsedFields.back().intVal = parseInt(fieldBuf.data(), fieldBuf.size());
					break;
				case UINT_TYPE:
					parsedFields.back().uintVal = parseUInt(fieldBuf.data(), fieldBuf.size());
					break;
			}
		}

		packets.emplace_back(AnalyzerPacket(it->second->name, parsedFields));
	}

}

uint64_t PacketsParser::parseUInt(char *buf, unsigned int size) {
	uint64_t result = 0;

	for (int i = 0; i < size; i++) {
		result += (unsigned char) buf[i] << 8 * i;
	}

	return result;
}

int64_t PacketsParser::parseInt(char *buf, unsigned int size) {
	uint64_t result = 0;

	for (int i = 0; i < size; i++) {
		result += (unsigned char) buf[i] << 8 * i;
	}

	return result;
}

std::string PacketsParser::parseString(char *buf, unsigned int size) {
	return std::string(buf);
}

void PacketsParser::getBytes(std::vector<char> &buf, unsigned int n) {
	int c;

	std::cout << "getBytes: " << n << std::endl;

	for (unsigned int i = 0; i < n; i++) {
		c = file.get();

		if (c == EOF) {
			throw std::runtime_error("Unexpected end of buffer");
		}
		buf.push_back(c);
	}

}

void PacketsParser::showPacket() {
	for (auto p : packets)
		p.show();
}

unsigned int PacketsParser::evaluateFieldLength(std::vector<AnalyzerField> &fields, std::unique_ptr<Field> &field) {
	unsigned int result = 0;
	Number *n;
	Identifier *i;

	OperandType t = field->type->length->first->getType();

	switch (t) {
		case NUMBER:
			n = static_cast<Number*>(field->type->length->first.get());
			result += n->value;
			break;
		case IDENT:
			i = static_cast<Identifier*>(field->type->length->first.get());

			// look for a dependent field
			for (auto f : fields) {
				// found
				if (f.name == i->str) {
					if (f.type == UINT_TYPE)
						result += f.uintVal;
					else
						result += f.intVal;
				}
			}
			break;
	}

	for (auto &op : field->type->length->rest) {
		t = op.second->getType();
		unsigned int val;

		switch (t) {
			case NUMBER:
				n = static_cast<Number*>(op.second.get());
				val = n->value;
				break;
			case IDENT:
				i = static_cast<Identifier*>(op.second.get());
				for (auto &f : fields) {
					// found
					if (f.name == i->str) {
						val = f.length;
					}
				}
				break;
		}

		switch (op.first) {
			case ADD_OPERATOR:
				result += val;
				break;
			case MUL_OPERATOR:
				result *= val;
				break;
			case SUBTR_OPERATOR:
				result -= val;
				break;
		}
	}

	return result;
}

PacketsParser::PacketsParser(const char *fileName,
                             std::unordered_map<uint64_t, std::unique_ptr<Packet>> pidMap,
                             unsigned int pidOffset, unsigned int pidLength) : pidMap(std::move(pidMap)),
                                                                               pidOffset(pidOffset),
                                                                               pidLength(pidLength) {
	file.open(fileName, std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("Can't open file: " + std::string(fileName));
}



