#include <iostream>
#include "Scanner.h"
#include "Source.h"

int main() {
    Source src("test2.txt");
	Scanner s(src);

	Token t = s.nextToken();

	while (t.type != T_UNKNOWN) {
		std::cout << "TOKEN: " << s.tokenToName[t.type] << " " << t.stringValue << " " << t.intValue << std::endl;
		t = s.nextToken();
	}


    return 0;
}