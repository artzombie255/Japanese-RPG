#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Intaractable.h"
#include "globals.h"


class Npc : public Intaractable
{
public:
	Npc();
	Npc(enum CHARACTERS);
	~Npc();

	void continueTalking(sf::RenderWindow&);
	void talk(sf::RenderWindow&, int, int);

private:
	//AUBREY, ASHTON, AERYK, LILLY, KIMORA, SHIN
	std::string voiceLines[10];
	int voiceLinesLength[10], CurrentInteraction = 0;
	sf::Font font;
	sf::Text text;
	int currentLine = 0, inputDelay = 0;
};

