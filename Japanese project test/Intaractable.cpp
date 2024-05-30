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


void Intaractable::talk(sf::RenderWindow&, int)
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
