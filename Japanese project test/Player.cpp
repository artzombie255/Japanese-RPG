#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>


Player::Player()
{
	setSize(sf::Vector2f(50, 50));
	setOrigin(0, 0);
	setPosition(0, 550);
	setFillColor(sf::Color::Green);
}


Player::~Player()
{
}


//checks if keys are pressed and starts movement
void Player::moveCheck()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		xMove = -3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		xMove = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		yMove = -3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		yMove = 3;
	}
	

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		xMove = 0;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		yMove = 0;
	}
}


//moves player based on pressed keys
void Player::move()
{
	//move
	RectangleShape::move(xMove, yMove);

	if (getPosition().x < 0)
	{
		RectangleShape::setPosition(WINDOWX - 50, getPosition().y);
		xScreen--;
		std::cout << "x: " << xScreen << std::endl;
		std::cout << "y: " << yScreen << std::endl;
	}
	if (getPosition().y < 0)
	{
		RectangleShape::setPosition(getPosition().x, WINDOWY - 50);
		yScreen--;
		std::cout << "x: " << xScreen << std::endl;
		std::cout << "y: " << yScreen << std::endl;
	}
	if (getPosition().x > WINDOWX - 50)
	{
		RectangleShape::setPosition(0, getPosition().y);
		xScreen++;
		std::cout << "x: " << xScreen << std::endl;
		std::cout << "y: " << yScreen << std::endl;
	}
	if (getPosition().y > WINDOWY - 50)
	{
		RectangleShape::setPosition(getPosition().x, 0);
		yScreen++;
		std::cout << "x: " << xScreen << std::endl;
		std::cout << "y: " << yScreen << std::endl;
	}
}


void Player::collision(std::vector<sf::RectangleShape> rect, int type)
{
	sf::FloatRect nextPos;
	for (int i = 0; i < rect.size(); i++)
	{
		sf::FloatRect bounds = rect.at(i).getGlobalBounds();
		sf::FloatRect playerBounds = getGlobalBounds();

		nextPos = playerBounds;

		nextPos.left += xMove;
		nextPos.top += yMove;

		//if (playerBounds.left > wallBounds.left + 25)
			//wallBounds.left++;
		//else if (playerBounds.left + 50 < wallBounds.left)
			//wallBounds.left--;

		if (bounds.intersects(nextPos))
		{
			
		}
	}
}


bool Player::isLost()
{
	return lost;
}


int Player::getScreenX()
{
	return xScreen;
}


int Player::getScreenY()
{
	return yScreen;
}