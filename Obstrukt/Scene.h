#pragma once
#include <SFML/System.hpp>
#include "Pixel.h"
#include <iostream>

class Scene
{
private:
	static Scene* currentScene;

	Pixel* pixels;

public:
	static Scene* getCurrentScene();

	sf::Vector2u size;
	unsigned int length;

	Scene(sf::Vector2u);

	void setAsCurrentScene();

	void clear();

	Pixel* getPixelAt(unsigned int, unsigned int);
	Pixel* getPixelAt(sf::Vector2u);

	Pixel* getPixelsBuffer();

	~Scene();
};