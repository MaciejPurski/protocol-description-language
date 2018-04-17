#include "Source.h"
#include <exception>
#include <iomanip>

void Source::printLine() {
	std::cout << std::endl << lineBuffer << std::endl << std::endl;
}

int Source::getIndex() {
	return characterPosition;
}

std::string Source::strToRed(const std::string &str) {
#ifdef __unix__
	return  std::string("\033[1;31m" + str + "\033[0m");
#else
	return str;
#endif
}

std::string Source::strToWhite(const std::string &str) {
#ifdef __unix__
	return  std::string("\033[1;37m" + str + "\033[0m");
#else
	return str;
#endif
}

void Source::raiseError(const std::string &errorDesc,
			int begIndex, int midIndex, int endIndex) {
	nErrors++;

	std::cerr << std::endl;

	std::cerr << strToWhite(fileName + ":" + std::to_string(linePosition) + ":" + std::to_string(characterPosition + 1) + ": ")
	          << strToRed("error: ") << errorDesc << std::endl;

	std::cerr << lineBuffer.substr(0, begIndex) << strToRed(lineBuffer.substr(begIndex, endIndex - begIndex))
	<< lineBuffer.substr(endIndex) << std::endl;

	for (int i = 0; i < begIndex; i++)
		std::cerr << " ";

	std::string underline = "";


	for (int i = begIndex; i < midIndex; i++)
		underline += '~';

	underline += '^';

	for (int i = midIndex + 1; i < endIndex; i++)
		underline += '~';

	std::cerr << strToRed(underline) << std::endl;

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
			characterPosition = -1;
			if (testMode)
				printLine();

			return '\n';
		}
	} else if (characterPosition == lineBuffer.size()) {
		return '\n';
	}

	return lineBuffer[characterPosition];
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
