#pragma once
#include <SFML/System.hpp>
#include "Pixel.h"
#include <iostream>

class Scene
{
private:
	Pixel* pixels;

public:
	sf::Vector2u size;
	unsigned int length;

	Scene(sf::Vector2u size)
	{
		this->size = size;
		this->length = size.x * size.y;
		this->pixels = (Pixel*) malloc(this->length * sizeof(unsigned int));
		for (int i = 0; i < this->length; i++)
			this->pixels[i].setColor(sf::Color::Black);
	}

	Pixel* getPixelAt(unsigned int x, unsigned int y) { return this->getPixelAt(sf::Vector2u(x, y)); }
	Pixel* getPixelAt(sf::Vector2u pos)
	{
		if (pos.x > size.x || pos.y > size.y) return nullptr;
		return &pixels[pos.x + pos.y * size.x];
	}

	Pixel* getPixelsBuffer()
	{
		return pixels;
	}

	~Scene()
	{
		free(pixels);
	}
};