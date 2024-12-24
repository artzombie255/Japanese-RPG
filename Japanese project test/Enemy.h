#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Intaractable.h"

class Enemy : public Intaractable
{
public: 
	Enemy();
	Enemy(int);
	~Enemy();

	void print(sf::RenderWindow&);
private:

};

