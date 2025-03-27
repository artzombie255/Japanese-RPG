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
	sprite.setPosition(getPosition().x, getPosition().y);
	window.draw(sprite);
}


void Enemy::move(int x, int y, std::vector<Intaractable*>& rect)
{
	//if (0 <= getPosition().x && 551 >= getPosition().x && 0 <= getPosition().y && 551 >= getPosition().y)
	bool boolY = false, boolX = false;
	sf::FloatRect nextPos;
	for (int i = 0; i < rect.size(); i++)
	{
		sf::FloatRect bounds = rect.at(i)->getGlobalBounds();
		sf::FloatRect playerBounds = getGlobalBounds();

		nextPos = playerBounds;

		if (x < getPosition().x)
			nextPos.left += -1;
		else if (x > getPosition().x)
			nextPos.left += 1;
		
		if (bounds.intersects(nextPos))
		{
			boolX = true;
		}

		nextPos = playerBounds;

		if (y < getPosition().y)
			nextPos.top += -1;
		else if (y > getPosition().y)
			nextPos.top += 1;

		if (bounds.intersects(nextPos))
		{
			boolY = true;
		}
	}

	if (boolX == false)
	{
		if (x < getPosition().x)
			RectangleShape::move(-1, 0);
		else if (x > getPosition().x)
			RectangleShape::move(1, 0);
	}

	if (boolY == false)
	{
		if (y < getPosition().y)
			RectangleShape::move(0, -1);
		else if (y > getPosition().y)
			RectangleShape::move(0, 1);
	}
}
