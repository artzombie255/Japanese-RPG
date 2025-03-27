#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class Intaractable : public sf::RectangleShape
{
public:
	Intaractable();
	~Intaractable();

	virtual void continueTalking(sf::RenderWindow&);
	void setInteraction(bool);
	bool getInteraction();
	virtual void talk(sf::RenderWindow&, int, int);
	virtual void nextLine();
	void increaseLength(int person);
	void print(sf::RenderWindow&);
	virtual void move(int, int, std::vector<Intaractable*>&);

protected:
	bool interaction = false;
	int currentLine = 0, currentLength[6] = {};
	sf::Texture img;
	sf::Sprite sprite;
};

