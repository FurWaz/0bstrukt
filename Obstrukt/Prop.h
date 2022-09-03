#pragma once
#include "Drawable.h"
#include "MapTile.h"

class Prop : public Drawable
{
private:
	float animationSpeed = 8.f;
	float animationDelay = 0.f;
	bool shouldRemove = false;
	unsigned int tileShift = 0;
	unsigned int type = 0;

	static const float PI;

protected:
	void init(unsigned int t, sf::Vector2i p)
	{
		this->type = t;
		this->animationSpeed = MapProp::getAnimationSpeed(this->type);
		this->moveTo(p);
		this->setSprite(Sprite("./resources/Props.png", sf::Vector2u(8, 8)));
		this->sprite.setCurrentTile(t);
	}

public:
	Prop() {}
	Prop(unsigned int t): type(t) {}
	Prop(unsigned int t, sf::Vector2i p) { this->init(t, p); }

	bool shouldBeRemoved()
	{
		return this->shouldRemove && this->animationDelay >= 1.f / animationDelay;
	}

	void update(float dt)
	{
		animationDelay += dt;
		if ((animationDelay >= 1.f / animationSpeed) && !this->shouldRemove)
		{
			animationDelay -= 1.f / animationSpeed;
			this->tileShift = (this->tileShift + 1) % MapProp::getAnimationLength(this->type);
			this->sprite.setCurrentTile(this->type + this->tileShift);
		}
	}

	unsigned int getType()
	{
		return this->type;
	}

	void action()
	{
		if (this->shouldRemove) return;

		if (this->type == MapProp::COIN)
		{
			this->shouldRemove = true;
			this->animationDelay = 0;
			this->sprite.setCurrentTile(this->type + MapProp::getAnimationLength(this->type));
		}

		if (this->type == MapProp::STONE)
		{
			sf::Vector2i distToPlayer = Common::playerPosition - ( this->position + sf::Vector2i(Common::BLOCK_SIZE / 2, Common::BLOCK_SIZE / 2) );
			if (abs(distToPlayer.x) > abs(distToPlayer.y))
			{
				if (distToPlayer.x > 0)
					this->moveBy(-Common::BLOCK_SIZE, 0);
				else this->moveBy(Common::BLOCK_SIZE, 0);
			}
			else
			{
				if (distToPlayer.y > 0)
					this->moveBy(0, -Common::BLOCK_SIZE);
				else this->moveBy(0, Common::BLOCK_SIZE);
			}	
		}
	};
};