#ifndef TKOM_FIELD_H
#define TKOM_FIELD_H

#include <utility>
#include <string>
#include <sstream>
#include <iomanip>

enum Format {HEX, DECIMAL, STRING, FLOAT};
enum ConditionSymbol {NONE, EQUAL, NOT_EQUAL};

/**
 * Class used to encapsulate information on a single filed in a packet.
 */
class Field {
private:
	using Condition = std::pair<ConditionSymbol, int>;
	std::string name;
	Format format; // used when displaying a value
	int offset;
	int length;
	Condition c = std::make_pair(NONE, 0);

public:
	Field () {

	}

	std::string toString(unsigned char *buffer);
};




#endif
