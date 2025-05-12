#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Intaractable.h"

class Enemy : public Intaractable
{
public: 
	Enemy();
	Enemy(int, int, int);
	~Enemy();

	void print(sf::RenderWindow&);
	void move(int, int, std::vector<Intaractable*>&);

private:
	double xMove = 0, yMove = 0;
};

