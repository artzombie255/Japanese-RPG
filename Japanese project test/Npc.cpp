#include "Npc.h"
#include <iostream>


Npc::Npc()
{

	setSize(sf::Vector2f(50, 50));
	setPosition(100,100);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 2; j++)
			voiceLines[i][j] = std::to_string(i);
	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);
}


Npc::Npc(int)
{
	setSize(sf::Vector2f(50, 50));
	setPosition(100, 100);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 10; j++)
			voiceLines[i][j] = std::to_string(j);
	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);


}


Npc::~Npc()
{
}


void Npc::continueTalking(sf::RenderWindow& window)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);

	inputDelay++;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && interaction == true 
		&& inputDelay > 5 && position.y > 300)
	{
		currentLine++;
		inputDelay = 0;
	}
}


void Npc::talk(sf::RenderWindow &window, int person)
{
	//do magic
	sf::RectangleShape outline, background;

	outline.setSize(sf::Vector2f(600, 300));
	outline.setPosition(0, 300);

	background.setSize(sf::Vector2f(580, 280));
	background.setPosition(10, 310);
	background.setFillColor(sf::Color::Black);

	text.setPosition(20, 320);

	window.draw(outline);
	window.draw(background);


	if (person < 6)
		text.setString(voiceLines[person][currentLine]);
	else
		std::cout << "above 6";
	window.draw(text);
}
