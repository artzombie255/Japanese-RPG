#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Intaractable.h"


class Shop : public Intaractable
{
public:
	Shop();
	Shop(int);
	~Shop();


private:
	sf::Font font;
	sf::Text text;
	int currentLine = 0, inputDelay = 0;
};
