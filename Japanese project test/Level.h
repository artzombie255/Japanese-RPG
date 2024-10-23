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

	void loadLevel(DoubleSubscriptedArray&, std::string, std::vector<Intaractable*>&);
	void print(sf::RenderWindow&, DoubleSubscriptedArray&);

private:
	bool oneLevelOneUpdated = false;
	sf::RectangleShape rect;
	sf::Texture img;
	sf::Sprite sprite;
};