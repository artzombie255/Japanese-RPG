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
		ActionsMenu(window);
	case MENUTYPE::WEAPONS:
		WeaponsMenu(window);
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

	//esc menu selection
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentMenuSelection >= 0)
	{
		switch (currentMenuSelection)
		{
		case 0:
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

	switch (currentScreen)
	{
	case MENUTYPE::ACTIONS:
		ActionsMenu(window);
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
}


void Encounter::WeaponsMenu(sf::RenderWindow &window)
{

}


bool Encounter::getInEncounter()
{
	return inEncounter;
}


int Encounter::getEncounterType()
{
	return encounterType;
}
