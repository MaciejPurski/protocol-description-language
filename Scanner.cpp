#include <vector>
#include "Scanner.h"

Token Scanner::nextToken() {
	skipSpaces();

	position.filePostiion = src.getPosition();
	position.column = src.getColumn();
	position.line = src.getLineNumber();

	if (ch == EOF)
		return Token(END, position, 1);

	// string constant
	if (ch == '\"')
		return getConstStringToken(ch);

	if (isalpha(ch))
		return getIdentifierToken();

	if (ch == '0')
		return getHexadecimalToken();

	if (isdigit(ch))
		return getDecimalToken();

	return getOperatorToken();
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

Token Scanner::getIdentifierToken() {
	std::string word;

	while (isalnum(ch) || ch == '_') {
		word += ch;
		nextChar();
	}

	// check if we have a keyword
	auto it2 = keywordMap.find(word);

	if (it2 == keywordMap.end()) // not a keyword
		return Token(IDENTIFIER, position, word.size(), word);
	else // a keyword
		return Token(it2->second, position, word.size());
}

Token Scanner::getDecimalToken() {
	int value = 0;
	unsigned int length = 0;

	while (isdigit(ch)) {
		value = value * 10 + ch - '0';
		nextChar();
		length++;
	}

	if (isalnum(ch)) {
		while (isalnum(ch)) {
			length++;
			nextChar();
		}

		Token t(UNKNOWN, position, length);
		src.raiseError("Invalid integer suffix", t);

		throw std::runtime_error("Lexer error");
	}

	return Token(DEC_NUMBER, position, length, "", value);
}

Token Scanner::getHexadecimalToken() {
	unsigned int length = 1;
	// we know that we alread have '0' character
	nextChar();

	// decimal 0 value
	if (!isalnum(ch))
		return Token(DEC_NUMBER, position, 0, "", 0);

	if (ch != 'x') {
		while (isalnum(ch)) {
			length++;
			nextChar();
		}

		Token t(UNKNOWN, position, length);
		src.raiseError("Invalid integer suffix", t);

		throw std::runtime_error("Lexer error");
	}

	nextChar();
	length++;

	int value = 0;
	while (isHex(ch)) {
		value = (value << 4) + toHex(ch);

		nextChar();
		length++;
	}

	if (isalnum(ch)) {
		while (isalnum(ch)) {
			length++;
			nextChar();
		}

		Token t(UNKNOWN, position, length);
		src.raiseError("Invalid integer suffix", t);

		throw std::runtime_error("Lexer error");
	}

	return Token(HEX_NUMBER, position, length, "", value);
}

Token Scanner::getOperatorToken() {
	switch (ch) {
		case '+':
			nextChar();
			return Token(ADD_OPERATOR, position, 1);
		case '-':
			nextChar();
			return Token(SUBTR_OPERATOR, position, 1);
		case '*':
			nextChar();
			return Token(MUL_OPERATOR, position, 1);
		case '(':
			nextChar();
			return Token(OPEN_PARENT, position, 1);
		case ')':
			nextChar();
			return Token(CLOSE_PARENT, position, 1);
		case '{':
			nextChar();
			return Token(OPEN_BRACK, position, 1);
		case '}':
			nextChar();
			return Token(CLOSE_BRACK, position, 1);
		case ';':
			nextChar();
			return Token(SEMICOLON, position, 1);
		case '=':
			nextChar();
			return Token(ASSIGNMENT, position, 1);
		case ',':
			nextChar();
			return Token(COMMA, position, 1);
		default:
			Token t(UNKNOWN, position, 1);
		std::cout << "token length: " << t.length << std::endl;
			nextChar();
			src.raiseError("Unknown token: ", t);
			throw std::runtime_error("Unknown token\n");
	}
}

Token Scanner::getConstStringToken(const int c) {
	std::string str;

	nextChar();

	while (ch != '\"' && ch != EOF) {
		str += (char) ch;
		nextChar();
	}

	if (ch == EOF) {
		Token t(UNKNOWN, position, str.size() + 1);
		src.raiseError("Quotation not closed", t);
		return Token();
	}

	nextChar();

	return Token(STRING_TYPE, position, str.size(), str);
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

void Scanner::skipSpaces() {
	while (isspace(ch) || ch == '#') {
		nextChar();

		if (ch == '#')
			while (ch != '\n')
				nextChar();
	}
}
