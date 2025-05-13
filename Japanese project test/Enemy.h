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
	void move(int x, int y, std::vector<Intaractable*>& rect);

private:
	double xMove = 0, yMove = 0;
	bool disabled = false;
};

