#include <iostream>
#include <cstring>
#include "Scanner.h"
#include "LexerTest.h"
#include "Parser.h"
#include "ParserTest.h"
#include "Interpreter.h"

int main(int argc, char *argv[]) {
	if (argc < 3) {
		std::cout << "Usage: ./TKOM --lexer-test <file>\n";
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


	} else if (!strcmp(argv[1], "--packets-parser")) {
		try {
			if (argc != 4) {
				std::cout << "Not enough arguments\n";
			}
			Interpreter i(argv[2], argv[3], false);

			i.start();
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;

			std::cout << "Program terminated\n";
		}
	} else if (argc == 3) {
		try {
			Interpreter i(argv[1], argv[2], true);

			i.start();
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