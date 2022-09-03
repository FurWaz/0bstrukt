#include "Scene.h"

Scene* Scene::currentScene = nullptr;

Scene* Scene::getCurrentScene()
{
	return Scene::currentScene;
}

Scene::Scene(sf::Vector2u size)
{
	currentScene = this;
	this->size = size;
	this->length = size.x * size.y;
	this->pixels = (Pixel*)malloc(this->length * sizeof(unsigned int));
	for (int i = 0; i < this->length; i++)
		this->pixels[i].setColor(sf::Color::Black);
}

void Scene::setAsCurrentScene()
{
	Scene::currentScene = this;
}

void Scene::clear()
{
	for (int i = 0; i < this->length; i++)
		this->pixels[i].setColor(sf::Color::Transparent);
}

Pixel* Scene::getPixelAt(unsigned int x, unsigned int y)
{
	return this->getPixelAt(sf::Vector2u(x, y));
}

Pixel* Scene::getPixelAt(sf::Vector2u coord)
{
	if (coord.x > size.x || coord.y > size.y) return nullptr;
	return &pixels[coord.x + coord.y * size.x];
}

Pixel* Scene::getPixelsBuffer()
{
	return pixels;
}

Scene::~Scene()
{
	try {
		free(pixels);
	} catch (std::exception e) {}
}