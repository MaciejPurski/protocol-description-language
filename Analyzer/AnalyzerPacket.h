#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_ANALYZERPACKET_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_ANALYZERPACKET_H

#include "AnalyzerField.h"
#include <vector>
#include <iostream>
#include <algorithm>

class AnalyzerPacket {
public:
	std::string name;
	std::vector<AnalyzerField> fields;

	AnalyzerPacket(std::string nname, std::vector<AnalyzerField> &nfields) {
		name = nname;
		fields = nfields;
	}

	std::string toStr() const {
		std::string str;

		str = name + ": ";
		for (auto f : fields)
			str += f.toStr();

		return str;
	}


	void show() {
		std::cout << "PACKET: " << toStr();

		std::cout << std::endl;
	}


};


#endif
