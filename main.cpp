#include <iostream>
#include <cstring>
#include "Scanner.h"
#include "Source.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Wrong arguments number\n";
		std::cout << argv[0] << std::endl;
		std::cout << argv[1] << std::endl;
		std::cout << argv[2] << std::endl;
		exit(1);
	}

	if (!strcmp(argv[1], "--lexer-test")) {
		try {
			Source src(argv[2]);
			Scanner s(src);

			Token t = s.nextToken();

			//if (src.getIndex() == 0)
			//	src.printLine();

			while (t.type != END) {
				std::cout << "TOKEN: " << s.tokenToString(t) << " " << t.stringValue << " " << t.intValue << std::endl;
				t = s.nextToken();
			}
			std::cout << std::endl;
			std::cout << "Number of scanning errors: " << src.getNErrors() << std::endl;

		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			std::cerr << "Program terminated\n";
			exit(1);
		}

	} else {
		std::cout << "Unknown arguments\n";
		exit(1);
	}



    return 0;
}