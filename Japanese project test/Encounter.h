#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Player.h"
#include "Level.h"


constexpr int NUMOFWEAPONS = 17, NUMOFRANGED = 5, NUMOFITEMS = 4;


enum class MENUTYPE : unsigned char
{
	ACTIONS,
	WEAPONS, 
	INVENTORY
};

enum class WEAPONTYPE : unsigned char
{
	PIERCE,
	SLASH,
	BLUDGEON,
	RANGED
};


class Encounter
{
public:
	Encounter();
	Encounter(Player&, Level&);
	~Encounter();

	void displayEncounter(sf::RenderWindow&);
	void playEncounter(sf::RenderWindow&);
	void setEncounter();

	//screens
	void ActionsMenu(sf::RenderWindow&);
	void WeaponsMenu(sf::RenderWindow&);
	void InvMenu(sf::RenderWindow&);
	void PrintActionsMenu(sf::RenderWindow&);
	void PrintWeaponsMenu(sf::RenderWindow&);
	void PrintInvMenu(sf::RenderWindow&);

	//get data
	bool getInEncounter();
	int getEncounterType();


	int attack();
	void loseHealth(int);
	void addExp(int);
	void levelUp();
	void displayStats();
	void equipWeapons();
	void useItems();
	void shop();
	void addMoney(int);

private:

	bool inEncounter = false;

	//left == true, right == false
	bool lost, burn = false, escMenuOpen = false;

	int encounterType = 0, currentMenuSelection = 0;
	MENUTYPE currentScreen = MENUTYPE::ACTIONS;

	int str, dex, hp, natArmor, maxHp;
	int lvl, exp, money,
		equippedWeapon = 1, equippedRanged = 0, equippedMagic = 0, weapon, activeBurn = 0;
		//possession
		/*meleeOwned[NUMOFMELEE] = {0, 1, 0, 0, 0, 0, 0, 0},
		rangedOwned[NUMOFRANGED] = { 0, 0, 0, 0, 0 },
		itemsOwned[NUMOFITEMS] = { 0, 5, 0, 0 };*/

	//levels
	const int levels[10] = { 0, 5, 15, 30, 50, 75, 105, 140, 180, 225 },
		//effect
			//piercing
		weapons[NUMOFWEAPONS] = { 4, 10, 12, 16,
		//slashing
		4, 7, 9, 12, 14,
		//bludgeoning
		6, 9, 12, 17,
		//ranged
		8, 12, 17, 21 },

		//ranged[NUMOFRANGED] = { 0, 10, 12, 8, 0 },
		items[NUMOFITEMS] = { 0, 3, 6, 0 },
		//cost
		meleeCost[NUMOFWEAPONS] = { 0, 10, 18, 30, 0, 0, 0, 0 },
		//rangedCost[NUMOFRANGED] = { 0, 20, 26, 30, 0 },
		itemsCost[NUMOFITEMS] = { 0, 4, 6, 14 };
		//burn delete?
		//meleeBurn[NUMOFWEAPONS] = { 0, 0, 0, 0 },
		//rangedBurn[NUMOFRANGED] = { 0, 0, 0, 0 },
		//itemsBurn[NUMOFITEMS] = { 0, 0, 0, 0 };
	
	/**
	 * Holds the data necessary to define a specific weapon
	 * 
	 * @param name_ The name of the weapon.
	 * @param type_ The type of weapon it is.
	 * 
	 */
	struct Weapon
	{
		// The name of the weapon.
		const wchar_t* name;

		// The type of weapon it is.
		const WEAPONTYPE type;

		Weapon(const wchar_t* name_, WEAPONTYPE type_) : name(name_), type(type_) {}
	};

	// Weapons
	const Weapon WEAPONS[NUMOFWEAPONS] =
	{
		{L"ぼう",			WEAPONTYPE::PIERCE},
		{L"す　やり",			WEAPONTYPE::PIERCE},
		{L"おみ　やり",		WEAPONTYPE::PIERCE},
		{L"じゅもんじ　やり",	WEAPONTYPE::PIERCE},
		{L"たんと",			WEAPONTYPE::SLASH},
		{L"わきざし",			WEAPONTYPE::SLASH},
		{L"ちょくと",			WEAPONTYPE::SLASH},
		{L"つるぎ",			WEAPONTYPE::SLASH},
		{L"かたな",			WEAPONTYPE::SLASH},
		{L"こんぼう",			WEAPONTYPE::BLUDGEON},
		{L"spiked bat",		WEAPONTYPE::BLUDGEON}, // Translate
		{L"morningstar",	WEAPONTYPE::BLUDGEON}, // Translate
		{L"war hammer",		WEAPONTYPE::BLUDGEON}, // Translate
		{L"Ninja star",		WEAPONTYPE::RANGED},   // Translate
		{L"Chakram",		WEAPONTYPE::RANGED},   // Translate
		{L"Bow",			WEAPONTYPE::RANGED},   // Translate
		{L"Crossbow" ,		WEAPONTYPE::RANGED}    // Translate
	};

	sf::String rangedStr[NUMOFRANGED] = { L"Nothing equipped", L"Ninja star", L"Chakram", L"Bow", L"Crossbow" },
			   itemStr[NUMOFITEMS] = { "Nothing equipped", "Small health potion", "Large health potion", "Full heal" };
	//weapon type
	const wchar_t* tee = L"test";

	sf::String test = tee;
};

