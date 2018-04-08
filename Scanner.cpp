//
// Created by maciej on 07.04.18.
//

#include "Scanner.h"


Token Scanner::nextToken() {
	while (isspace(ch))
		nextChar(); // omit white spaces

	if (ch == EOF)
		return Token(T_END);

	// look for one character keyword
	Token t = getKeywordToken(ch);

	if (t.type != T_UNKNOWN) {
		nextChar();
		return t;
	}

	// is a word
	if (isalpha(ch)) {
		std::string str;
		src.setTokenBegin();

		do {
			str += (char) ch;
			nextChar();
		} while (isalnum(ch) || ch == '_');

		auto it2 = keywordMap.find(str);

		// not a keyword
		if (it2 == keywordMap.end())
			return Token(T_IDENT, str);
		else
			return Token(it2->second, str);
	}

	// string constant
	if (ch == '\"') {
		std::string str;
		src.setTokenBegin();

		nextChar();

		while (ch != '\"' && ch != EOF) {
			str += (char) ch;
			nextChar();
		}

		if (ch == EOF) {
			src.raiseError("Quotation not closed");
			return Token(T_UNKNOWN);
		}

		return Token(T_STRING, str);
	}

	// hexadecimal number
	if (ch == '0') {
		src.setTokenBegin();
		nextChar();

		if (ch != 'x') {
			src.raiseError("Wrong number value");
			return Token(T_UNKNOWN);
		}

		int value = 0;

		nextChar();
		if (ch == EOF || isspace(ch)) {
			src.raiseError("Hexadecimal number not finished");
			return Token(T_UNKNOWN);
		}

		while (!isspace(ch) && ch != EOF) {
			value = value << 4;

			if (isdigit(ch))
				value += ch - '0';
			else if (ch >= 'a' && ch <= 'f')
				value += ch - 'a' + 10;
			else {
				src.raiseError("Hex number format wrong");
				return Token(T_UNKNOWN);
			}

			nextChar();
		}

		return Token(T_HEX, "", value);
	}

	if (isdigit(ch) && ch != '0') {
		int value = 0;
		src.setTokenBegin();

		do {
			value = value * 10 + ch - '0';
			nextChar();
		} while (isdigit(ch));


		return Token(T_DECIMAL, "", value);
	}

	src.setTokenBegin();
	src.raiseError("Unknown token");

	return Token(T_UNKNOWN);

}

Token Scanner::getKeywordToken(const int ch) {
	auto it  = keywordMap.find(std::string(1, ch));

	if (it != keywordMap.end())
		return Token(it->second);

	return Token(T_UNKNOWN);
}
