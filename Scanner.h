#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H
#include <iostream>
#include <unordered_map>
#include "Source.h"
enum TokenType {
	T_VAR_KEYWORD, T_PACK_KEYWORD, T_RULE_KEYWORD, T_INT8, T_INT16, T_INT32, T_INT64, T_UINT8, T_UINT16, T_UINT32, T_UINT64,
	T_FLOAT, T_DOUBLE, T_BYTE, T_STR_T, T_IDENT, T_STRING, T_OPEN_PARENT, T_CLOSE_PARENT, T_OPEN_BRACK, T_CLOSE_BRACK, T_ASSIGN, T_COLON,
	T_SEMICOLON, T_ASTERIX, T_DECIMAL, T_HEX, T_QUOTE, T_UNKNOWN, T_END
};

struct Token {
	TokenType  type;
	std::string stringValue;
	int intValue;

	explicit Token(TokenType nType, std::string strValue = "", int nintValue = 0) : type(nType), stringValue(strValue), intValue(nintValue) {}
};

class Scanner {
private:
	Source &src;
	int ch; // current character

	const std::unordered_map<std::string, TokenType> keywordMap = {
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
			{"\"", T_QUOTE}
	};

	Token getKeywordToken(const int ch);

	void nextChar() {
		ch = src.nextChar();
	}


public:
	explicit Scanner(Source &s) : src(s) {
		ch = '\n';
	}

	std::unordered_map<TokenType, std::string> tokenToName = {
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
			{T_QUOTE, "T_QUOTE"},
			{T_UNKNOWN, "T_UNKNOWN"},
			{T_END, "T_TEST"}
	};




	Token nextToken();

};


#endif //TKOM_SCANNER_H
