#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Intaractable.h"


class Npc : public Intaractable
{
public:
	Npc();
	Npc(int);
	~Npc();

	void continueTalking(sf::RenderWindow&);
	void talk(sf::RenderWindow&, int person);

private:
	//AUBREY, ASHTON, AERYK, LILLY, KIMORA, SHIN
	std::string voiceLines[6][10];
	int voiceLinesLength[6][1];
	sf::Font font;
	sf::Text text;
	int currentLine = 0, inputDelay = 0;
};

