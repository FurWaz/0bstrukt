#include <iostream>
#include "Screen.h"
#include <thread>
#include <math.h>

int main(int argc, char** argv)
{
	Screen window("Obstrukt");
	Scene* scene = new Scene(sf::Vector2u(256, 144));
	Scene* scene2 = new Scene(sf::Vector2u(72, 72));
	bool gotoscene2 = true;

	for(int i = 0; i < 628; i++)
		scene->getPixelAt(128 + cos(i / 10.f) * 20, 72 + sin(i / 10.f) * 20)->setColor(sf::Color(
		    128 + cos(i / 10.f) * 127,
			128 + cos(i / 10.f + 418) * 127,
			128 + cos(i / 10.f + 209) * 127
		));

	for (int i = 0; i < 628; i++)
		scene2->getPixelAt(20 + cos(i / 10.f) * 10, 15 + sin(i / 10.f) * 10)->setColor(sf::Color(
			128 + cos(i / 10.f) * 127,
			128 + cos(i / 10.f + 209) * 127,
			128 + cos(i / 10.f + 418) * 127
		));

	window.setTargetScene(scene);

	float time = 0.f;
	while (window.isOpen())
	{
		window.processEvents();
		window.setTargetPosition((sf::Vector2f)sf::Mouse::getPosition());

		time += window.update();
		if (time > 3.f)
		{
			if (gotoscene2) window.setTargetScene(scene2);
			else window.setTargetScene(scene);
			gotoscene2 = !gotoscene2;
			time = 0.f;
			std::cout << "switch to scene " << (gotoscene2 ? "2" : "1") << std::endl;
		}

		window.render();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	delete scene;
	
	return 0;
}