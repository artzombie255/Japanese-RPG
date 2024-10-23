#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

class PathFindingAStar
{

public:
	PathFindingAStar();
	~PathFindingAStar();

	

private:

	class nodes
	{
	public:
		nodes();
		~nodes();

		void setNode(sf::Vector2i);

	private:
		sf::Vector2i node;
		short f, g, h;
	};

	nodes nodeArr[12][12];


	std::vector<nodes> closedList, openList;
};

