#pragma once
#include <vector>
#include <string>

class Common
{
public:
	static const int BLOCK_SIZE = 8;

	template<class A> static A clamp(A val, A min, A max)
	{
		if (val > max) return max;
		if (val < min) return min;
		return val;
	}

	static std::vector<std::string> splitString(std::string str, char separator)
	{
		std::vector<std::string> res(0);
		unsigned int lastpos = 0;
		unsigned int length = str.length();

		for (unsigned int i = 0; i < length; i++)
		{
			if (str.at(i) == separator)
			{
				res.push_back(str.substr(lastpos, i - lastpos));
				lastpos = i + 1;
			}
		}

		res.push_back(str.substr(lastpos, length - lastpos));

		return res;
	}
};