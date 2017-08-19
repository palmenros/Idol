#include "FileUtils.h"
#include <fstream>
#include <sstream>

namespace Idol
{
String FileUtils::readTextFile(const String &path)
{
	std::ifstream input(path);

	if (!input.is_open()) {
		ERROR("Could not open file '" + path + "'");
		return "";
	}

	std::stringstream ss;
	ss << input.rdbuf();

	String contents = ss.str();

	//Account for UTF-8 BOM
	if (contents.length() >= 3) {
		char a = contents[0], b = contents[1], c = contents[2];
		if (a == 0xEF && b == 0xBB && c == 0xBF) {
			return contents.substr(3);
		}
	}

	return contents;
}
}
