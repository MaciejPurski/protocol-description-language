#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_COLORS_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_COLORS_H
#include <string>

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

#endif //PROTOCOL_DESCRIPTION_LANGUAGE_COLORS_H
