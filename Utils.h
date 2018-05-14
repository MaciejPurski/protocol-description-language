#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_UTILS_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_UTILS_H
#include <string>
#include <vector>
#include "Token.h"

static inline std::string strToRed(const std::string &str) {
#ifdef __unix__
	return  std::string("\033[1;31m" + str + "\033[0m");
#else
	return str;
#endif
}

static inline std::string strToWhite(const std::string &str) {
#ifdef __unix__
	return  std::string("\033[1;37m" + str + "\033[0m");
#else
	return str;
#endif
}

static inline std::string strToYellow(const std::string &str) {
#ifdef __unix__
	return  std::string("\033[1;33m" + str + "\033[0m");
#else
	return str;
#endif
}

static inline std::string strToBlue(const std::string &str) {
#ifdef __unix__
	return  std::string("\033[1;34m" + str + "\033[0m");
#else
	return str;
#endif
}

static inline std::string tokenToString(TokenType t) {
	static std::vector<std::string> arr = {
			"packet", "sequence", "protocol", "iterate", "do_iterate", "alt", "or", "opt", "repeat",
			"int", "uint", "bytes", "string", "bits", "+",
			"-", "*", "(", ")", "{", "}",
			";", "=", "decimal number", "hexadecimal number", ",", "END", "UNKNOWN", "identifier"
	};

	return arr[t];
}

#endif
