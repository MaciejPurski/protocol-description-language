#include "PacketsParser.h"

PacketsParser::PacketsParser(const char *fileName) {
	file.open(fileName, std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("Can't open file: " + std::string(fileName));

}

void PacketsParser::parsePackets(std::unordered_map<uint64_t, std::shared_ptr<Packet>> &pidMap,
                                 unsigned int pidOffset, unsigned int pidLength) {
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
		std::vector<std::shared_ptr<Field>> &fields = it->second->fields;

		for (unsigned int i = 1; i < fields.size(); i++) {
			std::vector<char> fieldBuf;
			unsigned int fieldLength = it->second->evaluateFieldLength(fields[i]);

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



