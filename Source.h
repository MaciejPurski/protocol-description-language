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

public:
	explicit Source(const std::string &fileName);
	~Source();
	void raiseError(const std::string &errorDesc);
	int nextChar();
	void setTokenBegin();
};


#endif //TKOM_SOURCE_H
