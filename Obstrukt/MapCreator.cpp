#include "MapCreator.h"
#include "Button.h"
#include "Title.h"
#include "Screen.h"

std::vector<Map*> MapCreator::deletedMaps;
int MapCreator::levelIndex = 0;

Map* MapCreator::CreateMenuMap()
{
	saveMapToDeleted();

	Map* res = new Map(sf::Vector2u(8, 8), false);

	res->addUIElement(new Title(
		sf::Vector2i(0, 0),
		"Title"
	));

	res->addUIElement(new Button(
		sf::Vector2i(Common::BLOCK_SIZE * 2, Common::BLOCK_SIZE * 3),
		Button::TYPE_PLAY,
		[]() {
			MapCreator::LoadGameMap(0);
			Screen::getCurrentScreen()->setTargetScene();
		}
	));

	/*
	res->addUIElement(new Button(
		sf::Vector2i(Common::BLOCK_SIZE * 4, Common::BLOCK_SIZE * 3),
		Button::TYPE_EDIT,
		[]() {
			MapCreator::createEditorMap();
			Screen::getCurrentScreen()->setTargetScene();
		}
	));
	*/

	res->addUIElement(new Button(
		sf::Vector2i(Common::BLOCK_SIZE * 2, Common::BLOCK_SIZE * 6),
		Button::TYPE_QUIT,
		[]() { Screen::getCurrentScreen()->close(); }
	));

	return res;
}

Map* MapCreator::CreateGameOverMap()
{
	saveMapToDeleted();

	Map* res = new Map(sf::Vector2u(8, 8), false);

	res->addUIElement(new Button(
		sf::Vector2i(Common::BLOCK_SIZE * 2, Common::BLOCK_SIZE * 4),
		Button::TYPE_MENU,
		[]() {
			MapCreator::CreateMenuMap();
			Screen::getCurrentScreen()->setTargetScene();
		}
	));

	res->addUIElement(new Title(
		sf::Vector2i(0, 0),
		"GameOver"
	));

	return res;
}

Map* MapCreator::CreateWinMap()
{
	saveMapToDeleted();

	Map* res = new Map(sf::Vector2u(8, 8), false);

	res->addUIElement(new Button(
		sf::Vector2i(Common::BLOCK_SIZE * 2, Common::BLOCK_SIZE * 4),
		Button::TYPE_MENU,
		[]() {
			MapCreator::CreateMenuMap();
			Screen::getCurrentScreen()->setTargetScene();
		}
	));

	res->addUIElement(new Title(
		sf::Vector2i(0, 0),
		"Win"
	));

	return res;
}

Map* MapCreator::createEditorMap()
{
	saveMapToDeleted();
	
	Map* res = new Map(sf::Vector2u(8, 8), false);

	return res;
}

Map* MapCreator::LoadGameMap(int index)
{
	saveMapToDeleted();
	levelIndex = index;

	Map* res = new Map(sf::Vector2u(1, 1), true);
	if (!res->loadFromFile("./resources/" + std::to_string(index) + ".obkt"))
		return nullptr;
	return res;
}

Map* MapCreator::LoadNextGameMap()
{
	Map* map = LoadGameMap(levelIndex + 1);
	if (map == nullptr)
		map = MapCreator::CreateWinMap();
	return map;
}

void MapCreator::deleteOldMaps()
{
	for (int i = 0; i < deletedMaps.size(); i++)
	{
		delete deletedMaps.at(i);
	}
}

void MapCreator::saveMapToDeleted()
{
	deletedMaps.push_back(Map::getCurrentMap());
}