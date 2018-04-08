#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H

enum TokenType {
	T_VAR_KEYWORD, T_PACK_KEYWORD, T_RULE_KEYWORD, T_INT8, T_INT16, T_INT32, T_INT64, T_UINT8, T_UINT16, T_UINT32, T_UINT64,
	T_FLOAT, T_DOUBLE, T_BYTE, T_STR_T, T_IDENT, T_STRING, T_OPEN_PARENT, T_CLOSE_PARENT, T_OPEN_BRACK, T_CLOSE_BRACK, T_ASSIGN, T_COLON,
	T_SEMICOLON, T_ASTERIX, T_DECIMAL, T_HEX, T_UNKNOWN, T_END, T_COMMA
};

struct Token {
	TokenType type;
	std::string stringValue;
	int intValue;

	explicit Token(TokenType nType, std::string str = "", int nValue = 0) : type(nType), stringValue(str), intValue(nValue) {
	}
};

#endif //TKOM_TOKEN_H
