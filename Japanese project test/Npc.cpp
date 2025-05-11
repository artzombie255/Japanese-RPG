#include "Npc.h"
#include <iostream>

int Npc::CurrentInteraction = 0;
int Npc::currentLine = 0;
int Npc::inputDelay = 0;
sf::String Npc::voiceLines[42] = { L"Aubrey：助けてください！", 
L"Aubrey：ゾンビたちは私たちを\n驚かしました。", 
L"Aeryk：ゾンビが多過ぎます。",
L"Aubrey：こちらはだめです。", 
L"Aeryk：私たちを助けてくれるなら、\n私は転石が押せます。", 
L"Aeryk：行きましょう！",
L"Aubrey：私たちははしを渡りたいなら、\nはしを直さなければなりません。",
L"Aeryk：うん、そうね、\n誰が橋を直せるでしょう。",
L"Rowan：誰ですか？！\nゾンビは帰ってくれませんか。私はおいしくない。"};
int Npc::voiceLinesLength[10] = {0, 5, 7, 9};




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
		img.loadFromFile("./Sprites/characters/AE_L.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(225, 3200);
		break;
	case ASHTON:
	case AUBREY:
		img.loadFromFile("./Sprites/characters/AU_R.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(300, 3200);
		break;
	case PHOENIX:
	case ROWAN:
	case STEVE:
	case BRIT:
	case KIMORA:
	case ALEX:
	case LEAH:
	case NATHAN:
	case BLANK:
		setSize(sf::Vector2f(600, 600));
		setPosition(0, 3100);
		break;
	}


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
		if (voiceLinesLength[CurrentInteraction] == currentLine)
		{
			std::cout << currentLine;
			currentLine++;
			CurrentInteraction++;
			interaction = false;
			std::cout << "interacted" << CurrentInteraction;


		}
		else
		{
			std::cout << currentLine;
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
