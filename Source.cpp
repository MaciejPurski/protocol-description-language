#include "Source.h"
#include "Token.h"
#include <exception>
#include <iomanip>

void Source::printLine() {
}

unsigned int Source::getColumn() {
	return characterPosition;
}

unsigned int Source::getLineNumber() {
	return linePosition;
}

unsigned int Source::getPosition() {
	return filePosition;
}

void Source::raiseError(const std::string &errorDesc, Token &token) {
	Position pos = token.position;
	std::string lineBuf;

	file.seekg(0, std::ios::beg);

	for (int i = 0; i < pos.line; i++) {
		std::getline(file, lineBuf);
		std::cout << "line: " << lineBuf << std::endl;
	}

	std::cout << "linebuf: " << lineBuf << std::endl;
	std::cerr << std::endl;

	std::cerr << strToWhite(fileName + ":" + std::to_string(pos.line) + ":" + std::to_string(pos.column) + ": ")
	          << strToRed("error: ") << errorDesc << std::endl;

	std::cerr << lineBuf.substr(0, pos.column - 1) << strToRed(lineBuf.substr(pos.column - 1, token.length))
	<< lineBuf.substr(pos.column - 1 + token.length) << std::endl;

	for (int i = 0; i < pos.column; i++) {
		if (lineBuf[i] == '\t')
			std::cerr << "\t";
		else
			std::cerr << " ";
	}

	std::string underline;

	underline += '^';

	for (int i = 0; i < token.length - 1; i++)
		underline += '~';

	std::cerr << strToRed(underline) << std::endl;
}

int Source::nextChar() {
	// read a line to the buffer if necessary
	int nextChar = file.get();

	characterPosition++;
	if (prevChar == '\n') {
		linePosition++;
		characterPosition = 0;
	}

	prevChar = nextChar;

	return nextChar;
}

Source::Source(const std::string &nFileName, bool testMode = false) {
	this->testMode = testMode;
	fileName = nFileName;
	nErrors = 0;
	characterPosition = 0;
	linePosition = 0;
	filePosition = 0;
	prevChar = '\n';

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
