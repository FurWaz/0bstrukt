#pragma once
#include <SFML/Graphics.hpp>
#include "Common.h"

class Pixel
{
private:
	sf::Color color;

public:
	static Pixel MixPixels(Pixel first, Pixel second, float factor = 0.5f)
	{
		factor = Common::clamp(factor, 0.f, 1.f);
		float counterFactor = 1 - factor;
		return Pixel(
			first.color.r * counterFactor + second.color.r * factor,
			first.color.g * counterFactor + second.color.g * factor,
			first.color.b * counterFactor + second.color.b * factor
		);
	}

	Pixel()
	{
		this->color = sf::Color::Black;
	}

	Pixel(sf::Color color)
	{
		this->color = color;
	}

	Pixel(unsigned int red, unsigned int green, unsigned int blue)
	{
		this->color = sf::Color(red, green, blue);
	}

	void copyColor(Pixel p)
	{
		this->color = p.color;
	}

	void MixPixel(Pixel second, float factor = 0.5f)
	{
		this->copyColor(Pixel::MixPixels(*this, second, factor));
	}

	void setColor(unsigned int red, unsigned int green, unsigned int blue) { this->setColor(sf::Color(red, green, blue)); }
	void setColor(sf::Color color)
	{
		this->color = color;
	}

	sf::Color getColor()
	{
		return this->color;
	}
};