#include "Npc.h"
#include <iostream>


Npc::Npc()
{

	setSize(sf::Vector2f(50, 50));
	setPosition(100,100);
	

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);
}


Npc::Npc(CHARACTERS player)
{
	setSize(sf::Vector2f(50, 50));
	setPosition(100, 100);

	switch (player)
	{
	case AERYK:
		setPosition(200, 2000);
		break;
	case ASHTON:
	case AUBREY:
		img.loadFromFile("./Sprites/characters/AU_R.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(300, 2000);
		break;
	case PHOENIX:
	case ROWAN:
	case STEVE:
	case BRIT:
	case KIMORA:
	case ALEX:
	case LEAH:
	case NATHAN:
		break;
	}

	for (int j = 0; j < 10; j++)
			voiceLines[j] = std::to_string(j);

	for (int j = 0; j < 10; j++)
			voiceLinesLength[j] = 2 * j;
	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

}


Npc::~Npc()
{
}


//manage interactions and incrementing current line
void Npc::continueTalking(sf::RenderWindow& window)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);

	inputDelay++;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && interaction == true 
		&& inputDelay > 5 && position.y > 300)
	{
		if (voiceLinesLength[CurrentInteraction] <= currentLine)
		{
			interaction = false;
			currentLine++;
			CurrentInteraction++;
		}
		else
		{
			currentLine++;
			inputDelay = 0;
		}
	}
}


//display text
void Npc::talk(sf::RenderWindow &window, int x, int y)
{
	//do magic
	sf::RectangleShape outline, background;

	outline.setSize(sf::Vector2f(600, 300));
	outline.setPosition(0 + ((x - 1) * 600), 300 + ((y - 1) * 600));

	background.setSize(sf::Vector2f(580, 280));
	background.setPosition(10 + ((x - 1) * 600), 310 + ((y - 1) * 600));
	background.setFillColor(sf::Color::Black);

	text.setPosition(20 + ((x - 1) * 600), 320 + ((y - 1) * 600));

	window.draw(outline);
	window.draw(background);

	text.setString(voiceLines[currentLine]);

	window.draw(text);
}


void Npc::print(sf::RenderWindow& window)
{
	sprite.setPosition(getPosition().x, getPosition().y);
	window.draw(sprite);
}
