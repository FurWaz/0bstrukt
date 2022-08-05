#pragma once
#include "Drawable.h"

class MapType
{
public:
	static const unsigned int GRASS_DARK = 0;
	static const unsigned int STONE_DARK = 13;
	static const unsigned int GRASS_LIGHT = 23;
	static const unsigned int STONE_LIGHT = 33;
	static const unsigned int DIRT = 16;
	static const unsigned int FLOWERS_YELLOW = 1;
	static const unsigned int FLOWERS_GREEN = 2;
	static const unsigned int FLOWERS_RED = 3;
	static const unsigned int LEAVES = 25;
	static const unsigned int PLANKS = 58;
	static const unsigned int WOOD_DARK = 7;
	static const unsigned int WOOD_LIGHT = 29;
	static const unsigned int CHUNK_DARK = 27;
	static const unsigned int CHUNK_LIGHT = 32;
};

class MapTile : public Drawable
{
private:
	static Sprite MapSprite;

	unsigned int tileIndex;

	void init()
	{
		this->sprite = Sprite::FromSprite(MapTile::MapSprite);
		this->setTileType(tileIndex);
		std::cout << "sprite size " << sprite.getSize().x << "x" << sprite.getSize().y << std::endl;
	}

public:
	MapTile() : Drawable(sf::Vector2i(), sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE)), tileIndex(0) { this->init(); }
	MapTile(unsigned int t): Drawable(sf::Vector2i(), sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE)), tileIndex(t) { this->init(); }
	MapTile(unsigned int t, sf::Vector2i p) : Drawable(p, sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE)), tileIndex(t) { this->init(); }

	void setTileType(unsigned int type)
	{
		this->tileIndex = type;
		this->sprite.setCurrentTile(this->tileIndex);
	}

	unsigned int getTileType()
	{
		return this->tileIndex;
	}

	void render(float dt)
	{
		this->renderOnScene(Scene::getCurrentScene());
	}
};