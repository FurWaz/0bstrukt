#pragma once
#include <SFML/Audio.hpp>
#include "Drawable.h"
#include "Screen.h"
#include "MapCreator.h"

class Player : public Drawable
{
private:
	static Player* currentPlayer;
	float speed = Common::BLOCK_SIZE * 4;
	float moveTimer = 0.f;
	bool falling = false;
	bool gameOver = false;
	sf::Vector2i askedMovement;

	unsigned int animationStep = 0;
	unsigned int direction = 0;
	float animationDelay = 0.f;

	sf::SoundBuffer soundbuffer;
	sf::Sound sound;

	void init()
	{
		this->setSprite(Sprite("./resources/player.png", sf::Vector2u(8, 16)));
		Player::currentPlayer = this;

		soundbuffer.loadFromFile("./resources/walk.wav");
		sound.setBuffer(soundbuffer);
	}

public:
	static Player* getCurrentPlayer()
	{
		return Player::currentPlayer;
	}

	Player() : Drawable(sf::Vector2i(0, 0), sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE * 2)) { this->init(); }
	Player(sf::Vector2i p) : Drawable(p, sf::Vector2i(Common::BLOCK_SIZE, Common::BLOCK_SIZE * 2)) { this->init(); }

	void update(float dt)
	{
		Map* map = Map::getCurrentMap();
		if (map->getTile(this->getCurrentBlock()).getTileType() == MapType::HOLE)
		{
			if (map->getProp(getCurrentBlock()) != nullptr)
			{
				this->falling = false;
			}
			else 
			{
				if (!this->falling && !this->gameOver);
				{
					this->falling = true;
				}
			}
		}

		Prop* p = map->getProp(this->getCurrentBlock());
		if (p != nullptr && p->getType() != MapProp::STONE)
		{
			p->action();
			if (p->getType() == MapProp::FLOWER)
			{
				MapCreator::LoadNextGameMap();
				Screen::getCurrentScreen()->setTargetScene();
				this->moveTo(0, 1);
			}
		}

		askedMovement.x = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		askedMovement.y = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		if (askedMovement.x != 0) askedMovement.y = 0;

		if (askedMovement.x == 0 && askedMovement.y == 0)
		{
			animationStep = 0;
			sound.stop();
		}
		else
		{
			if (!sound.Playing || sound.Stopped)
				sound.play();
		}

		if (!this->falling) this->moveTimer += dt;
		if (this->moveTimer >= 1 / this->speed && (askedMovement.x != 0 || askedMovement.y != 0))
		{
			this->moveTimer = 0;
			this->moveBy(askedMovement.x, askedMovement.y);
		}

		this->animationDelay += dt;
		if (animationDelay > 0.1f)
		{
			animationStep = (animationStep + 1) % 4;
			animationDelay = 0.f;
		}

		if (this->falling)
		{
			this->moveBy(0, 1);
			sf::IntRect rect = Screen::getCurrentScreen()->getSceneRect();
			if (this->position.y > rect.top + rect.height)
			{
				this->falling = false;
				this->moveTo(0, 0);
				this->gameOver = true;
			}
		}

		if (askedMovement.x > 0) direction = 2;
		if (askedMovement.x < 0) direction = 1;
		if (askedMovement.y > 0) direction = 3;
		if (askedMovement.y < 0) direction = 0;

		this->sprite.setCurrentTile(sf::Vector2u(animationStep, direction));

		Common::playerPosition = (sf::Vector2i) this->getCurrentBlock();
	}

	bool isFalling()
	{
		return this->falling;
	}

	void setFalling(bool state)
	{
		this->falling = state;
	}

	void render(float dt)
	{
		renderOnScene(Scene::getCurrentScene());
	}

	bool isGameOver()
	{
		return this->gameOver;
	}

	void setGameOver(bool s)
	{
		this->gameOver = s;
	}

	void moveBy(int x, int y) { this->moveBy(sf::Vector2i(x, y)); }
	void moveBy(sf::Vector2i m)
	{
		Map* map = Map::getCurrentMap();
		sf::Vector2i origin = getOrigin();
		Common::playerPosition = origin;

		bool cantGoUp = false;
		bool cantGoDown = false;
		bool cantGoLeft = false;
		bool cantGoRight = false;

		// check for movable blocks
		sf::Vector2i acts[] =
		{
			sf::Vector2i(0, 0), sf::Vector2i(0, -2),
			sf::Vector2i(getSize().x / 2 - 1, 0), sf::Vector2i(-getSize().x / 2 - 1, 0),
		};
		bool* mvts[] = { &cantGoDown, &cantGoUp, &cantGoRight, &cantGoLeft };

		for (unsigned int i = 0; i < 4; i++)
		{
			sf::Vector2u blockPos = getBlockAt(origin + acts[i]);
			Prop* p = map->getProp(blockPos);
			if (p != nullptr)
			{
				if (p->getType() == MapProp::STONE)
				{
					if (map->getTile(blockPos).getTileType() != MapType::HOLE)
					{
						*mvts[i] = true;
						p->action();
					}
				}
			}
		}

		// check for collisions
		bool movePossible = true;
		sf::Vector2i pts[] =
		{
			sf::Vector2i(getSize().x / 2 - 1, 0), sf::Vector2i(getSize().x / 2, -1), // bottom-right, middle right
			sf::Vector2i(-getSize().x / 2, 0), sf::Vector2i(-getSize().x / 2 - 1, -1), // bottom-left, middle left
			sf::Vector2i(getSize().x / 2 - 1, -3), sf::Vector2i(getSize().x / 2, -2), // top-right, middle right
			sf::Vector2i(-getSize().x / 2, -3), sf::Vector2i(-getSize().x / 2 - 1, -2), // top-left, middle left
		};

		cantGoUp |=    map->getTile(getBlockAt(origin + pts[4])).shouldCollide() || map->getTile(getBlockAt(origin + pts[6])).shouldCollide();
		cantGoDown |=  map->getTile(getBlockAt(origin + pts[0])).shouldCollide() || map->getTile(getBlockAt(origin + pts[2])).shouldCollide();
		cantGoLeft |=  map->getTile(getBlockAt(origin + pts[3])).shouldCollide() || map->getTile(getBlockAt(origin + pts[7])).shouldCollide();
		cantGoRight |= map->getTile(getBlockAt(origin + pts[1])).shouldCollide() || map->getTile(getBlockAt(origin + pts[5])).shouldCollide();

		movePossible = (m.y > 0 && !cantGoDown) || (m.y < 0 && !cantGoUp) || (m.x > 0 && !cantGoRight) || (m.x < 0 && !cantGoLeft);
		
		if (movePossible || this->falling) Entity::moveBy(m);
	}
};