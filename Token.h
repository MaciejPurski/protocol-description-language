#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H

#include <string>

enum TokenType {
	PACKET_KEYWORD, SEQUENCE_KEYWORD, PROTOCOL_KEYWORD, ITERATE_KEYWORD, DOITERATE_KEYWORD, ALT_KEYWORD, OR_KEYWORD, OPT_KEYWORD, REPEAT_KEYWORD,
	INT_TYPE, UINT_TYPE, BYTES_TYPE, STRING_TYPE, BITS_TYPE, ADD_OPERATOR,
	SUBTR_OPERATOR, MUL_OPERATOR, OPEN_PARENT, CLOSE_PARENT, OPEN_BRACK, CLOSE_BRACK,
	SEMICOLON, ASSIGNMENT, DEC_NUMBER, HEX_NUMBER, COMMA, END, UNKNOWN, IDENTIFIER
};

struct Token {
	TokenType type;
	std::string stringValue;
	unsigned int intValue;
	unsigned int position;
	unsigned int length;

	explicit Token(TokenType nType, unsigned int nposition, unsigned int nlength, std::string str = "", unsigned int nValue = 0) :
			position(nposition), length(nlength), type(nType), stringValue(str), intValue(nValue)  {}

	Token() {}
};

#endif //TKOM_TOKEN_H
