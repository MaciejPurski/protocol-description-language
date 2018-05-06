#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_ANALYZERPACKET_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_ANALYZERPACKET_H


#include <vector>
#include "../Nodes/Packet.h"
#include "AnalyzerField.h"

class AnalyzerPacket {
public:
	std::string name;
	std::vector<AnalyzerField> fields;

	AnalyzerPacket(std::string nname, std::vector<AnalyzerField> &nfields) {
		name = nname;
		fields = nfields;
	}


	void show() {
		int offset = 0;
		std::cout << "PACKET name(" << name <<") ";
		for (auto f : fields)
			f.show();

		std::cout << std::endl;
	}

};


#endif
