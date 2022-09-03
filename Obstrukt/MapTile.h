#pragma once
#include "Drawable.h"

class MapType
{
public:
	static const unsigned int UNKNOWN = 404;
	static const unsigned int HOLE = 9;
	static const unsigned int GRASS = 0;
	static const unsigned int DIRT = 1;
	static const unsigned int ROCK = 2;
	static const unsigned int STONE = 3;
	static const unsigned int METAL_CHUNK = 4;
	static const unsigned int WOOD = 5;
	static const unsigned int PLANK = 6;
	static const unsigned int WOOD_LOG = 7;
	static const unsigned int WOOD_CHUNK = 8;

	std::string getTypeName(unsigned int t)
	{
		std::string res;
		switch (t)
		{
			case GRASS: res = "GRASS"; break;
			case DIRT: res = "DIRT"; break;
			case ROCK: res = "ROCK"; break;
			case STONE: res = "STONE"; break;
			case METAL_CHUNK: res = "METAL CHUNK"; break;
			case WOOD: res = "WOOD"; break;
			case PLANK: res = "PLANK"; break;
			case WOOD_LOG: res = "WOOD LOG"; break;
			case WOOD_CHUNK: res = "WOOD CHUNK"; break;
			default: res = "HOLE"; break;
		}
		return res;
	}

	std::vector<unsigned int> getTypes()
	{
		std::vector<unsigned int> v;
		for (int i = 0; i < 9; i++)
			v.push_back(i);
		v.push_back(HOLE);
		return v;
	}
};

class MapProp
{
public:
	static const unsigned int UNKNOWN = 404;
	static const unsigned int STONE = 0;
	static const unsigned int BRICK = 1;
	static const unsigned int DRY_TREE = 2;
	static const unsigned int TREE = 3;
	static const unsigned int ROCK = 6;
	static const unsigned int GRASS = 7;
	static const unsigned int FLOWER = 8;
	static const unsigned int ALGA = 9;
	static const unsigned int COIN = 12;
	static const unsigned int BALL = 19;

	static unsigned int getAnimationLength(unsigned int t)
	{
		unsigned int res = 1;
		switch (t)
		{
			case ALGA: res = 3; break;
			case COIN: res = 6; break;
			case BALL: res = 8; break;
		}
		return res;
	}

	static float getAnimationSpeed(unsigned int t)
	{
		float res = 1.f;
		switch (t)
		{
		case ALGA: res = 2.f; break;
		case COIN: res = 8.f; break;
		case BALL: res = 10.f; break;
		}
		return res;
	}

	std::string getPropName(unsigned int t)
	{
		std::string res = "UNKNOWN";
		switch (t)
		{
			case STONE: res = "STONE"; break;
			case BRICK: res = "BRICK"; break;
			case DRY_TREE: res = "DRY TREE"; break;
			case TREE: res = "TREE"; break;
			case ROCK: res = "ROCK"; break;
			case GRASS: res = "GRASS"; break;
			case FLOWER: res = "FLOWER"; break;
			case ALGA: res = "ALGA"; break;
			case COIN: res = "COIN"; break;
			case BALL: res = "BALL"; break;
		}
		return res;
	}

	std::vector<unsigned int> getProps()
	{
		std::vector<unsigned int> v;
		for (int i = 0; i < 4; i++) v.push_back(i);
		for (int i = 6; i < 10; i++) v.push_back(i);
		v.push_back(12); v.push_back(19);
		return v;
	}
};

class MapTile : public Drawable
{
private:
	static Sprite MapSprite;

	unsigned int tileIndex;
	bool collides = false;

	void init()
	{
		this->sprite = Sprite::FromSprite(MapTile::MapSprite);
		this->setTileType(tileIndex);
	}

public:
	MapTile() : Drawable(sf::Vector2i(), sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE)), tileIndex(0) { this->init(); }
	MapTile(unsigned int t): Drawable(sf::Vector2i(), sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE)), tileIndex(t) { this->init(); }
	MapTile(unsigned int t, sf::Vector2i p) : Drawable(p, sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE)), tileIndex(t) { this->init(); }

	void setTileType(unsigned int type)
	{
		this->collides = type == MapType::WOOD_LOG || type == MapType::WOOD_CHUNK || type == MapType::METAL_CHUNK;
		this->tileIndex = type;
		this->sprite.setCurrentTile(this->tileIndex);
	}

	unsigned int getTileType()
	{
		return this->tileIndex;
	}

	bool shouldCollide()
	{
		return this->collides;
	}

	void render(float dt)
	{
		this->renderOnScene(Scene::getCurrentScene());
	}
};