#include "Level.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


Level::Level()
{
	rect.setSize(sf::Vector2f(25, 25));
}


Level::~Level()
{

}


void Level::loadLevel(DoubleSubscriptedArray& arr, std::string fileName)
{
	//int temp;
	std::ifstream file;
	file.open(fileName);

	if (file.is_open())
	{
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				arr(j, i) = '0';
				file >> arr(j, i);
				//arr(i, j) = temp;
				std::cout << arr(j, i);
				//system("pause");
			}
			//std::cout << std::endl;
		}
		file.close();
		//std::cout << "1 loaded";
	}
}


void Level::print(sf::RenderWindow& window, DoubleSubscriptedArray& arr)
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (arr(j, i) == '1')
				rect.setPosition(j * 25,i * 25);
			window.draw(rect);
		}
		//std::cout << std::endl;
	}
	rect.setPosition(-50, -50);
}
