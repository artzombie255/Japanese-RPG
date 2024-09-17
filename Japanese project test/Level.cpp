#include "Level.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <windows.h>


Level::Level()
{
	rect.setSize(sf::Vector2f(25, 25));
	sprite.setScale(sf::Vector2f(3.125, 3.125));
}


Level::~Level()
{
	for (int i = wallVec.size() - 1; i >= 0; i--)
	{
		delete wallVec.at(i);
	}
}


void Level::loadLevel(DoubleSubscriptedArray& arr, std::string fileName)
{
	std::ifstream file;
	int LY = 0, LX = 0, RY = 0, RX = 0, NumOfWalls = 0;

	
	for (int i = wallVec.size() - 1; i >= 0; i--)
	{
		delete wallVec.at(i);
	}

	file.open("./Levels/" + fileName + ".txt");

	system("cls");

	if (file.is_open())
	{
		file >> NumOfWalls;

		for (int i = 0; i < NumOfWalls; i++)
		{
			file >> LX >> LY >> RX >> RY;
			
			wallVec.push_back(new Intaractable);
			wallVec.at(i)->setSize(sf::Vector2f(RX - LX, RY - LY));
			wallVec.at(i)->setPosition(LX, LY);
			std::cout << "terst";
		}

		file.close();
	}

	img.loadFromFile("./Sprites/rooms/" + fileName + ".png");
	sprite.setTexture(img);
}


void Level::print(sf::RenderWindow& window, DoubleSubscriptedArray& arr)
{
	window.draw(sprite);

	for (int i = wallVec.size() - 1; i >= 0; i--)
		window.draw(*wallVec.at(i));
}


Intaractable* Level::getWalls(int temp)
{
	return wallVec.at(temp);
}


int Level::getWallsNum()
{
	return wallVec.size();
}
