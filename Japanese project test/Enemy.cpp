#include "Enemy.h"
#include <iostream>


Enemy::Enemy()
{
	setSize(sf::Vector2f(50, 50));
	setPosition(100, 100);
	img.loadFromFile("./Sprites/zombies/basic.png");
	sprite.setTexture(img);
	sprite.setScale(3.125,3.125);
	sprite.setPosition(getPosition().x, getPosition().y);
}


Enemy::Enemy(int type)
{
	setSize(sf::Vector2f(50, 50));
	setPosition(200, 200);
	setFillColor(sf::Color::Red);
	if (type == 1)
	{
		img.loadFromFile("./Sprites/zombies/basic.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
	}
	else
	{

	}
}


Enemy::~Enemy()
{

}


void Enemy::print(sf::RenderWindow &window)
{
	window.draw(sprite);
}
