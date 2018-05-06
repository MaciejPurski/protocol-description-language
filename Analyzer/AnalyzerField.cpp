#include <iostream>
#include "AnalyzerField.h"
#include <iomanip>

void AnalyzerField::show() {
	std::cout << name << "(";

	switch (type) {
		case BYTES_TYPE:
			for (auto b : bytes) {
				std::ios_base::fmtflags f( std::cout.flags() );

				std::cout << std::hex << std::showbase // show the 0x prefix
				                      << std::internal // fill between the prefix and the number
				                      << std::setfill('0') // fill with 0s
									  << (unsigned int) b << " ";
				std::cout.flags(f);
			}
			break;
		case STRING_TYPE:
			std::cout << strValue;
			break;
		case INT_TYPE:
			std::cout << intVal;
			break;
		case UINT_TYPE:
			std::cout << uintVal;
			break;
	}

	std::cout << ") ";
}
