#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_ANALYZERFIELD_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_ANALYZERFIELD_H

#include "../Token.h"
#include <string>
#include <vector>

class AnalyzerField {
public:
	TokenType type;
	unsigned int length;
	std::string name;

	std::string strValue;
	uint64_t uintVal;
	int64_t intVal;
	std::vector<char> bytes;

	AnalyzerField(std::string nname, TokenType nType, unsigned int nLength) : name(nname), type(nType), length(nLength) {

	}

	void show();

	std::string toStr() const;

	uint64_t getUintVal() {
		return uintVal;
	}

};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_ANALYZERFIELD_H
