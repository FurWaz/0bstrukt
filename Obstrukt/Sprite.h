#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Image.h"

class Sprite
{
private:
	Image img;
	sf::String path;
	sf::Vector2u size;
	sf::Vector2u imgSize;
	sf::Vector2u tilesSize;
	sf::Vector2u currentTile;

	void updateDims()
	{
		this->imgSize = img.getSize();
		this->tilesSize = sf::Vector2u(imgSize.x / size.x - 1, imgSize.y / size.y - 1);
		this->setCurrentTile(this->currentTile);
	}

public:
	static Sprite FromSprite(Sprite s)
	{
		Sprite sp(s.size);
		sp.setImage(s.img);
		return sp;
	}

	Sprite() {}
	Sprite(sf::Vector2u s) : size(s) {}
	Sprite(sf::String p, sf::Vector2u s) : size(s)
	{
		this->setPath(p);
	}

	void setImage(Image i)
	{
		this->img = i;
		updateDims();
	}

	void setPath(sf::String p)
	{
		this->path = p;
		img.loadFromFile(this->path);
		this->updateDims();
	}

	void setCurrentTile(unsigned int index)
	{
		index = std::min(index, (tilesSize.x + 1) * (tilesSize.y + 1) - 1);
		this->currentTile.x = index % (tilesSize.x + 1);
		this->currentTile.y = index / (tilesSize.x + 1);
	}

	void setCurrentTile(sf::Vector2u pos)
	{
		this->currentTile.x = std::min(pos.x, tilesSize.x);
		this->currentTile.y = std::min(pos.y, tilesSize.y);
	}

	sf::Color getPixelAt(int x, int y) { return this->getPixelAt(sf::Vector2u(x, y)); }
	sf::Color getPixelAt(sf::Vector2u coord)
	{
		if (coord.x > this->size.x || coord.y > this->size.y || coord.x < 0 || coord.y < 0)
			return sf::Color::Transparent;

		unsigned int posX = coord.x + currentTile.x * size.x;
		unsigned int posY = coord.y + currentTile.y * size.y;
		if (posX > this->imgSize.x || posY > this->imgSize.y || posX < 0 || posY < 0)
			return sf::Color::Transparent;

		return img.getPixel(posX, posY);
	}

	sf::Vector2u getSize()
	{
		return this->size;
	}

	unsigned int getWidth()
	{
		return this->size.x;
	}

	unsigned int getHeight()
	{
		return this->size.y;
	}

	~Sprite()
	{
		
	}
};