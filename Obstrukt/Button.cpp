#include "Button.h"

void Button::update(float dt)
{
	bool updateGraphics = false;

	if (lastClick != this->isClicked())
	{
		updateGraphics = true;
		if (!this->callbackCalled && lastClick && !this->isClicked())
		{
			this->callback.call();
			this->callbackCalled = true;
		}
		lastClick = this->isClicked();
	}
	else
	{
		if (this->callbackCalled)
			this->callbackCalled = false;
	}

	if (lastHover != this->isHovered())
	{
		updateGraphics = true;
		lastHover = this->isHovered();
	}

	if (updateGraphics)
		this->setButtonState( lastClick + lastHover );
}

void Button::setCallback(Callback c)
{
	this->callback = c;
}

void Button::setButtonState(unsigned int s)
{
	this->state = s;
	this->sprite.setCurrentTile(sf::Vector2u(this->state, this->type));
}

void Button::setButtonType(unsigned int t)
{
	this->type = t;
	this->sprite.setCurrentTile(sf::Vector2u(this->state, this->type));
}