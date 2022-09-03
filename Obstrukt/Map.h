#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Scene.h"
#include "MapTile.h"
#include "UIElement.h"
#include "Prop.h"

class Map
{
private:
	static Map* currentMap;

	std::vector<MapTile> tiles;
	Scene* scene = nullptr;
	sf::Vector2u size;

	bool loadData(std::string);
	std::vector<UIElement*> UIElements;
	std::vector<Prop*> props;

	bool playable = false;
	
public:
	static Map* getCurrentMap()
	{
		return currentMap;
	}

	Map() {}
	Map(sf::String p)
	{
		currentMap = this;
		this->loadFromFile(p);
	}
	Map(sf::String p, bool pl): playable(pl)
	{
		currentMap = this;
		this->loadFromFile(p);
	}
	Map(sf::Vector2u s, bool pl = false)
	{
		currentMap = this;

		this->size = s;
		this->setPlayable(pl);
		this->tiles = std::vector<MapTile>(0);

		if (this->scene != nullptr) delete this->scene;
		this->scene = new Scene(sf::Vector2u(this->size.x * Common::BLOCK_SIZE, this->size.y * Common::BLOCK_SIZE));
	}

	void addUIElement(UIElement* el);

	void addProp(Prop* p);

	bool hasPlayer();

	bool loadFromFile(sf::String);

	void update(float dt);

	void render(float);

	void setPlayable(bool);

	MapTile getTile(sf::Vector2u);
	Prop* getProp(sf::Vector2u);

	Scene* getScene()
	{
		return this->scene;
	}

	~Map()
	{
		if (this->scene != nullptr)
			delete this->scene;
	}
};