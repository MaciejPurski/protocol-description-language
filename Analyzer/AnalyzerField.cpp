#include <iostream>
#include "AnalyzerField.h"
#include <iomanip>

void AnalyzerField::show() {
	std::cout << toStr();
}

std::string AnalyzerField::toStr() const {
	std::stringstream s;

	s << name << "(";

	switch (type) {
		case BYTES_TYPE:
			for (auto b : bytes) {
				s << std::hex << std::showbase // show the 0x prefix
				          << std::internal // fill between the prefix and the number
				          << std::setfill('0') // fill with 0s
				          << (unsigned int) b << " ";
			}
			break;
		case STRING_TYPE:
			s << strValue;
			break;
		case INT_TYPE:
			s << intVal;
			break;
		case UINT_TYPE:
			s << uintVal;
			break;
	}

	s << ") ";

	return s.str();
}
