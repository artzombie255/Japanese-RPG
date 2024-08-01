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
	sf::RectangleShape MenuOutline, MenuBackground, background;

	background.setSize(sf::Vector2f(600, 600));
	background.setFillColor(sf::Color::Black);

	MenuOutline.setSize(sf::Vector2f(600, 200));
	MenuOutline.setPosition(0, 400);

	MenuBackground.setSize(sf::Vector2f(580, 180));
	MenuBackground.setPosition(10, 410);
	MenuBackground.setFillColor(sf::Color::Black);

	//text.setPosition(20, 320);

	window.draw(background);
	window.draw(MenuOutline);
	window.draw(MenuBackground);

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
	sf::Vector2i position = sf::Mouse::getPosition(window);


	/*if (position.x > 150 && position.x < 450)
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
	}*/
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
