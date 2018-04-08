//
// Created by maciej on 26.03.18.
//

#include "Field.h"

std::string Field::toString(unsigned char *buffer) {
	std::stringstream ss;
	ss << name << ": ";
	switch (format) {
		case HEX:
			ss << std::hex << std::setfill('0');
			for (int i = 0; i < length; i++) {
				ss << std::setw(2) << buffer[i + offset];
			}
			break;
		case STRING:
			int i;

			for (i = 0; i < length; i++) {
				if (buffer[i + offset] == '\0')
					break;
			}

			if (i == length)
				throw std::invalid_argument("String is not null-terminated");

			ss << buffer;
			break;
		case DECIMAL:
			/*if (length == 1) {
				int8_t val = reinterpret_cast<int8_t>(*buffer);
				ss << val;
			} else if (length == 2) {
				int16_t val = *(reinterpret_cast<int16_t *> (buffer));
				ss << val;
			} else if (length == 4) {
				int32_t val = *(reinterpret_cast<int32_t *> (buffer));
				ss << val;
			} else if (length == 8) {
				int64_t val = *(reinterpret_cast<int64_t *> (buffer));
				ss << val;
			} else {
				throw std::invalid_argument("Wrong decimal number length");
			}*/
			break;
		case FLOAT:
			if (length != 4)
				throw std::invalid_argument("Wrong float length");

			float val = *(reinterpret_cast<float *> (buffer));

			ss << val;
			break;
	}

	return ss.str();
}