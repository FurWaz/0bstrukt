#pragma once
#include "UIElement.h"
class Title : public UIElement
{
private:
    void init(sf::Vector2i p = sf::Vector2i(), sf::String name = "Title")
    {
        this->moveTo(p);
        this->growTo(sf::Vector2i(32, 16));
        this->setSprite(Sprite("./resources/"+name+".png", sf::Vector2u(64, 16)));
    }

public:
    Title() { this->init(); }
    Title(sf::Vector2i p) { this->init(p); }
    Title(sf::Vector2i p, sf::String n)
    {
        this->init(p, n);
    }

    void update(float dt) {}
};