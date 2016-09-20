// SimpleSplit.h: 简单的字符串分解，基于string::find
// 只支持单个字符作为间隔符
#pragma once
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& str, char sep)
{
	std::vector<std::string> res;
	std::string::size_type pos1 = 0, pos2 = pos1;
	while ((pos2 = str.find(sep, pos1)) != std::string::npos)
	{
		res.push_back(str.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
	}
	res.push_back(str.substr(pos1, pos2));
	return res;
}

inline void use_simple_split()
{
	std::string s = "A B C";
	auto substrs = split(s, ' ');
	display(substrs);
	s = "Hello,World,Cpp";
	substrs = split(s, ',');
	display(substrs);
}