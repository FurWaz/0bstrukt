#include <iostream>
#include <thread>
#include <math.h>

#include "Screen.h"
#include "Player.h"
#include "MapCreator.h"

int main(int argc, char** argv)
{
	Screen window("Obstrukt");

	MapCreator::CreateMenuMap();
	window.setTargetScene();

	Player p(sf::Vector2i(8, 8));

	while (window.isOpen())
	{
		if (p.isGameOver())
		{
			p.setGameOver(false);
			MapCreator::CreateGameOverMap();
			Screen::getCurrentScreen()->setTargetScene();
		}

		Map* map = Map::getCurrentMap();
		window.processEvents();
		if (map->hasPlayer())
			window.setSceneTargetPosition(p.getCenter());
		else window.setTargetPosition((sf::Vector2f)sf::Mouse::getPosition());

		float dt = window.update();
		map->update(dt);

		if (map->hasPlayer())
			p.update(dt);

		Scene::getCurrentScene()->clear();
		if (!p.isFalling()) map->render(dt);

		if (map->hasPlayer())
		{
			p.render(dt);
		}

		if (p.isFalling()) map->render(dt);

		window.render();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	MapCreator::deleteOldMaps();
	delete Map::getCurrentMap();
	
	return 0;
}