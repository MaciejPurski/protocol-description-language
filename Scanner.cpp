#include "Scanner.h"


Token Scanner::nextToken() {
	while (isspace(ch))
		nextChar(); // omit white spaces

	if (ch == EOF)
		return Token(T_END);

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

	return Token(T_UNKNOWN);

}

Scanner::Scanner(Source &s) : src(s) {
	// initialize maps
	std::unordered_map<std::string, TokenType> keywordMapTemp = {
			{"VARIABLES", T_VAR_KEYWORD},
			{"PACKETS", T_PACK_KEYWORD},
			{"RULES", T_RULE_KEYWORD},
			{"int8", T_INT8},
			{"int16", T_INT16},
			{"int32", T_INT32},
			{"int64", T_INT64},
			{"uint8", T_UINT8},
			{"uint16", T_UINT16},
			{"uint32", T_UINT32},
			{"uint64", T_UINT64},
			{"float", T_FLOAT},
			{"double", T_DOUBLE},
			{"bytes", T_BYTE},
			{"string", T_STRING},
			{"(", T_OPEN_PARENT},
			{")", T_CLOSE_PARENT},
			{"{", T_OPEN_BRACK},
			{"}", T_CLOSE_BRACK},
			{"=", T_ASSIGN},
			{":", T_COLON},
			{";", T_SEMICOLON},
			{"*", T_ASTERIX},
			{",", T_COMMA}
	};

	keywordMap = std::move(keywordMapTemp);

	std::unordered_map<TokenType, std::string> tokenMapTemp = {
		{T_VAR_KEYWORD, "T_VAR_KEYWORD"},
		{T_PACK_KEYWORD, "T_PACK_KEYWORD"},
		{T_RULE_KEYWORD, "T_RULE_KEYWORD"},
		{T_INT8, "T_INT8"},
		{T_INT16, "T_INT16"},
		{T_INT32, "T_INT32"},
		{T_INT64, "T_INT64"},
		{T_UINT8, "T_UINT8"},
		{T_UINT16, "T_UINT16"},
		{T_UINT32, "T_UINT32"},
		{T_UINT64, "T_UINT64"},
		{T_FLOAT, "T_FLOAT"},
		{T_DOUBLE, "T_DOUBLE"},
		{T_BYTE, "T_BYTE"},
		{T_STR_T, "T_STR_T"},
		{T_IDENT, "T_IDENT"},
		{T_STRING, "T_STRING"},
		{T_OPEN_PARENT, "T_OPEN_PARENT"},
		{T_CLOSE_PARENT, "T_CLOSE_PARENT"},
		{T_OPEN_BRACK, "T_OPEN_BRACK"},
		{T_CLOSE_BRACK, "T_OPEN_BRACK"},
		{T_ASSIGN, "T_ASSIGN"},
		{T_COLON, "T_COLON"},
		{T_SEMICOLON, "T_SEMICOLON"},
		{T_ASTERIX, "T_ASTERIX"},
		{T_DECIMAL, "T_DECIMAL"},
		{T_HEX, "T_HEX"},
		{T_UNKNOWN, "T_UNKNOWN"},
		{T_END, "T_END"},
		{T_COMMA, "T_COMMA"}
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

	return Token(T_UNKNOWN);
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
		return Token(T_IDENT, str);
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

		return Token(T_UNKNOWN);
	}


	return Token(T_DECIMAL, "", value);
}

Token Scanner::getHexadecimalToken(const int c) {
	src.setTokenBegin();
	nextChar();

	if (ch != 'x') {
		// decimal value 0
		if (isspace(ch) || ch == EOF || isKeyword(ch))
			return Token(T_DECIMAL, "", 0);
		src.raiseError("Wrong hex number format");
		return Token(T_UNKNOWN);
	}

	int value = 0;

	nextChar();

	while (isHex(ch)) {
		value = (value << 4) + toHex(ch);
		nextChar();
	}

	if (!isspace(ch) && ch != EOF && !isKeyword(ch)) {
		src.raiseError("Wrong hexadecimal number format");
		return Token(T_UNKNOWN);
	}

	return Token(T_HEX, "", value);
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
		return Token(T_UNKNOWN);
	}

	nextChar();

	return Token(T_STRING, str);
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
