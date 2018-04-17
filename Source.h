#ifndef TKOM_SOURCE_H
#define TKOM_SOURCE_H

#include <iostream>
#include <fstream>

class Source {
private:
	std::string fileName;
	std::fstream file;

	int characterPosition;
	int linePosition;
	std::string lineBuffer;
	int nErrors;
	int tokenBegin;
	std::string strToRed(const std::string &str);
	std::string strToWhite(const std::string &str);


public:
	explicit Source(const std::string &fileName);
	~Source();
	void raiseError(const std::string &errorDesc,
			int begIndex, int midIndex, int endIndex);
	int nextChar();
	void setTokenBegin();
	int getNErrors();
	void printLine();
	int getIndex();
};


#endif //TKOM_SOURCE_H
