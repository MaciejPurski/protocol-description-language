#include "Scanner.h"


Token Scanner::nextToken() {
	while (isspace(ch))
		nextChar(); // omit white spaces

	if (ch == EOF)
		return Token(END);

	if (isKeyword(ch))
		return getKeywordToken(ch);

	// is a word
	if (isalpha(ch)) {
		return getIdentifierToken(ch);
	}

	// string constant
	if (ch == '\"') {
		return getConstStringToken(ch);
	}

	// hexadecimal number
	if (ch == '0') {
		return getHexadecimalToken(ch);
	}

	// decimal number
	if (isdigit(ch)) {
		return getDecimalToken(ch);
	}

	nextChar();
	src.raiseError("Unknown token");

	return Token(UNKNOWN);
}

Scanner::Scanner(Source &s) : src(s) {
	// initialize maps
	std::unordered_map<std::string, TokenType> keywordMapTemp = {
			{"iterate", ITERATE_KEYWORD},
			{"alt", ALT_KEYWORD},
			{"or", OR_KEYWORD},
			{"opt", OPT_KEYWORD},
			{"repeat", REPEAT_KEYWORD},
			{"int", INT_TYPE},
			{"uint", UINT_TYPE},
			{"bytes", BYTES_TYPE},
			{"string", STRING_TYPE},
			{"bits", BITS_TYPE},
			{"+", ADD_OPERATOR},
			{"-", SUBTR_OPERATOR},
			{"*", MUL_OPERATOR},
			{"(", OPEN_PARENT},
			{")", CLOSE_PARENT},
			{"{", OPEN_BRACK},
			{"}", CLOSE_BRACK},
			{";", SEMICOLON},
			{"=", ASSIGNMENT},
			{",", COMMA}
	};

	keywordMap = std::move(keywordMapTemp);

	std::unordered_map<TokenType, std::string> tokenMapTemp = {
			{ITERATE_KEYWORD, "ITERATE KEYWORD"},
			{ALT_KEYWORD, "ALT KEYWORD"},
			{OR_KEYWORD, "OR KEYWORD"},
			{OPT_KEYWORD, "OPT KEYWORD"},
			{REPEAT_KEYWORD, "REPEAT KEYWORD"},
			{INT_TYPE, "INT_TYPE"},
			{UINT_TYPE, "UINT_TYPE"},
			{BYTES_TYPE, "BYTES TYPE"},
			{STRING_TYPE, "STRING TYPE"},
			{BITS_TYPE, "BITS TYPE"},
			{ADD_OPERATOR, "ADD OPERATOR"},
			{SUBTR_OPERATOR, "SUBTR OPERATOR"},
			{MUL_OPERATOR, "MUL OPERATOR"},
			{OPEN_PARENT, "OPEN PARENT"},
			{CLOSE_PARENT, "CLOSE PARENT"},
			{OPEN_BRACK, "OPEN BRACK"},
			{CLOSE_BRACK, "CLOSE BRACK"},
			{SEMICOLON, "SEMICOLON"},
			{ASSIGNMENT, "ASSIGNMNET"},
			{DEC_NUMBER, "DEC NUMBER"},
			{HEX_NUMBER, "HEX NUMBER"},
			{COMMA, "COMMA"},
			{UNKNOWN, "UNKOWN"},
			{END, "END"},
			{IDENTIFIER, "IDENTIFIER"}
	};

	tokenToName = std::move(tokenMapTemp);

	nextChar();
}

std::string Scanner::tokenToString(const Token &t) {
	auto it = tokenToName.find(t.type);

	if (tokenToName.end() == it)
		return "";

	return it->second;
}

bool Scanner::isKeyword(const int c) {
	return (keywordMap.find(std::string(1, ch)) != keywordMap.end());
}

Token Scanner::getKeywordToken(const int ch) {
	auto it  = keywordMap.find(std::string(1, ch));

	nextChar();

	if (it != keywordMap.end())
		return Token(it->second);

	return Token(UNKNOWN);
}

Token Scanner::getIdentifierToken(const int c) {
	std::string str;
	src.setTokenBegin();

	do {
		str += (char) ch;
		nextChar();
	} while (isalnum(ch) || ch == '_');

	auto it2 = keywordMap.find(str);

	// not a keyword
	if (it2 == keywordMap.end())
		return Token(IDENTIFIER, str);
	else
		return Token(it2->second, str);
}

Token Scanner::getDecimalToken(const int c) {
	int value = 0;
	src.setTokenBegin();

	while (isdigit(ch)) {
		value = value * 10 + ch - '0';
		nextChar();
	}

	// integer can't be followed with non-terminator characters
	if (!isspace(ch) && ch != EOF && !isKeyword(ch)) {
		src.raiseError("Wrong decimal number format");

		return Token(UNKNOWN);
	}


	return Token(DEC_NUMBER, "", value);
}

Token Scanner::getHexadecimalToken(const int c) {
	src.setTokenBegin();
	nextChar();

	if (ch != 'x') {
		// decimal value 0
		if (isspace(ch) || ch == EOF || isKeyword(ch))
			return Token(DEC_NUMBER, "", 0);
		src.raiseError("Wrong hex number format");
		return Token(UNKNOWN);
	}

	int value = 0;

	nextChar();

	while (isHex(ch)) {
		value = (value << 4) + toHex(ch);
		nextChar();
	}

	if (!isspace(ch) && ch != EOF && !isKeyword(ch)) {
		src.raiseError("Wrong hexadecimal number format");
		return Token(UNKNOWN);
	}

	return Token(HEX_NUMBER, "", value);
}

Token Scanner::getConstStringToken(const int c) {
	std::string str;
	src.setTokenBegin();

	nextChar();

	while (ch != '\"' && ch != EOF) {
		str += (char) ch;
		nextChar();
	}

	if (ch == EOF) {
		src.raiseError("Quotation not closed");
		return Token(UNKNOWN);
	}

	nextChar();

	return Token(STRING_TYPE, str);
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
