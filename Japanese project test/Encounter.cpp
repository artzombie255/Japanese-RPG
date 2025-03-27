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


void Encounter::addToTeam(CHARACTERS newCharacter)
{
	int i = 0;
	bool added = false;

	team.push_back(newCharacter);
	if (team.size() > 4)
		changeTeam();
	else 
		while (i < 4 && added == false)
		{
			if (currentTeam[i] == CHARACTERS::BLANK)
			{
				currentTeam[i] = newCharacter;
				added = true;
			}
			i++;
		}
	return;
}


void Encounter::changeTeam()
{

}


void Encounter::displayEncounter(sf::RenderWindow &window)
{
	//do magic
	sf::RectangleShape MenuOutline, MenuBackground, background, selection;

	//set size, color, and position
	background.setSize(sf::Vector2f(600, 600));
	background.setFillColor(sf::Color::Black);

	MenuOutline.setSize(sf::Vector2f(600, 200));
	MenuOutline.setPosition(0, 400);

	MenuBackground.setSize(sf::Vector2f(580, 180));
	MenuBackground.setPosition(10, 410);
	MenuBackground.setFillColor(sf::Color::Black);

	selection.setSize(sf::Vector2f(164, 60));
	selection.setFillColor(sf::Color(111, 124, 128));

	//draw the backgrounds and outlines
	window.draw(background);
	window.draw(MenuOutline);
	window.draw(MenuBackground);

	//display buttons
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

	//display the button being hovered over
	if (currentScreen != MENUTYPE::INVENTORY && currentScreen != MENUTYPE::CHARACTER_TARGET)
	{
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
	}


	window.draw(selection);

	//send it to the next display screen
	switch (currentScreen)
	{
	case MENUTYPE::ACTIONS:
		PrintActionsMenu(window);
		break;
	case MENUTYPE::WEAPONS:
		PrintWeaponsMenu(window);
		break;
	case MENUTYPE::INVENTORY:
		PrintInvMenu(window);
		break;
	case MENUTYPE::TARGET:
		printTargetMenu(window);
		break;
	case MENUTYPE::CHARACTER_TARGET:
		printTargetCharacterMenu(window);
	}
}


void Encounter::playEncounter(sf::RenderWindow &window)
{


	sf::Vector2i position = sf::Mouse::getPosition(window);

	currentMenuSelection = -1;

	//track where the cursor is
	if (currentScreen != MENUTYPE::INVENTORY && currentScreen != MENUTYPE::CHARACTER_TARGET)
	{
		if (position.y > 430 && position.y < 490)
		{
			for (int i = 0; i < 3; i++)
			{
				if (position.x > 32 + (i * 186) && position.x < 196 + (i * 186))
					currentMenuSelection = i;
			}
		}
		else if (position.y > 510 && position.y < 570)
		{
			for (int i = 0; i < 3; i++)
			{
				if (position.x > 32 + (i * 186) && position.x < 196 + (i * 186))
					currentMenuSelection = i + 3;
			}
		}
		else
			currentMenuSelection = -1;
	}

	//send to the next background/logic screen
	switch (currentScreen)
	{
	case MENUTYPE::ACTIONS:
		ActionsMenu(window);
		break;
	case MENUTYPE::WEAPONS:
		WeaponsMenu(window);
		break;
	case MENUTYPE::INVENTORY:
		InvMenu(window);
	case MENUTYPE::TARGET:
		targetMenu(window);
		break;
	case MENUTYPE::CHARACTER_TARGET:
		targetCharacterMenu(window);
	}
}


void Encounter::setEncounter()
{
	inEncounter = true;
}


void Encounter::switchTurn()
{
	if (currentTeamSpot != -1)
	{
		std::cout << currentTeamSpot << std::endl;
		if (currentTeamSpot < 3 && currentTeamSpot != -1)
		{
			currentTeamSpot++;
			currentScreen = MENUTYPE::ACTIONS;
		}
		else
		{
			currentTeamSpot = -1;
			currentEnemySpot = 0;
		}

		if (currentTeamSpot != -1)
			if (currentTeam[currentTeamSpot] == CHARACTERS::BLANK)
				switchTurn();

	}
	if (currentTeamSpot == -1)
		enemiesTurn();
}


void Encounter::enemiesTurn()
{
	std::cout << currentEnemySpot << ":" << enemyHp[currentEnemySpot] << std::endl;
	if (currentEnemySpot < 3 && currentEnemySpot != -1)
	{
		currentEnemySpot++;
	}
	else
	{
		currentTeamSpot = 0;
		currentEnemySpot = -1;
	}

	if (currentEnemySpot != -1)
		if (enemyHp[currentEnemySpot] <= 0)
			enemiesTurn();

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
			currentScreen = MENUTYPE::INVENTORY;
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
			currentScreen = MENUTYPE::TARGET;
			//std::cout << "hp:" << enemyHp[currentEnemySpot] << std::endl << "hit:" << attack << std::endl;
			//enemyHp[0] -= attack();
			//std::cout << "hp:" << enemyHp[currentEnemySpot] << std::endl << "hit:" << attack << std::endl;

			//switchTurn();
			break;
		case 1:
			//unique
			unique();
			//switchTurn();
			break;
		case 2:
			//special
			switchTurn();
			break;
		case 3:
			//dodge
			switchTurn();
			break;
		case 4:
			//ready attack
			switchTurn();
			break;
		case 5:
			currentScreen = MENUTYPE::ACTIONS;
			break;
		}
		enemiesAlive = false;

		for (int i = 0; i < 4; i++)
		{
			if (enemyHp[i] <= 0)
				enemyAlive[i] = false;

			if (enemyAlive[i] == true)
				enemiesAlive = true;
		}
	}
}


void Encounter::InvMenu(sf::RenderWindow& window)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);
	int temp = 0;

	currentMenuSelection = -1;

	//players button tracking
	if (position.x > 108 && position.x < 168)
	{
		for (int i = 0; i < 4; i++)
		{
			if (position.y > 108 + (i * 108) && position.y < 168 + (i * 108))
				currentMenuSelection = i;
		}
	}
	/*
	else if (position.y > 510 && position.y < 570)
	{
		for (int i = 0; i < 3; i++)
		{
			if (position.x > 32 + (i * 186) && position.x < 196 + (i * 186))
				currentMenuSelection = i + 3;
		}
	}*/
	else if(position.x > 510 && position.x < 540)
	{
		if (position.y > 60 && position.y < 90)
			currentMenuSelection = 4;
	}
	else
		currentMenuSelection = -1;



	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentMenuSelection != -1)
	{
		switch (currentMenuSelection)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			if (PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].type == WEAPONTYPE::RANGED)
			{

			}
			else if (PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].type == WEAPONTYPE::MELEE)
			{

			}
			break;
			
		case 4:
			currentScreen = MENUTYPE::ACTIONS;
			break;
		}
	}
}


void Encounter::targetMenu(sf::RenderWindow&)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentMenuSelection >= 0)
	{
		switch (currentMenuSelection)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			enemyHp[currentMenuSelection] -= attack();
			switchTurn();
			break;
		case 5:
			currentScreen = MENUTYPE::WEAPONS;
			break;
		}
		enemiesAlive = false;

		for (int i = 0; i < 4; i++)
		{
			if (enemyHp[i] <= 0)
				enemyAlive[i] = false;

			if (enemyAlive[i] == true)
				enemiesAlive = true;
		}
	}
}


void Encounter::targetCharacterMenu(sf::RenderWindow& window)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);
	int temp = 0;

	currentMenuSelection = -1;

	//players button tracking
	if (position.x > 210 && position.x < 390)
	{
		for (int i = 0; i < 4; i++)
		{
			if (position.y > 110 + (i * 100) && position.y < 170 + (i * 100))
				currentMenuSelection = i;
		}
	}
	else
		currentMenuSelection = -1;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentMenuSelection >= 0)
	{
		switch (currentTeam[currentTeamSpot])
		{
		case CHARACTERS::AERYK:
			targetingTeam[currentMenuSelection] = currentTeamSpot;
			break;
		case CHARACTERS::ROWAN:
			PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].hp += rand() % 6 + PlayableCharacters[enumToIntCharacters(currentTeam[currentTeamSpot])].lvl + 
				PlayableCharacters[enumToIntCharacters(currentTeam[currentTeamSpot])].maxMag;
			break;
		}
		switchTurn();
	}
}


void Encounter::PrintActionsMenu(sf::RenderWindow& window)
{
	sf::Text text;
	sf::String message[6] = { L"Attack",  L"Items",  L"Switch characters order",  L"Switch weapons?",  L"",  L"Run" };
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
	//sets up text
	sf::Text text;
	sf::String message[6] = { L"basic attack",  L"unique",  L"special",  L"dodge",  L"ready attack",  L"back" };
	sf::Font font;

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

	//prints text on buttons
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


void Encounter::PrintInvMenu(sf::RenderWindow& window)
{
	//sets up backgrounds and outlines and selection
	sf::RectangleShape MenuOutline, MenuBackground, selection;

	MenuOutline.setSize(sf::Vector2f(500, 500));
	MenuOutline.setPosition(50, 50);

	MenuBackground.setSize(sf::Vector2f(480, 480));
	MenuBackground.setPosition(60, 60);
	MenuBackground.setFillColor(sf::Color::Black);

	selection.setSize(sf::Vector2f(60, 60));
	selection.setFillColor(sf::Color(111, 124, 128));

	window.draw(MenuOutline);
	window.draw(MenuBackground);


	selection.setFillColor(sf::Color(99, 99, 99));

	//button highlights
	if (currentMenuSelection >= 0 && currentMenuSelection < 4)
	{
		selection.setPosition(108, 108 + (currentMenuSelection * 108));
		window.draw(selection);
	}
	else if (currentMenuSelection == 4)
	{
		selection.setSize(sf::Vector2f(30, 30));
		selection.setFillColor(sf::Color::Red);
		selection.setPosition(510, 60);
		window.draw(selection);
	}
	else
		selection.setPosition(-100, -100);


}


void Encounter::printTargetMenu(sf::RenderWindow& window)
{
	//sets up text
	sf::Text text;
	sf::String message[6] = { L"",  L"",  L"",  L"",  L"",  L"back" };
	sf::Font font;

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

	//prints text on buttons
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


void Encounter::printTargetCharacterMenu(sf::RenderWindow& window)
{
	//sets up backgrounds and outlines and selection
	sf::RectangleShape MenuOutline, MenuBackground, selection;

	MenuOutline.setSize(sf::Vector2f(200, 400));
	MenuOutline.setPosition(200, 100);

	MenuBackground.setSize(sf::Vector2f(180, 380));
	MenuBackground.setPosition(210, 110);
	MenuBackground.setFillColor(sf::Color::Black);


	selection.setSize(sf::Vector2f(180, 80));
	selection.setFillColor(sf::Color(111, 124, 128));

	window.draw(MenuOutline);
	window.draw(MenuBackground);


	selection.setFillColor(sf::Color(99, 99, 99));

	//button highlights
	if (currentMenuSelection >= 0 && currentMenuSelection < 4)
	{
		selection.setPosition(210, 110 + (currentMenuSelection * 100));
		window.draw(selection);
	}
	else
		selection.setPosition(-100, -100);
}


bool Encounter::getInEncounter()
{
	return inEncounter;
}


int Encounter::getEncounterType()
{
	return encounterType;
}


int Encounter::enumToIntCharacters(CHARACTERS temp)
{
	switch (temp)
	{
	case CHARACTERS::AERYK:
	
		return 0;
	case CHARACTERS::ASHTON:
		
		return 1;
	case CHARACTERS::AUBREY:
		
		return 2;
	case CHARACTERS::PHOENIX:
		
		return 3;
	case CHARACTERS::ROWAN:
		
		return 4;
	case CHARACTERS::BLANK:
		
		return 5;
	}
}


//deals with weapon logic
int Encounter::attack()
{
	int attack = 0, slash;

	if (currentTeamSpot >= 0)
		equippedWeapon = PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].equippedWeapon;
	else
		std::cout << "enemy turn";
		//equippedWeapon = currentTeam[currentTeamSpot].equippedWeapon;

	switch (WEAPONS[equippedWeapon].type)
	{
	case WEAPONTYPE::PIERCE:
		if ((rand() % 20 + PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].dex + 1) > 11)
		{
			attack = rand() % weapons[equippedWeapon] + PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].dex + 3;
		}
		break;
	case WEAPONTYPE::SLASH:
		slash = rand() % 20 + PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].dex + 1;
		if (slash > 11)
		{
			slash -= 11;
			attack = rand() % weapons[equippedWeapon] + (PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].str / 2) + slash + 1;
		}
		break;
	case WEAPONTYPE::BLUDGEON:
		if ((rand() % 20 + PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].str + 1) > 9)
		{
			attack = rand() % weapons[equippedWeapon] + PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].str + 1;
		}
		break;
	case WEAPONTYPE::RANGED:
		if ((rand() % 20 + PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].dex + 1) > 14)
		{
			attack = rand() % weapons[equippedWeapon] + PlayableCharacters[enumToIntCharacters(currentTeam[currentMenuSelection])].dex + 3;
		}
		break;
	}

	return attack;
}


void Encounter::unique()
{
	switch (currentTeam[currentTeamSpot])
	{
	case CHARACTERS::AERYK:
		//targetingTeam[] = currentTeamSpot
		currentScreen = MENUTYPE::CHARACTER_TARGET;
		break;
	case CHARACTERS::ASHTON:
		//second wind
		PlayableCharacters[enumToIntCharacters(currentTeam[currentTeamSpot])].hp += rand() % 10 + PlayableCharacters[enumToIntCharacters(currentTeam[currentTeamSpot])].lvl;
		switchTurn();
		break;
	case CHARACTERS::AUBREY:

		break;
	case CHARACTERS::PHOENIX:

		break;
	case CHARACTERS::ROWAN:
		currentScreen = MENUTYPE::CHARACTER_TARGET;
		break;
	case CHARACTERS::BLANK:

		break;
	}
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
