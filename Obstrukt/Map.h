#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "MapTile.h"

class Map
{
private:
	std::vector<MapTile> tiles;
	Scene* scene = nullptr;
	sf::Vector2u size;

	bool loadData(std::string);

public:
	Map() {}
	Map(sf::String p)
	{
		this->loadFromFile(p);
	}

	bool loadFromFile(sf::String);

	void render(float);

	Scene* getScene()
	{
		return this->scene;
	}
};