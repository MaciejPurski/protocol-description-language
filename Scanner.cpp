#include <vector>
#include "Scanner.h"

Token Scanner::nextToken() {
	while (isspace(ch) || ch == '#') {
		nextChar();

		if (ch == '#')
			while (ch != '\n')
				nextChar();
	}

	//TODO: column number
	begIndex = src.getIndex();

	if (ch == EOF) {
		return Token(END, begIndex, 1);
	}

	switch (ch) {
		case '+':
			nextChar();
			return Token(ADD_OPERATOR, begIndex, 1);
		case '-':
			nextChar();
			return Token(SUBTR_OPERATOR, begIndex, 1);
		case '*':
			nextChar();
			return Token(MUL_OPERATOR, begIndex, 1);
		case '(':
			nextChar();
			return Token(OPEN_PARENT, begIndex, 1);
		case ')':
			nextChar();
			return Token(CLOSE_PARENT, begIndex, 1);
		case '{':
			nextChar();
			return Token(OPEN_BRACK, begIndex, 1);
		case '}':
			nextChar();
			return Token(CLOSE_BRACK, begIndex, 1);
		case ';':
			nextChar();
			return Token(SEMICOLON, begIndex, 1);
		case '=':
			nextChar();
			return Token(ASSIGNMENT, begIndex, 1);
		case ',':
			nextChar();
			return Token(COMMA, begIndex, 1);
		default:
			break;
	}

	// string constant
	if (ch == '\"')
		return getConstStringToken(ch);

	if (isalpha(ch))
		return getIdentifierToken();

	if (ch == '0')
		return getHexadecimalToken();

	if (isdigit(ch))
		return getDecimalToken();


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

	keywordMap = std::move(keywordMapTemp);

	nextChar();
}

bool Scanner::isKeyword(const int c) {
	return (keywordMap.find(std::string(1, ch)) != keywordMap.end());
}

bool Scanner::isSeparator(const int c) {
	return (separatorMap.find(ch) != separatorMap.end());
}

Token Scanner::getIdentifierToken() {
	std::string word;

	while (isalnum(ch) || ch == '_') {
		word += ch;
		nextChar();
	}

	// check if we have a keyword
	auto it2 = keywordMap.find(word);

	if (it2 == keywordMap.end()) // not a keyword
		return Token(IDENTIFIER, begIndex, word.size(), word);
	else // a keyword
		return Token(it2->second, begIndex, word.size());
}

Token Scanner::getDecimalToken() {
	int value = 0;
	unsigned int length = 0;

	while (isdigit(ch)) {
		value = value * 10 + ch - '0';
		nextChar();
		length++;
	}

	if (isalpha(ch)) {
		//TODO: invalid integer suffix
	}

	return Token(DEC_NUMBER, begIndex, length, "", value);
}

Token Scanner::getHexadecimalToken() {
	// we know that we alread have '0' character
	nextChar();

	// decimal 0 value
	if (!isalpha(ch)) {
		return Token(DEC_NUMBER, begIndex, 0, "", 0);
	}

	if (ch != 'x') {
		//TODO: error
	}

	nextChar();

	int value = 0;
	unsigned int length = 0;
	while (isHex(ch)) {
		value = (value << 4) + toHex(ch);

		nextChar();
		length++;
	}

	if (isalpha(ch)) {
		//TODO: error
	}

	return Token(HEX_NUMBER, begIndex, length, "", value);
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