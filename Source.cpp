#include "Source.h"
#include <exception>
#include <iomanip>


void Source::raiseError(std::string errorDesc) {
	nErrors++;

	std::cout << fileName <<": " << linePosition <<": " << characterPosition << ": error: " << errorDesc << std::endl;
	std::cout << lineBuffer << std::endl;
	for (int i = 0; i < tokenBegin; i++)
		std::cout << " ";

	for (int i = tokenBegin; i < characterPosition; i++)
		std::cout << "~";

	std::cout << "^" << std::endl;
}

int Source::nextChar() {
	bool isEnd;

	characterPosition++;
	// read a line to the buffer if necessary
	if (characterPosition >= lineBuffer.size()) {
		std::string temp;

		if (!std::getline(file, temp)) {
			return EOF;
		} else {
			// new line successfuly read
			lineBuffer = temp;
			linePosition = 0;
			tokenBegin = 0;
			characterPosition = -1;
			lineErrors = 0;

			return '\n';
		}
	}

	return lineBuffer[characterPosition];
}

Source::Source(std::string nFileName) {
	fileName = nFileName;
	nErrors = 0;
	lineErrors = 0;
	characterPosition = 0;
	linePosition = 0;
	lineBuffer = "";
	tokenBegin = 0;
	file.open(fileName, std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("Can't open file: " + fileName);
}

Source::~Source() {
	if (file.is_open())
		file.close();
}

void Source::setTokenBegin() {
	tokenBegin = characterPosition;
}
