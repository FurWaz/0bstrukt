#include "Map.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Map* Map::currentMap = nullptr;

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
	// get map size and add the maptiles
	sf::Vector2u mapSize(0, 0);

	std::vector<std::string> mapData = Common::splitString(d, ';');

	std::vector<std::string> lines = Common::splitString(mapData[0], '\n');
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
			this->tiles[i * mapSize.x + j] = MapTile( type, sf::Vector2i(j * Common::BLOCK_SIZE, i * Common::BLOCK_SIZE) );
		}
	}

	this->size = mapSize;

	if (this->scene != nullptr)
		delete this->scene;
	this->scene = new Scene(sf::Vector2u(mapSize.x * Common::BLOCK_SIZE, mapSize.y * Common::BLOCK_SIZE));

	// get the props and add them
	if (mapData.size() > 1)
	{
		std::vector<std::string> props = Common::splitString(mapData[1], '\n');

		for (int i = 0; i < props.size(); i++)
		{
			std::string prop = props.at(i);
			std::vector<std::string> parts = Common::splitString(prop, '.');
			this->addProp(new Prop(atoi(parts.at(0).c_str()), sf::Vector2i(atoi(parts.at(1).c_str()) * Common::BLOCK_SIZE, atoi(parts.at(2).c_str()) * Common::BLOCK_SIZE)));
		}
	}

	return true;
}

void Map::update(float dt)
{
	bool clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	sf::Vector2i mapMousePos = Common::ScreenToSceneCoord(sf::Mouse::getPosition());
	for (std::vector<UIElement*>::iterator i = this->UIElements.begin(); i != this->UIElements.end(); i++)
	{
		UIElement* e = (*i);
		if (e->collides(mapMousePos))
		{
			if (!e->isHovered()) e->onHover(true);
			if (clicked)
			{
				if (!e->isClicked()) e->onClick(true);
			}
			else
				if (e->isClicked()) e->onClick(false);
		}
		else
		{
			if (e->isHovered()) e->onHover(false);
			if (e->isClicked()) e->onClick(false);
		}
		e->update(dt);
	}

	for (std::vector<Prop*>::iterator i = this->props.begin(); i != this->props.end(); i++)
	{
		(*i)->update(dt);
		if ((*i)->shouldBeRemoved())
		{
			try {
//				this->props.erase(i);
			}
			catch (std::exception e) {}
		}
	}
}

void Map::render(float dt)
{
	unsigned int length = this->tiles.size();
	for (int i = 0; i < length; i++)
	{
		this->tiles[i].render(dt);
	}

	length = this->props.size();
	for (int i = 0; i < length; i++)
	{
		Prop* p = this->props.at(i);
		if (!p->shouldBeRemoved())
			p->render(dt);
	}
	
	length = this->UIElements.size();
	for (int i = 0; i < length; i++)
	{
		this->UIElements.at(i)->render(dt);
	}
}

void Map::addUIElement(UIElement* el)
{
	this->UIElements.push_back(el);
}

void Map::addProp(Prop* p)
{
	this->props.push_back(p);
}

bool Map::hasPlayer()
{
	return this->playable;
}

void Map::setPlayable(bool s)
{
	this->playable = s;
}

MapTile Map::getTile(sf::Vector2u c)
{
	if (c.x < 0 || c.y < 0 || c.x >= this->size.x || c.y >= this->size.y)
		return MapTile(404);
	return this->tiles.at(c.x + c.y * this->size.x);
}

Prop* Map::getProp(sf::Vector2u c)
{
	int index = -1;
	for (int i = 0; i < this->props.size(); i++)
	{
		Prop* p = this->props.at(i);
		if (c.x == p->getPosition().x / Common::BLOCK_SIZE && c.y == p->getPosition().y / Common::BLOCK_SIZE)
			return p;
	}

	return nullptr;
}