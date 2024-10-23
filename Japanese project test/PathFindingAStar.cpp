#include "PathFindingAStar.h"


PathFindingAStar::PathFindingAStar()
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			nodeArr[j][i].setNode(sf::Vector2i(i * 50, j * 50));
		}
	}


}


PathFindingAStar::~PathFindingAStar()
{

}


PathFindingAStar::nodes::nodes()
{

}


PathFindingAStar::nodes::~nodes()
{

}


void PathFindingAStar::nodes::setNode(sf::Vector2i newNode)
{
	node = newNode;
}
