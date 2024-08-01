#include "Enemy.h"
#include <iostream>


Enemy::Enemy()
{
	setSize(sf::Vector2f(50, 50));
	setPosition(100, 100);
}


Enemy::Enemy(int type)
{
	setSize(sf::Vector2f(50, 50));
	setPosition(200, 200);
	setFillColor(sf::Color::Red);
	if (type == 1)
	{

	}
	else
	{

	}
}


Enemy::~Enemy()
{

}
