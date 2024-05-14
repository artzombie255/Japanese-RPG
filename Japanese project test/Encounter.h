#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Level.h"


class Encounter
{
public:
	Encounter();
	Encounter(Player&, Level&);
	~Encounter();

	//get data
	bool getInEncounter();
	int getEncounterType();


private:
	bool inEncounter = false;
	int encounterType;

};

