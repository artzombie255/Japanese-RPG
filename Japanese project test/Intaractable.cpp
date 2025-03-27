#include "Intaractable.h"

Intaractable::Intaractable()
{
}

Intaractable::~Intaractable()
{
}


void Intaractable::continueTalking(sf::RenderWindow&)
{
}


void Intaractable::setInteraction(bool temp)
{
	interaction = temp;
	return;
}


bool Intaractable::getInteraction()
{
	return interaction;
}


void Intaractable::talk(sf::RenderWindow&, int, int)
{
}


void Intaractable::nextLine()
{
	currentLine++;
}


void Intaractable::increaseLength(int person)
{
	currentLength[person]++;
}


void Intaractable::print(sf::RenderWindow &window)
{
	sprite.setPosition(getPosition().x, getPosition().y);
	window.draw(sprite);
}


void Intaractable::move(int, int, std::vector<Intaractable*>&)
{
}
