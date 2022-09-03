#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Scene.h"

class Drawable: public Entity
{
protected:
	Sprite sprite;

public:
	Drawable(): Entity() {}
	Drawable(sf::Vector2i p) : Entity(p) {}
	Drawable(sf::Vector2i p, sf::Vector2i s) : Entity(p, s) {}
	Drawable(sf::Vector2i p, sf::Vector2i s, Sprite r) : Entity(p, s) 
	{
		this->setSprite(r);
	}

	void setSprite(Sprite r)
	{
		this->sprite = r;
	}

	void renderOnScene(Scene* scene)
	{
		unsigned int spriteW = this->sprite.getWidth();
		unsigned int spriteH = this->sprite.getHeight();
		unsigned int shiftX = 0; //  spriteW / 2;
		unsigned int shiftY = 0; // spriteH - Common::BLOCK_SIZE / 2;

		for (int x = 0; x < spriteW; x++)
		{
			for (int y = 0; y < spriteH; y++)
			{
				Pixel* p = scene->getPixelAt(this->position.x + x - shiftX, this->position.y + y - shiftY);
				if (p == nullptr) continue;

				sf::Color imgColor = this->sprite.getPixelAt(x, y);
				p->MixPixel(Pixel(imgColor), imgColor.a);
			}
		}
	}
	
	void render(float dt)
	{
		renderOnScene(Scene::getCurrentScene());
	}
};

