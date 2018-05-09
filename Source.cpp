#include "Source.h"
#include "Token.h"
#include <exception>
#include <iomanip>

void Source::printLine() {
	std::cout << lineBuffer << std::endl << std::endl;
}

int Source::getIndex() {
	return characterPosition;
}

void Source::raiseError(const std::string &errorDesc, Token &token) {
	nErrors++;

	std::cerr << std::endl;

	std::cerr << strToWhite(fileName + ":" + std::to_string(linePosition) + ":" + std::to_string(characterPosition) + ": ")
	          << strToRed("error: ") << errorDesc << std::endl;

	std::cerr << lineBuffer.substr(0, token.position - 1) << strToRed(lineBuffer.substr(token.position - 1, token.length))
	<< lineBuffer.substr(token.position - 1 + token.length) << std::endl;

	for (int i = 0; i < token.position - 1; i++) {
		if (lineBuffer[i] == '\t')
			std::cerr << "\t";
		else
			std::cerr << " ";
	}


	std::string underline;

	underline += '^';

	for (int i = 0; i < token.length -1; i++)
		underline += '~';

	std::cerr << strToRed(underline) << std::endl;

}

int Source::nextChar() {
	// read a line to the buffer if necessary
	if (characterPosition >= lineBuffer.size()) {

		if (!std::getline(file, lineBuffer)) {
			return EOF;
		} else {
			// new line successfuly read
			lineBuffer += '\n';
			linePosition++;
			characterPosition = 0;
			if (testMode)
				printLine();
		}
	}

	return lineBuffer[characterPosition++];
}

Source::Source(const std::string &nFileName, bool testMode = false) {
	this->testMode = testMode;
	fileName = nFileName;
	nErrors = 0;
	characterPosition = 0;
	linePosition = 0;
	lineBuffer = "";

	file.open(fileName, std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("Can't open file: " + fileName);
}

Source::~Source() {
	if (file.is_open())
		file.close();
}

int Source::getNErrors() {
	return nErrors;
}
