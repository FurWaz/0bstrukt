#pragma once
#include <SFML/Graphics.hpp>

class Image
{
private:
	sf::Image img;

public:
	Image()
	{
		img = sf::Image();
	}

	bool loadFromFile(sf::String p)
	{
		return img.loadFromFile(p);
	}

	sf::Color getPixel(unsigned int x, unsigned int y)
	{
		return img.getPixel(x, y);
	}

	sf::Vector2u getSize()
	{
		return img.getSize();
	}
};