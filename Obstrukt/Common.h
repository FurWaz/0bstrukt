#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Common
{
public:
	static const int BLOCK_SIZE = 8;
	static sf::FloatRect sceneScreenRect;
	static float BLOCK_2_PIXEL;
	static sf::Vector2i playerPosition;

	static void (*quitCallback)();

	void Quit();

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

	template<class T> static T SceneToScreenCoord(T coord)
	{
		return T(coord.x * BLOCK_SIZE + sceneScreenRect.left, coord.y * BLOCK_SIZE + sceneScreenRect.top);
	}

	template<class T> static T ScreenToSceneCoord(T coord)
	{
		return T((coord.x - sceneScreenRect.left) / BLOCK_2_PIXEL, (coord.y - sceneScreenRect.top) / (float)BLOCK_2_PIXEL);
	}
};