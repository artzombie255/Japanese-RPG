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


void Player::collision(std::vector<Intaractable*> &rect, INTERACTIONTYPE type)
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
			}
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
	sf::String message[8] = { L"つづく",  L"",  L"",  L"",  L"",  L"",  L"",  L"終わり", };
	sf::Font font;

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

	outline.setSize(sf::Vector2f(300, 420));
	outline.setPosition(150, 100);

	background.setSize(sf::Vector2f(280, 400));
	background.setPosition(160, 110);
	background.setFillColor(sf::Color::Black);

	selection.setSize(sf::Vector2f(280, 50));
	selection.setFillColor(sf::Color(111, 124, 128));

	if (escMenuOpen == true)
	{
		window.draw(outline);
		window.draw(background);

		if (currentMenuSelection >= 0)
			selection.setPosition(160, 110 + (currentMenuSelection * 50));
		else 
			selection.setPosition(-100, -100);
		if (currentMenuSelection == 7)
			selection.setFillColor(sf::Color::Red);
		window.draw(selection);

		for (int i = 0; i < 8; i++)
		{
			text.setString(message[i]);
			text.setPosition(250, 115 + (i * 50));
			window.draw(text);
		}
	}

}


bool Player::getEscMenuOpen()
{
	return escMenuOpen;
}


int Player::attack()
{
	int attack = 0;

	//menu to choose what you want to attack with.
	system("cls");
	if (equippedMelee != 0)
		std::cout << "1. " << meleeStr[equippedMelee] << std::endl;
	if (equippedRanged != 0)
		std::cout << "2. " << rangedStr[equippedRanged] << std::endl;
	std::cin >> weapon;
	switch (weapon)
	{
	case 1:
		if ((rand() % 20 + (str + 1)) > 8)
		{
			attack = rand() % melee[equippedMelee] + str + 2;
			if (meleeBurn[equippedMelee] > 0)
			{
				activeBurn = meleeBurn[equippedMelee];
				burn = true;
			}
		}
		break;
	case 2:
		if ((rand() % 20 + (dex + 1)) > 10)
		{
			attack = rand() % ranged[equippedRanged] + dex;
			if (rangedBurn[equippedRanged] > 0)
			{
				activeBurn = rangedBurn[equippedRanged];
				burn = true;
			}
		}
		break;
	}
	system("cls");
	if (burn == true)
	{
		attack += rand() % activeBurn;
		if (rand() % 4 == 0)
			burn = false;
		std::cout << "burn active\n";
	}

	return attack;
}


void Player::loseHealth(int damage)
{
	
	//display health loss

	if (damage > natArmor)
	{
		damage -= natArmor;
		hp -= damage;
	}
	return;
}


void Player::addExp(int tempExp)
{
	exp += tempExp;
	while (levels[lvl + 1] <= exp)
	{
		levelUp();
	}
	return;
}


void Player::levelUp()
{
	int improvementPoints = 3, menu = 0;
	bool dexUp = true, strUp = true, wisUp = true, hpUp = true;

	lvl += 1;
	do
	{
		//display menu
		/*
		std::cout << "New level: " << lvl << std::endl << "What do you want to improve?\n";
		if (dex < 10 && dexUp == true)
			std::cout << "1. Dexterity (" << dex << ")\n";
		if (str < 10 && strUp == true)
			std::cout << "2. Strength (" << str << ")\n";
		if (maxHp < 60 && hpUp == true)
			std::cout << "4. Health (" << maxHp << ")\n";
		if (natArmor < 10 && improvementPoints > 1)
			std::cout << "5. Armor (" << natArmor << ") (Takes 2 improvement points)\n";
		*/ 

		//menu for choices
		switch (menu)
		{
		case 1:
			if (dex < 10 && dexUp == true)
			{
				dex++;
				improvementPoints--;
				dexUp = false;
			}
			break;
		case 2:
			if (str < 10 && strUp == true)
			{
				str++;
				improvementPoints--;
				strUp = false;
			}
			break;
		case 4:
			if (maxHp < 60 && hpUp == true)
			{
				maxHp += 5;
				improvementPoints--;
				hpUp = false;
			}
			break;
		case 5:
			if (natArmor < 10 && improvementPoints > 1)
			{
				natArmor++;
				improvementPoints -= 2;
			}
			break;
		}
	} while (improvementPoints != 0);
	hp = maxHp;

	return;
}


void Player::displayStats()
{
	//display stats
	return;
}


void Player::openInv()
{
	int menu = 0;

	do
	{
		//show inventory

		//std::cout << "Inventory options:\n\n1. Equip weapons\n2. Use items\n3. Display stats\n4. Exit\n";

		switch (menu)
		{
		case 1:
			equipWeapons();
			break;
		case 2:
			useItems();
			break;
		case 3:
			displayStats();
			break;
		}
	} while (menu != 4);
}


void Player::equipWeapons()
{
	int typeOfWeapon = 0;
	bool again;
	system("cls");

	//display weapon menu

	//<< rangedStr[equippedRanged] << std::endl << magicStr[equippedMagic];

	
	switch (typeOfWeapon)
	{
	case 1:
		for (int i = 1; i < NUMOFMELEE; i++)
		{
			if (meleeOwned[i] > 0)
				std::cout << i << ". " << meleeStr[i] << std::endl;
		}
		meleeOwned[equippedMelee] = 1;
		std::cin >> equippedMelee;
		meleeOwned[equippedMelee] = 2;
		meleeOwned[0] = 0;

		break;
	case 2:
		for (int i = 1; i < NUMOFRANGED; i++)
		{
			if (rangedOwned[i] > 0)
				std::cout << i << ". " << rangedStr[i] << std::endl;
		}
		rangedOwned[equippedRanged] = 1;
		std::cin >> equippedRanged;
		rangedOwned[equippedRanged] = 2;
		rangedOwned[0] = 0;

		break;
	case 4:
		system("cls");
		return;
	}

	system("cls");
	std::cout << "Equip more weapons?\n\n0. No\n1. Yes\n";
	std::cin >> again;

	if (again == true)
		equipWeapons();
	return;

}


void Player::useItems()
{
	int menu;
	system("cls");

	//take input

	//use items
	return;
}


void Player::shop()
{
	int typeOfWeapon = 0, selection;
	bool again;

	//weapon shop menu
	switch (typeOfWeapon)
	{
	case 1:
		for (int i = 1; i < NUMOFMELEE; i++)
		{
			if (meleeOwned[i] == 0)
				std::cout << i << ". " << meleeStr[i] << " (" << meleeCost[i] << ")" << std::endl;
		}
		std::cin >> selection;
		meleeOwned[selection] = 1;
		if (money >= meleeCost[selection])
			money -= meleeCost[selection];
		else
		{
			std::cout << "You don't have enough money to buy that";
			system("pause");
		}
		break;
	case 2:
		for (int i = 1; i < NUMOFRANGED; i++)
		{
			if (rangedOwned[i] == 0)
				std::cout << i << ". " << rangedStr[i] << " (" << rangedCost[i] << ")" << std::endl;
		}
		std::cin >> selection;
		rangedOwned[selection] = 1;
		if (money >= rangedCost[selection])
			money -= rangedCost[selection];
		else
		{
			std::cout << "You don't have enough money to buy that";
			system("pause");
		}
		break;
	case 4:
		for (int i = 1; i < NUMOFITEMS; i++)
		{
			std::cout << i << ". " << itemStr[i] << " (" << itemsCost[i] << ")" << std::endl;
		}
		std::cin >> selection;
		itemsOwned[selection]++;
		if (money >= itemsCost[selection])
			money -= itemsCost[selection];
		else
		{
			std::cout << "You don't have enough money to buy that";
			system("pause");
		}
		break;
	case 5:
		system("cls");
		return;
	}

	system("cls");
	std::cout << "Shop for more weapons?\n\n0. No\n1. Yes\n";
	std::cin >> again;

	if (again == true)
		shop();
	return;
}


void Player::addMoney(int tempMoney)
{
	money += tempMoney;
}
