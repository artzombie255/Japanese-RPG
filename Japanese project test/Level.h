#pragma once
#include "DoubleSubscriptedArray.h"
#include <string.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Level
{
public:
	Level();
	~Level();

	void loadLevel(DoubleSubscriptedArray&, std::string);
	void print(sf::RenderWindow&, DoubleSubscriptedArray&);

private:
	sf::RectangleShape rect;
	sf::Texture img;
	sf::Sprite sprite;
};