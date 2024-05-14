#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>


extern const int WINDOWX, WINDOWY;
const int NUMOFMELEE = 8, NUMOFRANGED = 5, NUMOFITEMS = 4;

class Player : public sf::RectangleShape
{
public:
	Player();
	~Player();

	void moveCheck();
	void move();
	void collision(std::vector<sf::RectangleShape*>&, int);
	bool isLost();
	int getScreenX();
	int getScreenY();
	void escMenu(sf::RenderWindow&);
	void printEscMenu(sf::RenderWindow&);
	bool getEscMenuOpen();

	int attack();
	void loseHealth(int);
	void addExp(int);
	void levelUp();
	void displayStats();
	void openInv();
	void equipWeapons();
	void useItems();
	void shop();
	void addMoney(int);

private:
	int xMove = 0, yMove = 0, xScreen = 1, yScreen = 1, str, dex, hp, natArmor, maxHp, escDelay = 0, currentMenuSelection = 0;
	//left == true, right == false
	bool lost, burn = false, escMenuOpen = false;
	int lvl, exp, money,
		equippedMelee = 1, equippedRanged = 0, equippedMagic = 0, weapon, activeBurn = 0,
		//possession
		meleeOwned[NUMOFMELEE] = { 0, 1, 0, 0, 0, 0, 0, 0 }, 
		rangedOwned[NUMOFRANGED] = { 0, 0, 0, 0, 0 },
		itemsOwned[NUMOFITEMS] = { 0, 5, 0, 0 };
	//levels
	const int levels[10] = { 0, 5, 15, 30, 50, 75, 105, 140, 180, 225 },
		//effect
		melee[NUMOFMELEE] = { 0, 4, 6, 9 }, 
		ranged[NUMOFRANGED] = { 0, 10, 12, 8 },
		items[NUMOFITEMS] = { 0, 3, 6, 0 },
		//cost
		meleeCost[NUMOFMELEE] = { 0, 10, 18, 30, 0, 0, 0, 0 }, 
		rangedCost[NUMOFRANGED] = { 0, 20, 26, 30, 0 },
		itemsCost[NUMOFITEMS] = { 0, 4, 6, 14 },
		//burn delete?
		meleeBurn[NUMOFMELEE] = { 0, 0, 0, 0 }, 
		rangedBurn[NUMOFRANGED] = { 0, 0, 0, 0 },
	    itemsBurn[NUMOFITEMS] = { 0, 0, 0, 0 };
	//name
	const std::string meleeStr[NUMOFMELEE] = { "Nothing equipped", "Dagger", "Staff", "Spiked bat", "Morningstar", "Smallsword", "Longsword", "Katana" },
		rangedStr[NUMOFRANGED] = { "Nothing equipped", "Ninja star", "Chakram", "Bow", "Crossbow"},
		itemStr[NUMOFITEMS] = { "Nothing equipped", "Small health potion", "Large health potion", "Full heal" };
};

