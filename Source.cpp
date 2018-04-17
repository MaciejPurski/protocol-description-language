#include "Source.h"
#include <exception>
#include <iomanip>

std::string Source::strToRed(const std::string &str) {
	return  std::string("\033[1;31m" + str + "\033[0m");
}

std::string Source::strToWhite(const std::string &str) {
	return  std::string("\033[1;37m" + str + "\033[0m");
}

void Source::raiseError(const std::string &token,
			const std::string &errorDesc) {
	nErrors++;

	std::cout << "TOKEN: " << token << std::endl;
	std::cout << std::endl;
	std::cout << strToWhite(fileName + ":" + std::to_string(linePosition + 1) + ":" + std::to_string(characterPosition + 1) + ": ")
	          << strToRed("error: ") << errorDesc << std::endl;
	std::cout << lineBuffer.substr(0, tokenBegin) << strToRed(token)
	<< lineBuffer.substr(tokenBegin + token.size()) << std::endl;
	for (int i = 0; i < tokenBegin; i++)
		std::cout << " ";

	std::string underline = "^";


	for (int i = tokenBegin; i < characterPosition - 1; i++)
		underline += '~';

	std::cout << strToRed(underline) << std::endl;

}

int Source::nextChar() {
	characterPosition++;

	// read a line to the buffer if necessary
	if (characterPosition > lineBuffer.size()) {
		std::string temp;

		if (!std::getline(file, temp)) {
			return EOF;
		} else {
			// new line successfuly read
			lineBuffer = temp;
			linePosition++;
			tokenBegin = 0;
			characterPosition = -1;

			return '\n';
		}
	} else if (characterPosition == lineBuffer.size()) {
		return '\n';
	}

	return lineBuffer[characterPosition];
}

Source::Source(const std::string &nFileName) {
	fileName = nFileName;
	nErrors = 0;
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

int Source::getNErrors() {
	return nErrors;
}
