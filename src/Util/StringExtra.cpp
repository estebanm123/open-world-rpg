#include "StringExtra.h"

#include <regex>

std::vector<std::string> StringExtra::split(const std::string & str, const std::string & regex_str) {
	std::regex regexz(regex_str);
	std::sregex_token_iterator token_iter(str.begin(), str.end(), regexz, -1);
	std::sregex_token_iterator end;
	std::vector<std::string> list;
	while (token_iter != end)
	{
		list.emplace_back(*token_iter++);
	}
	return list;
}
