#pragma once
#include "Drawable.h"

class Player : public Drawable
{
private:
	float speed = Common::BLOCK_SIZE * 2;
	float moveTimer = 0.f;
	sf::Vector2i askedMovement;

	void init()
	{
		this->setSprite(Sprite("./resources/player.png", sf::Vector2u(8, 16)));
	}

public:
	Player() : Drawable(sf::Vector2i(0, 0), sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE * 2)) { this->init(); }
	Player(sf::Vector2i p) : Drawable(p, sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE * 2)) { this->init(); }

	void update(float dt)
	{
		askedMovement.x = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		askedMovement.y = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		if (askedMovement.x != 0) askedMovement.y = 0;

		this->moveTimer += dt;
		if (this->moveTimer >= 1 / this->speed && (askedMovement.x != 0 || askedMovement.y != 0))
		{
			this->moveTimer = 0;
			this->moveBy(askedMovement.x, askedMovement.y);
		}
	}

	void render(float dt)
	{
		renderOnScene(Scene::getCurrentScene());
	}
};