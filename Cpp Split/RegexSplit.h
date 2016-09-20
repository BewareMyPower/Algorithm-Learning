// RegexSplit.h: 简单的字符串分解，基于regex的正则替换
#pragma once
#include <vector>
#include <string>
#include <regex>

std::vector<std::string> split(std::string str, const std::regex& e)
{
	std::vector<std::string> res;
	std::smatch sm;
	auto itbeg = str.cbegin();
	auto itend = str.cend();

	while (std::regex_search(itbeg, itend, sm, e))
	{
		if (itbeg != sm[0].first)
			res.emplace_back(itbeg, sm[0].first);
		itbeg = sm[0].second;
	}

	if (itbeg != str.cend())
		res.emplace_back(itbeg, str.end());
	
	return res;
}

inline void use_regex_split()
{
	std::string s = "<Head>this is a head</Head>\n  \
			<p>this is a paragraph</p>";
	// 采用非贪婪匹配, 得到<xxx>和</xxx>之间的字符串, 忽略空白字符
	auto substrs = split(s, std::regex("(<(.*?)>\\s*)+"));  
	for (auto& str : substrs)
		std::cout << str << std::endl;
}
