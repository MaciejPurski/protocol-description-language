#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H
#include <iostream>
#include <unordered_map>
#include "Source.h"
#include "Token.h"

/**
 * Class used by the interpreter to get new token.
 * It gets next character from Source class.
 */
class Scanner {
private:
	Source &src;
	int ch; // current character
	std::unordered_map<std::string, TokenType> keywordMap;
	std::unordered_map<char, TokenType> separatorMap;

	std::unordered_map<TokenType, std::string> tokenToName;

	bool isKeyword(const int c);
	bool isSeparator(const int c);
	bool isHex(const int c);
	int toHex(const int c);
	Token getKeywordToken(const int c);
	Token getSeparatorToken(const int c);
	Token getIdentifierToken(const std::string &word);
	Token getDecimalToken(const std::string &word);
	Token getHexadecimalToken(const std::string &word);
	Token getConstStringToken(const int c);

	void nextChar() {
		ch = src.nextChar();
	}


public:
	explicit Scanner(Source &s);
	Token nextToken();
	std::string tokenToString(const Token &t);
};


#endif //TKOM_SCANNER_H
