#include "Level.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <windows.h>


Level::Level()
{
	rect.setSize(sf::Vector2f(25, 25));
	sprite.setScale(sf::Vector2f(3.125, 3.125));
	foreground.setScale(sf::Vector2f(3.125, 3.125));
}


Level::~Level()
{
}


void Level::loadLevel(DoubleSubscriptedArray& arr, std::string fileName, std::vector<Intaractable*> &wallVec, int x, int y, sf::View &viewport)
{
	std::ifstream file;
	int LY = 0, LX = 0, RY = 0, RX = 0, NumOfWalls = 0;

	//oneLevelThreeUpdated = true;
	if (fileName == "1level3" && oneLevelThreeUpdated == false)
		fileName = "p" + fileName;

	if (fileName == "0level6" && zeroLevelSixUpdated == false)
		fileName = "p" + fileName;
	
	//for (int i = wallVec.size() - 1; i >= 0; i--)
	//{
		//delete wallVec.at(i);
	//}

	if ((x == 1 && y == 3) || (x == 3 && y == 0))
		inCave = false;
	
	if ((x == 1 && y == 2) || (x == 2 && y == 0))
		inCave = true;

	//if ((x == 4 && y == 0) || (x == 5 && y == 0) || (x == 4 && y == 1))
		//inCave = false;

	file.open("./Levels/" + fileName + ".txt");

	system("cls");

	if (file.is_open())
	{
		file >> NumOfWalls;

		if (loaded[x + 3][y] == false)
		{
			for (int i = 0; i < NumOfWalls; i++)
			{
				file >> LX >> LY >> RX >> RY;

				wallVec.push_back(new Intaractable);
				wallVec.at(i + totalWalls)->setSize(sf::Vector2f(RX - LX, RY - LY));
				wallVec.at(i + totalWalls)->setPosition(LX + ((x - 1) * 600), LY + ((y - 1) * 600));
				std::cout << "terst";
			}
			loaded[x + 3][y] = true;
			totalWalls += NumOfWalls;
		}
		if (x == 1 && y == 3 && oneLevelThreeUpdated == true)
		{
			for (int i = 0; i < NumOfWalls; i++)
			{
				file >> LX >> LY >> RX >> RY;
				wallVec.at(i)->setSize(sf::Vector2f(RX - LX, RY - LY));
				wallVec.at(i)->setPosition(LX + ((x - 1) * 600), LY + ((y - 1) * 600));
			}
		}
		if (zeroLevelSixUpdated == true)
		{
			wallVec.at(12)->setSize(sf::Vector2f(0, 0));
			wallVec.at(12)->setPosition(-1000, -1000);
		}

		file.close();
	}

	if (inCave == false)
		img.loadFromFile("./Sprites/rooms/" + fileName + ".png");
	else
		img.loadFromFile("./Sprites/rooms/c" + fileName + ".png");
	sprite.setTexture(img);
	sprite.setPosition((600 * x) - 600, (600 * y) - 600);


	if ((x == 1 && y == 3 && oneLevelThreeUpdated == true) || (x == 1 && y == 2) || (x == 2 && y == 0) || (x == 3 && y == 0)
		|| (x == 0 && y == 3) || (x == 0 && y == 4) || (x == 1 && y == 4) || (x == 2 && y == 4)
		|| (x == 4 && y == 0) || (x == 4 && y == 1) || (x == 5 && y == 0) || (x == 4 && y == 4) || (x == 5 && y == 4))
	{
		imgF.loadFromFile("./Sprites/rooms/f" + fileName + ".png");
		foreground.setTexture(imgF);
		foreground.setPosition((600 * x) - 600, (600 * y) - 600);
	}
	viewport.setCenter((600.f * x) - 300, (600.f * y) - 300);
}


void Level::print(sf::RenderWindow& window, DoubleSubscriptedArray& arr)
{
	window.draw(sprite);

	//for (int i = wallVec.size() - 1; i >= 0; i--)
		//window.draw(*wallVec.at(i));
}

void Level::printF(sf::RenderWindow& window, DoubleSubscriptedArray&)
{
	window.draw(foreground);
}


void Level::updateRoom(int x, int y)
{
	if (x == 1)
		oneLevelThreeUpdated = true;
	else
		zeroLevelSixUpdated = true;
}
