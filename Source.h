#ifndef TKOM_SOURCE_H
#define TKOM_SOURCE_H

#include <iostream>
#include <fstream>
#include "Token.h"
#include "Utils.h"

class Source {
private:
	std::string fileName;
	std::fstream file;
	bool testMode;
	int prevChar;

	unsigned int characterPosition;
	unsigned int linePosition;
	unsigned int filePosition;
	int nErrors;

public:
	explicit Source(const std::string &fileName, bool testMode);
	~Source();
	void raiseError(const std::string &errorDesc, Token &token);
	int nextChar();
	int getNErrors();
	void printLine();
	int getIndex();

	unsigned int getPosition();

	unsigned int getLineNumber();

	unsigned int getColumn();
};


#endif //TKOM_SOURCE_H
