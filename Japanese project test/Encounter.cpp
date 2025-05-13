#include "Encounter.h"


Encounter::Characters Encounter::PlayableCharacters[8] =
{
	//name, type, max hp, current hp, armor, strength, dexterity, magic slots, max magic slots, level, xp, current weapon
	{CHARACTERS::AERYK,		WEAPONTYPE::MELEE,  25, 25, 1, 1, 0, 2, 2, 1, 0, 10},
	{CHARACTERS::ASHTON,	WEAPONTYPE::MELEE,  25, 25, 2, 3, 0, 2, 2, 1, 0, 6},
	{CHARACTERS::AUBREY,	WEAPONTYPE::MELEE,  20, 20, 0, 2, 1, 2, 2, 1, 0, 5},
	{CHARACTERS::PHOENIX,	WEAPONTYPE::RANGED, 15, 15, 0, 0, 2, 3, 3, 1, 0, 14},
	{CHARACTERS::ROWAN,		WEAPONTYPE::RANGED, 15, 15, 0, 0, 2, 7, 7, 1, 0, 14},
	{CHARACTERS::STEVE,		WEAPONTYPE::RANGED, 15, 15, 0, 0, 2, 3, 3, 1, 0, 14},
	{CHARACTERS::CHASE,		WEAPONTYPE::RANGED, 15, 15, 0, 0, 2, 5, 5, 1, 0, 14},
	{CHARACTERS::BLANK,		WEAPONTYPE::MELEE,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

Encounter::Encounter()
{
}


Encounter::Encounter(Player& player, Level& level)
{

}


Encounter::~Encounter()
{
}


bool Encounter::endEncounter()
{
	if (enemiesAlive == false && currentScreen != MENUTYPE::LEVEL_UP)
	{
		inEncounter = false;
		return true;
	}
	return false;
}

void Encounter::upgradeEnemies()
{
	upgradedEnemies++;
}


void Encounter::addToTeam(CHARACTERS newCharacter)
{
	int i = 0;
	bool added = false;

	totalTeam++;

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


void Encounter::printTeamSpot(int temp)
{
	switch (currentTeam[temp])
	{
	case CHARACTERS::AERYK:
		std::cout << "Aeryk\n";
		break;
	case CHARACTERS::ASHTON:
		std::cout << "Ashton\n";
		break;
	case CHARACTERS::AUBREY:
		std::cout << "Aubrey\n";
		break;
	case CHARACTERS::PHOENIX:
		std::cout << "Phoenix\n";
		break;
	case CHARACTERS::ROWAN:
		std::cout << "Rowan\n";
		break;
	case CHARACTERS::BLANK:
		std::cout << "Blank\n";
		break;
	}
}


void Encounter::changeTeam()
{

}


void Encounter::displayEncounter(sf::RenderWindow &window)
{
	//do magic
	sf::RectangleShape MenuOutline, MenuBackground, background, selection;
	sf::Text playerHealth, enemyHealth;
	sf::String playerNames[4] = { L"オーブリー：",  L"エリック：",  L"ローワン：",  L"アシトン：" }, 
		enemyNames[4] = { L"一：",  L"二：",  L"三：",  L"四：" };
	sf::Font font;

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	playerHealth.setFont(font);
	enemyHealth.setFont(font);

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

	//hp
	for (int i = 0; i < totalTeam; i++)
	{
		playerHealth.setFillColor(sf::Color::White);
		if (currentTeamSpot == i)
			playerHealth.setFillColor(sf::Color::Green);

		playerHealth.setString(playerNames[i] + std::to_string(PlayableCharacters[enumToIntCharacters(currentTeam[i])].hp));
		//playerHealth.setOrigin(playerHealth.getLocalBounds().width / 2, playerHealth.getGlobalBounds().height / 2);
		playerHealth.setPosition(50, 50 + (i * 60));
		window.draw(playerHealth);

		playerHealth.setString("MAG: " + std::to_string(PlayableCharacters[enumToIntCharacters(currentTeam[i])].mag));
		//playerHealth.setOrigin(playerHealth.getLocalBounds().width / 2, playerHealth.getGlobalBounds().height / 2);
		playerHealth.setPosition(70, 75 + (i * 60));
		window.draw(playerHealth);
	}
	for (int i = 0; i < 4; i++)
	{
		enemyHealth.setString(enemyNames[i] + std::to_string(DefaultEnemies[enumToIntEnemies(currentEnemies[i])].hp));
		//enemyHealth.setOrigin(enemyHealth.getLocalBounds().width / 2, enemyHealth.getGlobalBounds().height / 2);
		enemyHealth.setPosition(450, 50 + (i * 50));
		window.draw(enemyHealth);
	}


	//display the button being hovered over
	if (currentScreen != MENUTYPE::INVENTORY && currentScreen != MENUTYPE::CHARACTER_TARGET 
		&& currentScreen != MENUTYPE::LEVEL_UP)
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
		break;
	case MENUTYPE::LEVEL_UP:
		printLevelUpMenu(window);
	}
}


void Encounter::playEncounter(sf::RenderWindow &window)
{
	//std::cout << enemyHp[0] << std::endl;

	//printTeamSpot(currentTeamSpot);

	sf::Vector2i position = sf::Mouse::getPosition(window);

	currentMenuSelection = -1;

	if (currentTeamSpot != -1)
		if (currentTeam[currentTeamSpot] == CHARACTERS::BLANK)
			switchTurn();

	//track where the cursor is
	if (currentScreen != MENUTYPE::INVENTORY && currentScreen != MENUTYPE::CHARACTER_TARGET
		&& currentScreen != MENUTYPE::LEVEL_UP)
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
		break;
	case MENUTYPE::TARGET:
		targetMenu(window);
		break;
	case MENUTYPE::CHARACTER_TARGET:
		targetCharacterMenu(window);
		break;
	case MENUTYPE::LEVEL_UP:
		levelUpMenu(window);
	}
}


void Encounter::setEncounter(int temp)
{
	inEncounter = true;
	targetingTeam[0] = 0;
	targetingTeam[1] = 1;
	targetingTeam[2] = 2;
	targetingTeam[3] = 3;
	currentScreen = MENUTYPE::ACTIONS;
	DefaultEnemies[0].hp = DefaultEnemies[0].maxHp;
	DefaultEnemies[1].hp = DefaultEnemies[1].maxHp;
	DefaultEnemies[2].hp = DefaultEnemies[2].maxHp;
	DefaultEnemies[3].hp = DefaultEnemies[3].maxHp;
	DefaultEnemies[4].hp = DefaultEnemies[4].maxHp;
	DefaultEnemies[5].hp = DefaultEnemies[5].maxHp;
	DefaultEnemies[6].hp = DefaultEnemies[6].maxHp;
	enemiesAlive = true;
	enemyAlive[0] = true;
	currentTeamSpot = 0; 
	enemyTurn = 0; 
	currentEnemySpot = 0;

	switch (temp)
	{
	case 0:
		if (upgradedEnemies == 0)
		{
			switch (rand() % 3)
			{
			case 0:
				currentEnemies[0] = ENEMIES::BSPEAR;
				currentEnemies[1] = ENEMIES::BLANK_E;
				currentEnemies[2] = ENEMIES::BLANK_E;
				currentEnemies[3] = ENEMIES::BLANK_E;
				break;
			case 1:
				currentEnemies[0] = ENEMIES::DAGGER;
				currentEnemies[1] = ENEMIES::BLANK_E;
				currentEnemies[2] = ENEMIES::BLANK_E;
				currentEnemies[3] = ENEMIES::BLANK_E;
				break;
			case 2:
				currentEnemies[0] = ENEMIES::STAFF;
				currentEnemies[1] = ENEMIES::BLANK_E;
				currentEnemies[2] = ENEMIES::BLANK_E;
				currentEnemies[3] = ENEMIES::BLANK_E;
				break;
			}
		}
		else
		{
			switch (rand() % 3)
			{
			case 0:
				currentEnemies[0] = ENEMIES::SPEAR;
				currentEnemies[1] = ENEMIES::BLANK_E;
				currentEnemies[2] = ENEMIES::BLANK_E;
				currentEnemies[3] = ENEMIES::BLANK_E;
				break;
			case 1:
				currentEnemies[0] = ENEMIES::SWORD;
				currentEnemies[1] = ENEMIES::BLANK_E;
				currentEnemies[2] = ENEMIES::BLANK_E;
				currentEnemies[3] = ENEMIES::BLANK_E;
				break;
			case 2:
				currentEnemies[0] = ENEMIES::CLUB;
				currentEnemies[1] = ENEMIES::BLANK_E;
				currentEnemies[2] = ENEMIES::BLANK_E;
				currentEnemies[3] = ENEMIES::BLANK_E;
				break;
			}
		}
		break;
	case 1:
		currentEnemies[0] = ENEMIES::ASHTONE;
		currentEnemies[1] = ENEMIES::BLANK_E;
		currentEnemies[2] = ENEMIES::BLANK_E;
		currentEnemies[3] = ENEMIES::BLANK_E;
		break;
	case 2:
		currentEnemies[0] = ENEMIES::SENSEIE;
		currentEnemies[1] = ENEMIES::BLANK_E;
		currentEnemies[2] = ENEMIES::BLANK_E;
		currentEnemies[3] = ENEMIES::BLANK_E;
		break;
	}
	std::cout << currentEnemySpot << ":" << DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].hp << std::endl;
}


void Encounter::switchTurn()
{
	//std::cout << 0 << ":" << DefaultEnemies[enumToIntEnemies(currentEnemies[0])].hp << std::endl;
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


	}
	if (currentTeamSpot == -1)
		enemiesTurn();
}


void Encounter::enemiesTurn()
{
	int attack;
	std::cout << currentEnemySpot << ":" << DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].hp << std::endl;
	if (currentEnemySpot <= 3 && currentEnemySpot != -1 && DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].hp > 0)
	{
		attack = enemiesAttack();
		std::cout << "ATK: " << attack << "\n";
		PlayableCharacters[enumToIntCharacters(currentTeam[targetingTeam[rand() % totalTeam]])].hp -= attack;
		currentEnemySpot++;
	}
	else if (currentEnemySpot <= 3 && currentEnemySpot != -1 && DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].hp <= 0)
	{
		currentEnemySpot++;
	}
	if (currentEnemySpot > 3)
	{
		currentTeamSpot = 0;
		currentEnemySpot = -1;
	}

	if (currentEnemySpot >= 0)
	{
		if (DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].hp <= 0)
			enemiesTurn();
	}
	else
		currentScreen = MENUTYPE::ACTIONS;


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
			//switchTurn();
			break;
		case 3:
			//dodge
			//switchTurn();
			break;
		case 4:
			//ready attack
			//switchTurn();
			break;
		case 5:
			currentScreen = MENUTYPE::ACTIONS;
			break;
		}
		enemiesAlive = false;

		for (int i = 0; i < 4; i++)
		{
			if (DefaultEnemies[enumToIntEnemies(currentEnemies[i])].hp <= 0)
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
			DefaultEnemies[enumToIntEnemies(currentEnemies[currentMenuSelection])].hp -= attack();
			//addExp(10);
			switchTurn();
			//currentScreen = MENUTYPE::LEVEL_UP;
			break;
		case 5:
			currentScreen = MENUTYPE::WEAPONS;
			break;
		}
		enemiesAlive = false;

		for (int i = 0; i < 4; i++)
		{
			if (DefaultEnemies[enumToIntEnemies(currentEnemies[i])].hp <= 0)
				enemyAlive[i] = false;

			if (enemyAlive[i] == true)
				enemiesAlive = true;
		}
		int rando = rand() % 5;
		if (enemiesAlive == false)
		{
			addExp(rando);
			std::cout << " : " << rando;
			if (DefaultEnemies[enumToIntEnemies(currentEnemies[0])].enemyName == ASHTONE)
				addExp(25);
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


void Encounter::levelUpMenu(sf::RenderWindow& window)
{
	//int improvementPoints = 3, menu = 0;
	//bool dexUp = true, strUp = true, wisUp = true, hpUp = true;

	sf::Vector2i position = sf::Mouse::getPosition(window);
	//int temp = 0;

	currentMenuSelection = -1;

	
	if ((!(PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].exp >= levels[PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].lvl]) ||
		currentTeam[currentLeveling] == CHARACTERS::BLANK) && currentLeveling < 3)
	{
		currentLeveling++;
	}
	else if (currentLeveling == 3 && (!(PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].exp >= 
		levels[PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].lvl]) ||
		currentTeam[currentLeveling] == CHARACTERS::BLANK))
	{
		currentScreen = MENUTYPE::ACTIONS;
		currentLeveling = 0;
	}

	//players button tracking
	if (position.x > 108 && position.x < 168)
	{
		for (int i = 0; i < 4; i++)
		{
			if (position.y > 108 + (i * 108) && position.y < 168 + (i * 108))
				currentMenuSelection = i;
		}
	}
	else if (position.x > 510 && position.x < 540)
	{
		if (position.y > 60 && position.y < 90)
			currentMenuSelection = 4;
	}
	else
		currentMenuSelection = -1;

	std::cout << currentLeveling << std::endl;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentMenuSelection != -1)
	{
		switch (currentMenuSelection)
		{
		case 0:
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxHp += 5;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].lvl++;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].hp =
				PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxHp;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].mag =
				PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxMag;
			break;
		case 1:
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].dex++;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].lvl++;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].hp =
				PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxHp;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].mag =
				PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxMag;
			break;
		case 2:
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].str++;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].lvl++;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].hp =
				PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxHp;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].mag =
				PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxMag;
			break;
		case 3:
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxMag++;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].mag++;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].lvl++;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].hp =
				PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxHp;
			PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].mag =
				PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxMag;
			break;

		case 4:
			currentScreen = MENUTYPE::ACTIONS;
			break;
		}

		if (currentLeveling == 3)
		{
			currentLeveling = 0;
			currentScreen = MENUTYPE::ACTIONS;
		}
		else
			currentLeveling++;
	}


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
		/*switch (menu)
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

	hp = maxHp;
	*/
	return;
}



void Encounter::PrintActionsMenu(sf::RenderWindow& window)
{
	sf::Text text;
	sf::String message[6] = { L"おそう",  L"だめ",  L"だめ",  L"ウエポンズ",  L"だめ",  L"走る" };
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
	sf::String message[6] = { L"おそう",  L"ユニーク",  L"だめ",  L"だめ",  L"だめ",  L"帰る" };
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
	sf::String message[6] = { L"一",  L"二",  L"三",  L"四",  L"だめ",  L"帰る" };
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
	sf::Text text;
	sf::String names[4] = { L"オーブリー",  L"エリック",  L"ローワン",  L"アシトン" };
	sf::Font font;

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

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

	for (int i = 0; i < totalTeam; i++)
	{
		text.setString(names[i]);
		//playerHealth.setOrigin(playerHealth.getLocalBounds().width / 2, playerHealth.getGlobalBounds().height / 2);
		text.setPosition(210, 110 + (i * 100));
		window.draw(text);
	}

}


void Encounter::printLevelUpMenu(sf::RenderWindow& window)
{
	//sets up backgrounds and outlines and selection
	sf::RectangleShape MenuOutline, MenuBackground, selection;
	//sets up text
	sf::Text text;
	sf::String message[4] = { L"HP     ",  L"DEX     ",  L"STR     ",  L"MAG     " };
	sf::String names[4] = { L"オーブリー",  L"エリック",  L"ローワン",  L"アシトン" };
	sf::Font font;

	message[0] += std::to_string(PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxHp);
	message[1] += std::to_string(PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].dex);
	message[2] += std::to_string(PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].str);
	message[3] += std::to_string(PlayableCharacters[enumToIntCharacters(currentTeam[currentLeveling])].maxMag);

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);
	
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

	for (int i = 0; i < 4; i++)
	{
		text.setString(message[i]);
		//text.setOrigin(text.getLocalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(110, 120 + (i * 108));
		window.draw(text);
	}

	text.setString(names[currentLeveling]);
	//playerHealth.setOrigin(playerHealth.getLocalBounds().width / 2, playerHealth.getGlobalBounds().height / 2);
	text.setPosition(300, 275);
	window.draw(text);


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


int Encounter::enumToIntEnemies(ENEMIES temp)
{
	switch (temp)
	{
	case ENEMIES::BLANK_E:

		return 0;
	case ENEMIES::BSPEAR:

		return 1;
	case ENEMIES::DAGGER:

		return 2;
	case ENEMIES::STAFF:

		return 3;
	case ENEMIES::SPEAR:

		return 4;
	case ENEMIES::SWORD:

		return 5;
	case ENEMIES::CLUB:

		return 6;
	case ENEMIES::ASHTONE:

		return 7;
	}
}


void Encounter::addToParty(CHARACTERS tempCharacter)
{
	int i = 0;
	bool added = false;

	while( i < 4 && added == false )
	{
		if (currentTeam[i] == CHARACTERS::BLANK)
		{
			currentTeam[i] = tempCharacter;
			added = true;
		}
	}
}


bool Encounter::playerAlive()
{
	for (int i = 0; i < totalTeam; i++)
	{
		if (PlayableCharacters[enumToIntCharacters(currentTeam[i])].hp <= 0)
			return false;
	}
	return true;
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

	attack += increasedDamage;

	increasedDamage = 0;

	return attack;
}


int Encounter::enemiesAttack()
{
	int attack = 0, slash;

	if (currentEnemySpot >= 0)
		equippedWeapon = DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].equippedWeapon;
	else
		std::cout << "players turn";
	//equippedWeapon = currentTeam[currentTeamSpot].equippedWeapon;
	if (currentEnemySpot >= 0)
	{
		switch (WEAPONS[equippedWeapon].type)
		{
		case WEAPONTYPE::PIERCE:
			if ((rand() % 20 + DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].dex + 1) > 11)
			{
				attack = rand() % weapons[equippedWeapon] + DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].dex + 3;
			}
			break;
		case WEAPONTYPE::SLASH:
			slash = rand() % 20 + DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].dex + 1;
			if (slash > 11)
			{
				slash -= 11;
				attack = rand() % weapons[equippedWeapon] + (DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].str / 2) + slash + 1;
			}
			break;
		case WEAPONTYPE::BLUDGEON:
			if ((rand() % 20 + DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].str + 1) > 9)
			{
				attack = rand() % weapons[equippedWeapon] + DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].str + 1;
			}
			break;
		case WEAPONTYPE::RANGED:
			if ((rand() % 20 + DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].dex + 1) > 14)
			{
				attack = rand() % weapons[equippedWeapon] + DefaultEnemies[enumToIntEnemies(currentEnemies[currentEnemySpot])].dex + 3;
			}
			break;
		}

		attack += increasedDamage;

		increasedDamage = 0;

		return attack;
	}
	return 0;
}


void Encounter::unique()
{
	if (PlayableCharacters[enumToIntCharacters(currentTeam[currentTeamSpot])].mag > 0)
	{
		PlayableCharacters[enumToIntCharacters(currentTeam[currentTeamSpot])].mag--;
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
			currentScreen = MENUTYPE::TARGET;
			increasedDamage = PlayableCharacters[enumToIntCharacters(currentTeam[currentTeamSpot])].maxMag;
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
	else
		currentScreen = MENUTYPE::WEAPONS;
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
	for (int i = 0; i < 4; i++)
	{
		PlayableCharacters[enumToIntCharacters(currentTeam[i])].exp += tempExp;
		/*while (levels[lvl + 1] <= exp)
		{
			levelUp(i);
		}*/
		if (PlayableCharacters[enumToIntCharacters(currentTeam[i])].exp >= levels[PlayableCharacters[enumToIntCharacters(currentTeam[i])].lvl])
			currentScreen = MENUTYPE::LEVEL_UP;

		std::cout << "xp: " << PlayableCharacters[enumToIntCharacters(currentTeam[i])].exp
			<< "\nxp gained: " << tempExp << "\n";
		std::cout << "lvl: " << PlayableCharacters[enumToIntCharacters(currentTeam[i])].lvl
			<< "\n" << "xp needed: " <<levels[PlayableCharacters[enumToIntCharacters(currentTeam[i])].lvl]
			<< "\n";
	}
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
