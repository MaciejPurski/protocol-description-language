#ifndef TKOM_LEXERTEST_H
#define TKOM_LEXERTEST_H

#include "Source.h"
#include "Scanner.h"

class LexerTest {
private:
	Source src;
	Scanner s;
	std::unordered_map<TokenType, std::string> tokenToName;

public:
	explicit LexerTest(const char *str) : src(str, true), s(src) {
		std::unordered_map<TokenType, std::string> tokenMapTemp = {
				{PACKET_KEYWORD, "PACKET KEYWORD"},
				{SEQUENCE_KEYWORD, "SEQUENCE KEYWORD"},
				{PROTOCOL_KEYWORD, "PROTOCOL KEYWORD"},
				{DOITERATE_KEYWORD, "DO_ITERATE KEYWORD"},
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
				{UNKNOWN, "UNKNOWN"},
				{END, "END"},
				{IDENTIFIER, "IDENTIFIER"}
		};

		tokenToName = std::move(tokenMapTemp);
	}

	void startTest() {
		Token t = s.nextToken();

		while (t.type != END) {
			std::cout << "TOKEN: " << tokenToName[t.type] << " ";
			if (t.type == IDENTIFIER)
				std::cout << t.stringValue << " ";
			if (t.type == DEC_NUMBER || t.type == HEX_NUMBER)
				std::cout << t.intValue;

			std::cout << std::endl;

			t = s.nextToken();
		}

		std::cout << std::endl;
		std::cout << "Number of scanning errors: " << src.getNErrors() << std::endl;
	}
};

#endif
