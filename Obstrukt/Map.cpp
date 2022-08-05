#include "Map.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

bool Map::loadFromFile(sf::String s)
{
	std::stringstream ss;
	std::ifstream file;
	file.open(s.toAnsiString());

	if (file.fail())
	{
		file.close();
		return false;
	}
	ss << file.rdbuf();
	file.close();

	std::string data = ss.str();

	return this->loadData(data);
}

bool Map::loadData(std::string d)
{
	sf::Vector2u mapSize(0, 0);

	std::vector<std::string> lines = Common::splitString(d, '\n');
	unsigned int nbLines = lines.size();
	mapSize.y = nbLines;

	for (unsigned int i = 0; i < mapSize.y; i++)
	{
		std::vector<std::string> blocks = Common::splitString(lines.at(i), ',');
		if (mapSize.x == 0)
		{
			mapSize.x = blocks.size();
			this->tiles = std::vector<MapTile>(mapSize.x * mapSize.y);
		}
		else if (mapSize.x != blocks.size()) return false;

		for (int j = 0; j < mapSize.x; j++)
		{
			unsigned int type = std::atoi(blocks.at(j).c_str());
			this->tiles[i * mapSize.x + j] = MapTile( type, sf::Vector2i(i * Common::BLOCK_SIZE, j * Common::BLOCK_SIZE) );
		}
	}

	this->size = mapSize;

	if (this->scene != nullptr)
		delete this->scene;
	this->scene = new Scene(sf::Vector2u(mapSize.x * Common::BLOCK_SIZE, mapSize.y * Common::BLOCK_SIZE));

	return true;
}

void Map::render(float dt)
{
	unsigned int length = this->size.x * this->size.y;
	for (int i = 0; i < length; i++)
	{
		this->tiles[i].render(dt);
	}
}