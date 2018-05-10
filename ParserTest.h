#ifndef TKOM_PARSERTEST_H
#define TKOM_PARSERTEST_H

#include "Parser.h"

class ParserTest {
private:
	Source src;
	Scanner s;
	Parser p;

public:
	explicit ParserTest(const char *str) : src(str, true), s(src), p(s, src) {
	}

	void start() {
		std::unique_ptr<Protocol> prot = p.parse();

		if (prot != nullptr)
			prot->traverseParseTree(0);
	}
};

#endif //TKOM_PARSERTEST_H
