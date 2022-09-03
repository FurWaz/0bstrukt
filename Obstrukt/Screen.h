#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Common.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#pragma comment(lib, "User32")
#pragma comment(lib, "Gdi32")

class Screen
{
private:
	static Screen* currentScreen;

	sf::Vector2u size;
	sf::String name;
	sf::RenderWindow window;
	sf::Color backgroundColor;

	sf::Vector2f position;
	sf::Vector2i monitorSize;
	sf::Vector2f targetPosition;

	float blockToPixelRatio = 4.f;
	sf::Vector2u windowDefinition;

	Scene* targetScene = nullptr;
	sf::FloatRect sceneScreenRect;
	sf::Vector2u monitorMargins;

	sf::FloatRect windowScenePart;
	sf::Clock clock;

	unsigned int maxDefinition = 64u;
	float windowSpeed = 6.f;

	bool setWindowPosition(sf::Vector2i pos)
	{
		if (pos.x == this->position.x && pos.y == this->position.y)
			return false;

		this->windowScenePart.left = (pos.x - this->sceneScreenRect.left) / blockToPixelRatio + 0.5f;
		this->windowScenePart.top = (pos.y - this->sceneScreenRect.top) / blockToPixelRatio + 0.5f;
		return true;
	}

	void setShape()
	{
		HRGN hRegion = CreateRectRgn(0, 0, window.getSize().x, window.getSize().y);

		for (unsigned int y = 0; y < windowDefinition.y; y++)
		{
			for (unsigned int x = 0; x < windowDefinition.x; x++)
			{
				bool makeItTrans = false;
				Pixel* p = targetScene->getPixelAt(windowScenePart.left + x, windowScenePart.top + y);
				if (p == nullptr) makeItTrans = true;
				else
				{
					sf::Color c = p->getColor();
					makeItTrans = c.r + c.g + c.b == 0;
				}
				if (makeItTrans)
				{
					HRGN hRegionPixel = CreateRectRgn(x * blockToPixelRatio, y * blockToPixelRatio, x * blockToPixelRatio + blockToPixelRatio, y * blockToPixelRatio + blockToPixelRatio);
					CombineRgn(hRegion, hRegion, hRegionPixel, RGN_XOR);
					DeleteObject(hRegionPixel);
				}
			}
		}

		SetWindowRgn(window.getSystemHandle(), hRegion, true);
		DeleteObject(hRegion);
	}

public:
	static Screen* getCurrentScreen()
	{
		return Screen::currentScreen;
	}

	Screen(sf::String name)
	{
		currentScreen = this;

		::ShowWindow(GetConsoleWindow(), SW_HIDE);
		this->monitorMargins = sf::Vector2u(100, 200);
		this->name = name;

		sf::VideoMode monitor = sf::VideoMode::getDesktopMode();
		this->monitorSize = sf::Vector2i(monitor.width, monitor.height);

		window.setVerticalSyncEnabled(true);

		this->position = sf::Vector2f(window.getPosition().x, window.getPosition().y);
		backgroundColor = sf::Color(0, 0, 0, 0);

		this->setPosition(0, 0);
		clock.restart();
	}

	sf::IntRect getSceneRect()
	{
		return (sf::IntRect)windowScenePart;
	}

	bool isOpen()
	{
		return window.isOpen();
	}

	void close()
	{
		window.close();
	}

	void setPosition(float x, float y) { this->setPosition(sf::Vector2f(x, y)); }
	void setPosition(sf::Vector2f pos)
	{
		if (pos.x == this->position.x && pos.y == this->position.y)
			return;

		this->position = pos;
	}

	void setClampedPosition(float x, float y) { this->setClampedPosition(sf::Vector2f(x, y)); }
	void setClampedPosition(sf::Vector2f pos)
	{
		// clamp the position
		pos.x = Common::clamp(pos.x, sceneScreenRect.left, sceneScreenRect.width + sceneScreenRect.left - (float)this->size.x);
		pos.y = Common::clamp(pos.y, sceneScreenRect.top, sceneScreenRect.height + sceneScreenRect.top - (float)this->size.y);

		this->setPosition(pos.x, pos.y);
	}

	void setTargetPosition(float x, float y) { this->setTargetPosition(sf::Vector2f(x, y)); }
	void setTargetPosition(sf::Vector2f pos)
	{
		sf::Vector2f windowFromMouseShift( (this->windowDefinition.x / 2) * blockToPixelRatio, (this->windowDefinition.y / 2) * blockToPixelRatio);
		this->targetPosition = sf::Vector2f(pos.x - windowFromMouseShift.x, pos.y - windowFromMouseShift.y);
	}

	void setSceneTargetPosition(float x, float y) { this->setSceneTargetPosition(sf::Vector2f(x, y)); }
	void setSceneTargetPosition(sf::Vector2i pos) { this->setSceneTargetPosition(sf::Vector2f(pos.x, pos.y)); }
	void setSceneTargetPosition(sf::Vector2f pos)
	{
		this->setTargetPosition(this->sceneScreenRect.left + blockToPixelRatio * pos.x, this->sceneScreenRect.top + blockToPixelRatio * pos.y);
	}

	void setTargetScene(Scene* scene = Scene::getCurrentScene())
	{
		this->targetScene = scene;
		float monitorRatio = ((monitorSize.x - monitorMargins.x) / (float) (monitorSize.y - monitorMargins.y));
		float sceneRatio = (targetScene->size.x / (float) targetScene->size.y);
		float sceneScale = 1.f;

		// calculate scene size based on it's ratio and the available monitor display zone (monitor size - margins)
		if (monitorRatio > sceneRatio)
			sceneScale = (monitorSize.y - monitorMargins.y) / (float) targetScene->size.y;
		else
			sceneScale = (monitorSize.x - monitorMargins.x) / (float) targetScene->size.x;

		// calculate the scene display position on screen (it's top left corner)
		blockToPixelRatio = sceneScale;
		Common::BLOCK_2_PIXEL = blockToPixelRatio;

		sceneScreenRect.width = targetScene->size.x * blockToPixelRatio;
		sceneScreenRect.height = targetScene->size.y * blockToPixelRatio;
		sceneScreenRect.left = (monitorSize.x - sceneScreenRect.width) / 2.f;
		sceneScreenRect.top = (monitorSize.y - sceneScreenRect.height) / 2.f;

		Common::sceneScreenRect = sceneScreenRect;

		// update the window to match the new scene
		this->updateWindowSize();
	}

	void updateWindowSize()
	{
		if (targetScene != nullptr)
		{
			this->windowDefinition = sf::Vector2u(std::min(targetScene->size.x, this->maxDefinition), std::min(targetScene->size.y, this->maxDefinition));
		}
		else this->windowDefinition = sf::Vector2u(this->maxDefinition, this->maxDefinition);

		this->windowScenePart.width = this->windowDefinition.x;
		this->windowScenePart.height = this->windowDefinition.y;

		this->size = sf::Vector2u(windowDefinition.x * blockToPixelRatio, windowDefinition.y * blockToPixelRatio);
		window.create(sf::VideoMode(this->size.x, this->size.y), this->name, sf::Style::None);

		HWND hwnd = window.getSystemHandle();
		SetWindowLongPtrW(hwnd, GWL_EXSTYLE, GetWindowLongPtrW(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	}

	void processEvents()
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
				// CLOSE WINDOW EVENT
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::F4 && ev.key.alt)
					window.close();
				break;


				// CLOSE WINDOW EVENT
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}

	float update()
	{
		float dt = clock.restart().asSeconds();
		if (this->targetPosition != this->position)
		{
			sf::Vector2f shift((this->targetPosition.x - this->position.x) * dt * this->windowSpeed, (this->targetPosition.y - this->position.y) * dt * this->windowSpeed);
			setClampedPosition(this->position + shift);
		}
		return dt;
	}

	void render()
	{
		window.clear(this->backgroundColor);

		sf::Vector2i newPosition = sf::Vector2i(
			std::round(this->position.x / blockToPixelRatio) * blockToPixelRatio,
			std::round(this->position.y / blockToPixelRatio) * blockToPixelRatio
		);
		bool shouldUpdatePosition = this->setWindowPosition(newPosition);

		if (this->targetScene != nullptr) // render current scene
		{
			int nbBlocks = this->windowDefinition.x * this->windowDefinition.y;
			sf::RectangleShape rect;
			for (int i = 0; i < nbBlocks; i++)
			{
				Pixel* curPixel = targetScene->getPixelAt(i % this->windowDefinition.x + this->windowScenePart.left, i / this->windowDefinition.x + this->windowScenePart.top);
				if (curPixel == nullptr) continue;
				rect.setSize(sf::Vector2f(blockToPixelRatio, blockToPixelRatio));
				rect.setPosition(i % windowDefinition.x * blockToPixelRatio, i / windowDefinition.x * blockToPixelRatio);
				rect.setFillColor(curPixel->getColor());
				window.draw(rect);
			}
		}

		if (!Map::getCurrentMap()->hasPlayer() || true) setShape();
		window.display();
		if (shouldUpdatePosition) window.setPosition(newPosition);
	}
};