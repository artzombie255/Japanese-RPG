#pragma once
#include "DoubleSubscriptedArray.h"
#include <string.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Intaractable.h"


class Level
{
public:
	Level();
	~Level();

	void loadLevel(DoubleSubscriptedArray&, std::string);
	void print(sf::RenderWindow&, DoubleSubscriptedArray&);
	std::vector<Intaractable*> getWalls();

private:
	sf::RectangleShape rect;
	sf::Texture img;
	sf::Sprite sprite;
	std::vector<Intaractable*> wallVec;
};