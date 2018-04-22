#include "Scanner.h"

Token Scanner::nextToken() {
	while (isspace(ch))
		nextChar(); // omit white spaces

	// omit comments
	if (ch == '#') {
		while (ch != '\n')
			nextChar();
		while (isspace(ch))
			nextChar();
	}

	begIndex = src.getIndex();

	if (ch == EOF) {
		return Token(END, begIndex, 1);
	}

	if (isSeparator(ch)) {
		return getSeparatorToken(ch);
	}

	// string constant
	if (ch == '\"') {
		return getConstStringToken(ch);
	}

	// is a word
	if (isalnum(ch)) {
		std::string word;

		do {
			word += (char) ch;
			nextChar();
		} while (isalnum(ch) || ch == '_');

		// can be identifier or a keyword
		if (isalpha(word[0]))
			return getIdentifierToken(word);

		if (word[0] == '0')
			return getHexadecimalToken(word);

		return getDecimalToken(word);
	}

	Token t(UNKNOWN, begIndex, 1);

	src.raiseError("Unknown token", t);
	nextChar();

	return t;
}

Scanner::Scanner(Source &s) : src(s) {
	// initialize maps
	std::unordered_map<std::string, TokenType> keywordMapTemp = {
			{"packet", PACKET_KEYWORD},
			{"sequence", SEQUENCE_KEYWORD},
			{"protocol", PROTOCOL_KEYWORD},
			{"iterate", ITERATE_KEYWORD},
			{"do_iterate", DOITERATE_KEYWORD},
			{"alt", ALT_KEYWORD},
			{"or", OR_KEYWORD},
			{"opt", OPT_KEYWORD},
			{"repeat", REPEAT_KEYWORD},
			{"int", INT_TYPE},
			{"uint", UINT_TYPE},
			{"bytes", BYTES_TYPE},
			{"string", STRING_TYPE},
			{"bits", BITS_TYPE}
	};

	std::unordered_map<char, TokenType> separatorMapTemp = {
			{'+', ADD_OPERATOR},
			{'-', SUBTR_OPERATOR},
			{'*', MUL_OPERATOR},
			{'(', OPEN_PARENT},
			{')', CLOSE_PARENT},
			{'{', OPEN_BRACK},
			{'}', CLOSE_BRACK},
			{';', SEMICOLON},
			{'=', ASSIGNMENT},
			{',', COMMA}
	};

	keywordMap = std::move(keywordMapTemp);
	separatorMap = std::move(separatorMapTemp);

	nextChar();
}

bool Scanner::isKeyword(const int c) {
	return (keywordMap.find(std::string(1, ch)) != keywordMap.end());
}

bool Scanner::isSeparator(const int c) {
	return (separatorMap.find(ch) != separatorMap.end());
}

Token Scanner::getSeparatorToken(const int ch) {
	auto it  = separatorMap.find(ch);

	nextChar();

	if (it != separatorMap.end())
		return Token(it->second, begIndex, 1);

	return Token(UNKNOWN, begIndex, 1);
}


Token Scanner::getIdentifierToken(const std::string &word) {
	auto it2 = keywordMap.find(word);

	if (it2 == keywordMap.end()) // not a keyword
		return Token(IDENTIFIER, begIndex, word.size(), word);
	else // a keyword
		return Token(it2->second, begIndex, word.size());
}

Token Scanner::getDecimalToken(const std::string &word) {
	int value = 0;

	for (unsigned int i = 0; i < word.size(); i++) {
		if (!isdigit(word[i])) {
			Token t(UNKNOWN, begIndex, word.size());

			src.raiseError("Invalid integer suffix", t);

			return t;
		}

		value = value * 10 + word[i] - '0';
	}

	return Token(DEC_NUMBER, begIndex, word.size(), "", value);
}

Token Scanner::getHexadecimalToken(const std::string &word) {
	if (word.size() == 1 || word[1] != 'x') {
		// decimal value 0
		if (word.size() == 1)
			return Token(DEC_NUMBER, begIndex, word.size(), "", 0);

		Token t(UNKNOWN, begIndex, word.size());

		src.raiseError("Invalid integer suffix", t);

		return t;
	}

	int value = 0;

	for (unsigned int i = 2; i < word.size(); i++) {
		if (!isHex(word[i])) {
			Token t(UNKNOWN, begIndex, word.size());

			src.raiseError("Invalid integer suffix", t);

			return t;
		}

		value = (value << 4) + toHex(word[i]);
	}

	return Token(HEX_NUMBER, begIndex, word.size(), "", value);
}

Token Scanner::getConstStringToken(const int c) {
	std::string str;

	nextChar();

	while (ch != '\"' && ch != EOF) {
		str += (char) ch;
		nextChar();
	}

	if (ch == EOF) {
		Token t(UNKNOWN, begIndex, str.size() + 1);
		src.raiseError("Quotation not closed", t);
		return Token();
	}

	nextChar();

	return Token(STRING_TYPE, begIndex, str.size(), str);
}

bool Scanner::isHex(const int c) {
	return (isdigit(c) || (c >= 'a' && c <= 'f'));
}

int Scanner::toHex(const int c) {
	if (isdigit(c))
		return c - '0';

	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;

	return -1;
}
