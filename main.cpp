#include <iostream>
#include <cstring>
#include "Scanner.h"
#include "LexerTest.h"
#include "Parser.h"
#include "ParserTest.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Usage: ./TKOM --lexer-test <file>\n";
		std::cout << argv[0] << std::endl;
		std::cout << argv[1] << std::endl;
		std::cout << argv[2] << std::endl;
		exit(1);
	}

	if (!strcmp(argv[1], "--lexer-test")) {
		try {
			LexerTest l(argv[2]);

			l.startTest();
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;

			std::cout << "Program terminated\n";
		}

	} else if (!strcmp(argv[1], "--parser-test")) {
		try {
			ParserTest p(argv[2]);

			p.start();
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;

			std::cout << "Program terminated\n";
		}


	} else {
		std::cout << "Unknown arguments\n";
		exit(1);

	}



    return 0;
}