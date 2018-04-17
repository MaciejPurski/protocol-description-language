#include "Scanner.h"

Token Scanner::nextToken() {
	while (isspace(ch))
		nextChar(); // omit white spaces

	if (ch == EOF)
		return Token(END);

	if (isSeparator(ch))
		return getSeparatorToken(ch);

	// string constant
	if (ch == '\"') {
		return getConstStringToken(ch);
	}

	// is a word
	if (isalnum(ch)) {
		std::string word;
		src.setTokenBegin();

		do {
			word += ch;
			nextChar();
		} while (isalnum(ch) || ch == '_');

		// can be identifier or a keyword
		if (isalpha(word[0]))
			return getIdentifierToken(word);

		if (word[0] == '0')
			return getHexadecimalToken(word);

		return getDecimalToken(word);
	}

	nextChar();
	src.raiseError(std::string(1, ch), "Unknown token");

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

bool Scanner::isSeparator(const int c) {
	return (separatorMap.find(ch) != separatorMap.end());
}

Token Scanner::getSeparatorToken(const int ch) {
	auto it  = separatorMap.find(ch);

	nextChar();

	if (it != separatorMap.end())
		return Token(it->second);

	return Token(UNKNOWN);
}

Token Scanner::getKeywordToken(const int ch) {
	auto it  = keywordMap.find(std::string(1, ch));

	nextChar();

	if (it != keywordMap.end())
		return Token(it->second);

	return Token(UNKNOWN);
}

Token Scanner::getIdentifierToken(const std::string &word) {
	auto it2 = keywordMap.find(word);

	if (it2 == keywordMap.end()) // not a keyword
		return Token(IDENTIFIER, word);
	else // a keyword
		return Token(it2->second, word);
}

Token Scanner::getDecimalToken(const std::string &word) {
	int value = 0;

	for (int i = 0; i < word.size(); i++) {
		if (!isdigit(word[i])) {
			src.raiseError(word, "Invalid integer suffix");
			return Token(UNKNOWN);
		}

		value = value * 10 + word[i] - '0';
	}

	return Token(DEC_NUMBER, "", value);
}

Token Scanner::getHexadecimalToken(const std::string &word) {
	if (word.size() == 1 || word[1] != 'x') {
		// decimal value 0
		if (word.size() == 1)
			return Token(DEC_NUMBER, "", 0);

		src.raiseError(word, "Invalid integer suffix");
		return Token(UNKNOWN);
	}

	int value = 0;

	for (int i = 2; i < word.size(); i++) {
		if (!isHex(word[i])) {
			src.raiseError(word, "Invalid integer suffix");
			return Token(UNKNOWN);
		}

		value = (value << 4) + toHex(word[i]);
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
		src.raiseError("", "Quotation not closed");
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
