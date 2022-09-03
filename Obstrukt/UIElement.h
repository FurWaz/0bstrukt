#pragma once
#include <SFML/Graphics.hpp>
#include "Drawable.h"

class UIElement : public Drawable
{
private:
	bool clicked = false;
	bool hovered = false;

public:
	void onHover(bool);
	void onClick(bool);

	virtual void update(float) = 0;

	bool isHovered();
	bool isClicked();
	bool collides(sf::Vector2i);
};