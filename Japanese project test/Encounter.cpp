#include "Encounter.h"


Encounter::Encounter()
{
}


Encounter::Encounter(Player& player, Level& level)
{

}


Encounter::~Encounter()
{
}


bool Encounter::getInEncounter()
{
	return inEncounter;
}


int Encounter::getEncounterType()
{
	return encounterType;
}
