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
	virtual void talk(sf::RenderWindow&, int);
	virtual void nextLine();
	void increaseLength(int person);

protected:
	bool interaction = false;
	int currentLine = 0, currentLength[6] = {};;

};

