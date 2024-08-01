#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Level.h"


enum class MENUTYPE
{
	ACTIONS,
	WEAPONS
};


class Encounter
{
public:
	Encounter();
	Encounter(Player&, Level&);
	~Encounter();

	void displayEncounter(sf::RenderWindow&);
	void playEncounter(sf::RenderWindow&);
	void setEncounter();

	//screens
	void ActionsMenu(sf::RenderWindow&);
	void WeaponsMenu(sf::RenderWindow&);

	//get data
	bool getInEncounter();
	int getEncounterType();

private:
	bool inEncounter = false;
	int encounterType, currentMenuSelection = 0;
	MENUTYPE currentScreen;

};

