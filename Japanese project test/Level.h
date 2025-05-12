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

	void loadLevel(DoubleSubscriptedArray&, std::string, std::vector<Intaractable*>&, int, int, sf::View&);
	void print(sf::RenderWindow&, DoubleSubscriptedArray&);
	void printF(sf::RenderWindow&, DoubleSubscriptedArray&);
	void updateRoom(int, int);
	bool getInCave() { return inCave; }
	void addWalls(int temp) { totalWalls += temp; }

private:
	bool oneLevelThreeUpdated = false, loaded[9][9], inCave = false;
	int totalWalls = 0;
	sf::RectangleShape rect;
	sf::Texture img, imgF;
	sf::Sprite sprite, foreground;
};