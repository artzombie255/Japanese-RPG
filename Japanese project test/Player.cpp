#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>


Player::Player()
{
	setSize(sf::Vector2f(50, 50));
	setOrigin(0, 0);
	setPosition(0, 1750);
	setFillColor(sf::Color::Green);
}


Player::~Player()
{
}


//checks if keys are pressed and starts movement
void Player::moveCheck()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		xMove = -3.125;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		xMove = 3.125;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		yMove = -3.125;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		yMove = 3.125;
	}
	

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		xMove = 0;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		yMove = 0;
	}
}


//moves player based on pressed keys
void Player::move()
{
	//move
	RectangleShape::move(xMove, yMove);

	if (getPosition().x < WINDOWX * xScreen - 600)
	{
		xScreen--;
		RectangleShape::setPosition(WINDOWX * xScreen - 50, getPosition().y);
		lastScreen.x = xScreen;
		std::cout << "x: " << xScreen << std::endl;
		std::cout << "y: " << yScreen << std::endl;
	}
	if (getPosition().y < WINDOWY * yScreen - 600)
	{
		yScreen--;
		RectangleShape::setPosition(getPosition().x, WINDOWY * yScreen - 50);
		lastScreen.y = yScreen;
		std::cout << "x: " << xScreen << std::endl;
		std::cout << "y: " << yScreen << std::endl;
	}
	if (getPosition().x > WINDOWX * xScreen - 50)
	{
		xScreen++;
		RectangleShape::setPosition(WINDOWX * xScreen - 600, getPosition().y);
		lastScreen.x = xScreen;
		std::cout << "x: " << xScreen << std::endl;
		std::cout << "y: " << yScreen << std::endl;
	}
	if (getPosition().y > WINDOWY * yScreen - 50)
	{
		yScreen++;
		RectangleShape::setPosition(getPosition().x, WINDOWY * yScreen - 600);
		lastScreen.y = yScreen;
		std::cout << "x: " << xScreen << std::endl;
		std::cout << "y: " << yScreen << std::endl;
	}
}


bool Player::collision(std::vector<Intaractable*> &rect, INTERACTIONTYPE type)
{
	sf::FloatRect nextPos;
	for (int i = 0; i < rect.size(); i++)
	{
		sf::FloatRect bounds = rect.at(i)->getGlobalBounds();
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
			if (type == NPC)
			{
				rect.at(i)->setInteraction(true);
				rect.at(i)->increaseLength(i);
				return true;
			}
			else if (type == ENEMY)
			{
				rect.at(i)->setInteraction(true);
				return true;
			}
			else if (type == WALL)
			{
				return true;
			}
		}
	}
	return false;
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


void Player::escMenu(sf::RenderWindow &window)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);
	escDelay++;

	//close the esc menu if the escape button is clicked and it is on
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escMenuOpen == true && escDelay > 15)
	{
		escMenuOpen = false;
		escDelay = 0;
	}

	//where cursor is on menu
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escMenuOpen == false && escDelay > 1) || escMenuOpen == true)
	{
		escMenuOpen = true;

		if (position.x > 150 && position.x < 450)
		{
			for (int i = 0; i < 8; i++)
			{
				if (position.y > 110 + (i * 50) && position.y < 160 + (i * 50))
					currentMenuSelection = i;
			}
		}
		else 
			currentMenuSelection = -1;

		//esc menu selection
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentMenuSelection >= 0)
		{
			switch (currentMenuSelection)
			{
			case 0:
				//resume
				escMenuOpen = false;
				escDelay = 0;
				break;
			case 1:
				//inv
				break;
			case 2:
				//
				break;
			case 3:
				//
				break;
			case 4:
				//
				break;
			case 5:
				//credits
				break;
			case 6:
				//save
				break;
			case 7:
				//close
				window.close();
				break;
			}
		}
	}
}


void Player::printEscMenu(sf::RenderWindow& window)
{
	sf::RectangleShape outline, background, selection;
	sf::Text text;
	sf::String message[8] = { L"つづく",  L"ありがとう",  L"",  L"",  L"",  L"",  L"",  L"終わり", };
	sf::Font font;

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

	outline.setSize(sf::Vector2f(300, 420));
	outline.setPosition(150 + (600 * (xScreen - 1)), 100 + (600 * (yScreen - 1)));

	background.setSize(sf::Vector2f(280, 400));
	background.setPosition(160 + (600 * (xScreen - 1)), 110 + (600 * (yScreen - 1)));
	background.setFillColor(sf::Color::Black);

	selection.setSize(sf::Vector2f(280, 50));
	selection.setFillColor(sf::Color(111, 124, 128));

	if (escMenuOpen == true)
	{
		window.draw(outline);
		window.draw(background);

		if (currentMenuSelection >= 0)
			selection.setPosition(160 + (600 * (xScreen - 1)), 110 + (currentMenuSelection * 50) + (600 * (yScreen - 1)));
		else 
			selection.setPosition(-100 + (600 * (xScreen - 1)), -100 + (600 * (yScreen - 1)));
		if (currentMenuSelection == 7)
			selection.setFillColor(sf::Color::Red);
		window.draw(selection);

		for (int i = 0; i < 8; i++)
		{
			text.setString(message[i]);
			text.setOrigin(text.getLocalBounds().width /2, text.getGlobalBounds().height / 2);
			text.setPosition(300 + (600 * (xScreen - 1)), 130 + (i * 50) + (600 * (yScreen - 1)));
			window.draw(text);
		}
	}

}


bool Player::getEscMenuOpen()
{
	return escMenuOpen;
}