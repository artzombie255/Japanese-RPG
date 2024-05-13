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


private:
	bool inEncounter = false;

};

