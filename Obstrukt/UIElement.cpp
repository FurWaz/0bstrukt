#include "UIElement.h"

bool UIElement::collides(sf::Vector2i p)
{
	return p.x >= this->position.x && p.x < this->position.x + this->size.x
		&& p.y >= this->position.y && p.y < this->position.y + this->size.y;
}

void UIElement::onHover(bool state)
{
	this->hovered = state;
}

void UIElement::onClick(bool state)
{
	this->clicked = state;
}

bool UIElement::isHovered()
{
	return this->hovered;
}

bool UIElement::isClicked()
{
	return this->clicked;
}