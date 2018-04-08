#include <iostream>
#include "Scanner.h"
#include "Source.h"

int main() {
    Source src("../tests/full-test.txt");
	Scanner s(src);

	Token t = s.nextToken();

	while (t.type != T_END) {
		std::cout << "TOKEN: " << s.tokenToString(t) << " " << t.stringValue << " " << t.intValue << std::endl;
		t = s.nextToken();
	}


    return 0;
}