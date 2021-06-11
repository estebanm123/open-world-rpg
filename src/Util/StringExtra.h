#pragma once

#include <string>
#include <vector>

struct StringExtra {
	static std::vector<std::string> split(const std::string & str, const std::string & regex_str);
};
