#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Intaractable.h"
#include <vector>
#include "globals.h"


extern const int WINDOWX, WINDOWY;

extern const enum INTERACTIONTYPE
{
	NPC,
	WALL,
	ENEMY
};


class Player : public sf::RectangleShape
{
public:
	Player();
	~Player();

	void moveCheck();
	void move();
	bool collision(std::vector<Intaractable*>&, INTERACTIONTYPE);
	bool isLost();
	int getScreenX();
	int getScreenY();
	void escMenu(sf::RenderWindow&);
	void printEscMenu(sf::RenderWindow&);
	bool getEscMenuOpen();

private:
	int xScreen = 1, yScreen = 3, escDelay = 0, currentMenuSelection = 0;
	double xMove = 0, yMove = 0;
	//left == true, right == false
	bool lost, escMenuOpen = false;
	sf::Vector2i lastScreen = sf::Vector2i(1, 3);

};