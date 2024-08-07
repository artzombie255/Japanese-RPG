#include "Encounter.h"


Encounter::Encounter()
{
}


Encounter::Encounter(Player& player, Level& level)
{

}


Encounter::~Encounter()
{
}


void Encounter::displayEncounter(sf::RenderWindow &window)
{
	//do magic
	sf::RectangleShape MenuOutline, MenuBackground, background, selection;


	background.setSize(sf::Vector2f(600, 600));
	background.setFillColor(sf::Color::Black);

	MenuOutline.setSize(sf::Vector2f(600, 200));
	MenuOutline.setPosition(0, 400);

	MenuBackground.setSize(sf::Vector2f(580, 180));
	MenuBackground.setPosition(10, 410);
	MenuBackground.setFillColor(sf::Color::Black);

	selection.setSize(sf::Vector2f(164, 60));
	selection.setFillColor(sf::Color(111, 124, 128));


	window.draw(background);
	window.draw(MenuOutline);
	window.draw(MenuBackground);


	for (int i = 0; i < 3; i++)
	{
		selection.setPosition(32 + (i * 186), 430);
		window.draw(selection);
	}
	for (int i = 0; i < 3; i++)
	{
		selection.setPosition(32 + (i * 186), 510);
		window.draw(selection);
	}
	
	selection.setFillColor(sf::Color(99, 99, 99));

	if (currentMenuSelection >= 0 && currentMenuSelection < 3)
	{
		selection.setPosition(32 + (currentMenuSelection * 186), 430);
		window.draw(selection);

		selection.setSize(sf::Vector2f(154, 50));
		selection.setFillColor(sf::Color(59, 59, 59));
		selection.setPosition(37 + (currentMenuSelection * 186), 435);
		window.draw(selection);
	}
	else if (currentMenuSelection >= 3 && currentMenuSelection < 6)
	{
		selection.setPosition(32 + ((currentMenuSelection - 3) * 186), 510);
		window.draw(selection);

		selection.setSize(sf::Vector2f(154, 50));
		selection.setFillColor(sf::Color(59, 59, 59));
		selection.setPosition(37 + ((currentMenuSelection - 3) * 186), 515);
		window.draw(selection);
	}
	else
		selection.setPosition(-100, -100);

	//text.setPosition(20, 320);

	window.draw(selection);

	switch (currentScreen)
	{
	case MENUTYPE::ACTIONS:
		PrintActionsMenu(window);
		break;
	case MENUTYPE::WEAPONS:
		PrintWeaponsMenu(window);
	}
}


void Encounter::playEncounter(sf::RenderWindow &window)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);

	currentMenuSelection = -1;

	if (position.y > 430 && position.y < 490)
	{
		for (int i = 0; i < 3; i++)
		{
			if (position.x > 32 + (i * 186) && position.x < 196 + (i * 186))
				currentMenuSelection = i;
		}
	}
	else if(position.y > 510 && position.y < 570)
	{
		for (int i = 0; i < 3; i++)
		{
			if (position.x > 32 + (i * 186) && position.x < 196 + (i * 186))
				currentMenuSelection = i + 3;
		}
	}
	else
		currentMenuSelection = -1;


	switch (currentScreen)
	{
	case MENUTYPE::ACTIONS:
		ActionsMenu(window);
		break;
	case MENUTYPE::WEAPONS:
		WeaponsMenu(window);
	}
}


void Encounter::setEncounter()
{
	inEncounter = true;
}


void Encounter::ActionsMenu(sf::RenderWindow& window)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentMenuSelection >= 0)
	{
		switch (currentMenuSelection)
		{
		case 0:
			//Attack
			currentScreen = MENUTYPE::WEAPONS;
			break;
		case 1:
			//Items
			break;
		case 2:
			//Switch characters order
			break;
		case 3:
			//Switch weapons?
			break;
		case 4:
			//
			break;
		case 5:
			//Run
			inEncounter = false;
			break;
		}
	}
}


void Encounter::WeaponsMenu(sf::RenderWindow &window)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentMenuSelection >= 0)
	{
		switch (currentMenuSelection)
		{
		case 0:
			//basic attack
			break;
		case 1:
			//unique
			break;
		case 2:
			//special
			break;
		case 3:
			//dodge
			break;
		case 4:
			//ready attack
			break;
		case 5:
			currentScreen = MENUTYPE::ACTIONS;
			break;
		}
	}
}


void Encounter::PrintActionsMenu(sf::RenderWindow& window)
{
	sf::Text text;
	sf::String message[6] = { L"Attack",  L"Items",  L"Switch characters order",  L"Switch weapons?",  L"Run",  L"Run" };
	sf::Font font;

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

	for (int i = 0; i < 3; i++)
	{
		text.setString(message[i]);
		text.setOrigin(text.getLocalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(113 + (i * 186), 454);
		window.draw(text);
	}

	for (int i = 3; i < 6; i++)
	{
		text.setString(message[i]);
		text.setOrigin(text.getLocalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(113 + ((i - 3) * 186), 534);
		window.draw(text);
	}
}


void Encounter::PrintWeaponsMenu(sf::RenderWindow& window)
{
	sf::Text text;
	sf::String message[6] = { L"basic attack",  L"unique",  L"special",  L"dodge",  L"ready attack",  L"back" };
	sf::Font font;

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

	for (int i = 0; i < 3; i++)
	{
		text.setString(message[i]);
		text.setOrigin(text.getLocalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(113 + (i * 186), 454);
		window.draw(text);
	}

	for (int i = 3; i < 6; i++)
	{
		text.setString(message[i]);
		text.setOrigin(text.getLocalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(113 + ((i - 3) * 186), 534);
		window.draw(text);
	}
}


bool Encounter::getInEncounter()
{
	return inEncounter;
}


int Encounter::getEncounterType()
{
	return encounterType;
}


int Encounter::attack()
{
	int attack = 0, slash;

	switch (weaponType[equippedWeapon])
	{
	case WEAPONTYPE::PIERCE:
		if ((rand() % 20 + dex) > 11)
		{
			attack = rand() % weapons[equippedWeapon] + dex + 2;
		}
		break;
	case WEAPONTYPE::SLASH:
		slash = rand() % 20 + dex;
		if (slash > 11)
		{
			slash -= 11;
			attack = rand() % weapons[equippedWeapon] + (str / 2) + slash;
		}
		break;
	case WEAPONTYPE::BLUDGEON:
		if ((rand() % 20 + str) > 9)
		{
			attack = rand() % weapons[equippedWeapon] + str;
		}
		break;
	case WEAPONTYPE::RANGED:
		if ((rand() % 20 + dex) > 14)
		{
			attack = rand() % weapons[equippedWeapon] + dex + 2;
		}
		break;
	}

	return attack;
}


void Encounter::loseHealth(int damage)
{

	//display health loss

	if (damage > natArmor)
	{
		damage -= natArmor;
		hp -= damage;
	}
	return;
}


void Encounter::addExp(int tempExp)
{
	exp += tempExp;
	while (levels[lvl + 1] <= exp)
	{
		levelUp();
	}
	return;
}


void Encounter::levelUp()
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


void Encounter::displayStats()
{
	//display stats
	return;
}


void Encounter::openInv()
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


void Encounter::equipWeapons()
{
	int typeOfWeapon = 0;
	bool again;
	system("cls");

	//display weapon menu

	//<< rangedStr[equippedRanged] << std::endl << magicStr[equippedMagic];


	/*switch (typeOfWeapon)
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
	*/

}


void Encounter::useItems()
{
	int menu;
	system("cls");

	//take input

	//use items
	return;
}


void Encounter::shop()
{
	int typeOfWeapon = 0, selection;
	bool again;

	//weapon shop menu
	/*switch (typeOfWeapon)
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
	*/
}


void Encounter::addMoney(int tempMoney)
{
	money += tempMoney;
}
