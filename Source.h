#ifndef TKOM_SOURCE_H
#define TKOM_SOURCE_H

#include <iostream>
#include <fstream>
#include "Token.h"

class Source {
private:
	std::string fileName;
	std::fstream file;
	bool testMode;

	unsigned int characterPosition;
	unsigned int linePosition;
	std::string lineBuffer;
	int nErrors;
	std::string strToRed(const std::string &str);
	std::string strToWhite(const std::string &str);


public:
	explicit Source(const std::string &fileName, bool testMode);
	~Source();
	void raiseError(const std::string &errorDesc, Token &token);
	int nextChar();
	int getNErrors();
	void printLine();
	int getIndex();
};


#endif //TKOM_SOURCE_H
