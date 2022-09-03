#pragma once
#include <SFML/System.hpp>
#include "Common.h"

class Entity
{
private:


protected:
	sf::Vector2i position;
	sf::Vector2i size;
	sf::Vector2i center;

	void init()
	{
		this->calculateCenter();
	}

	void calculateCenter()
	{
		this->center = sf::Vector2i(
			this->position.x + this->size.x / 2,
			this->position.y + this->size.y / 2
		);
	}

	sf::Vector2u getBlockAt(int x, int y) { return this->getBlockAt(sf::Vector2i(x, y)); }
	sf::Vector2u getBlockAt(sf::Vector2i pos)
	{
		return sf::Vector2u(pos.x / Common::BLOCK_SIZE, pos.y / Common::BLOCK_SIZE);
	}

public:
	Entity(): position(sf::Vector2i(0, 0)), size(sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE)) { this->init(); }
	Entity(sf::Vector2i p): position(p), size(sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE)) { this->init(); }
	Entity(sf::Vector2i p, sf::Vector2i s) : position(p), size(s) { this->init(); }

	void moveBy(int x, int y) { this->moveBy(sf::Vector2i(x, y)); }
	void moveBy(sf::Vector2i m)
	{
		this->position += m;
		this->calculateCenter();
	}

	void moveTo(int x, int y) { this->moveTo(sf::Vector2i(x, y)); }
	void moveTo(sf::Vector2i p)
	{
		this->position = p;
		this->calculateCenter();
	}

	void growBy(int x, int y) { this->growBy(sf::Vector2i(x, y)); }
	void growBy(sf::Vector2i s)
	{
		this->size += s;
		this->calculateCenter();
	}

	void growTo(int x, int y) { this->growTo(sf::Vector2i(x, y)); }
	void growTo(sf::Vector2i s)
	{
		this->size = s;
		this->calculateCenter();
	}

	sf::Vector2i getPosition()
	{
		return this->position;
	}

	sf::Vector2i getCenter()
	{
		return this->center;
	}

	sf::Vector2i getSize()
	{
		return this->size;
	}

	void update(float dt)
	{

	}

	sf::Vector2i getOrigin()
	{
		return sf::Vector2i((this->position.x + this->size.x / 2), (this->position.y + this->size.y));
	}

	sf::Vector2u getCurrentBlock()
	{
		return this->getBlockAt(this->getOrigin());
	}
};