#pragma once
#include "UIElement.h"
#include "Callback.h"

class Button : public virtual UIElement
{
private:
    Callback callback;
    bool callbackCalled = false;

    bool lastHover = false;
    bool lastClick = false;
    unsigned int type;
    unsigned int state;

    void init(sf::Vector2i p = sf::Vector2i(), unsigned int t = TYPE_PLAY)
    {
        this->moveTo(p);
        this->growTo(sf::Vector2i(32, 16));
        this->setSprite(Sprite("./resources/Buttons.png", sf::Vector2u(32, 16)));
        this->setButtonState(STATE_NORMAL);
        this->setButtonType(t);
    }

public:
    static const unsigned int STATE_NORMAL = 0;
    static const unsigned int STATE_HOVERED = 1;
    static const unsigned int STATE_PRESSED = 2;

    static const unsigned int TYPE_PLAY = 0;
    static const unsigned int TYPE_QUIT = 1;
    static const unsigned int TYPE_MENU = 2;
    static const unsigned int TYPE_EDIT = 3;

    Button() { this->init(); }
    Button(sf::Vector2i p) { this->init(p); }
    Button(sf::Vector2i p, void (*c)())
    {
        this->init(p);
        this->setCallback(c);
    }

    Button(sf::Vector2i p, unsigned int t, void (*c)())
    {
        this->init(p, t);
        this->setCallback(c);
    }

    void setButtonState(unsigned int state);
    void setButtonType(unsigned int type);

    void update(float);

    void setCallback(Callback);
};