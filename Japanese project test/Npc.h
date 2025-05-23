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

	void continueTalking(sf::RenderWindow&, int);
	void talk(sf::RenderWindow&, int, int, int); 
	void print(sf::RenderWindow&);


private:
	//AUBREY, ASHTON, AERYK, LILLY, KIMORA, SHIN
	static sf::String voiceLines[43];
	static sf::String individualVoiceLines[3];
	static int voiceLinesLength[15];
	sf::Font font;
	sf::Text text;
	static int inputDelay;
	int leahLine;
};

