#include <iostream>
#include <thread>
#include <math.h>

#include "Screen.h"
#include "Player.h"
#include "Map.h"

int main(int argc, char** argv)
{
	Screen window("Obstrukt");
	Scene* scene = new Scene(sf::Vector2u(256, 144));

	Map m("./resources/map.obkt");
	m.getScene()->setAsCurrentScene();
	window.setTargetScene(m.getScene());

	Player p;

	float color_shift = 0;

	while (window.isOpen())
	{
		window.processEvents();
		window.setSceneTargetPosition(p.getCenter());

		float dt = window.update();
		p.update(dt);

		Scene::getCurrentScene()->clear();
		m.render(dt);

		p.render(dt);
		scene->getPixelAt((sf::Vector2u)p.getCenter())->setColor(sf::Color::Red);

		window.render();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	delete scene;
	
	return 0;
}