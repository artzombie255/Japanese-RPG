#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Player.h"
#include "Level.h"
#include "globals.h"


constexpr int NUMOFWEAPONS = 17, NUMOFRANGED = 5, NUMOFITEMS = 4;


enum class MENUTYPE : unsigned char
{
	ACTIONS,
	WEAPONS, 
	INVENTORY,
	TARGET,
	CHARACTER_TARGET,
	LEVEL_UP
};

enum class WEAPONTYPE : unsigned char
{
	PIERCE,
	SLASH,
	BLUDGEON,
	RANGED,
	MELEE
};


enum ENEMIES
{
	BLANK_E = 0,
	BSPEAR,
	DAGGER,
	STAFF,
	SPEAR,
	SWORD,
	CLUB,
	ASHTONE,
	SENSEIE
};



class Encounter
{
public:
	Encounter();
	Encounter(Player&, Level&);
	~Encounter();
	
	bool endEncounter();

	void upgradeEnemies();

	void addToTeam(CHARACTERS);
	void printTeamSpot(int);
	void changeTeam();

	void displayEncounter(sf::RenderWindow&);
	void playEncounter(sf::RenderWindow&);
	void setEncounter(int);

	void switchTurn();

	void enemiesTurn();

	//screens
	void ActionsMenu(sf::RenderWindow&);
	void WeaponsMenu(sf::RenderWindow&);
	void InvMenu(sf::RenderWindow&);
	void targetMenu(sf::RenderWindow&);
	void targetCharacterMenu(sf::RenderWindow&);
	void levelUpMenu(sf::RenderWindow&);

	void PrintActionsMenu(sf::RenderWindow&);
	void PrintWeaponsMenu(sf::RenderWindow&);
	void PrintInvMenu(sf::RenderWindow&);
	void printTargetMenu(sf::RenderWindow&);
	void printTargetCharacterMenu(sf::RenderWindow&);
	void printLevelUpMenu(sf::RenderWindow&);

	//get data
	bool getInEncounter();
	int getEncounterType();

	int enumToIntCharacters(CHARACTERS);
	int enumToIntEnemies(ENEMIES);

	void addToParty(CHARACTERS);

	bool playerAlive();

	int attack();
	int enemiesAttack();
	void unique();
	void loseHealth(int);
	void addExp(int);
	void displayStats();
	void equipWeapons();
	void useItems();
	void shop();
	void addMoney(int);

private:

	bool inEncounter = false;

	//left == true, right == false
	bool lost, burn = false, escMenuOpen = false;

	int encounterType = 0, currentMenuSelection = 0, currentLeveling = 0;
	MENUTYPE currentScreen = MENUTYPE::ACTIONS;
	bool enemyAlive[4] = { true, false, false, false }, enemiesAlive = true;
	int str, dex, hp, natArmor, maxHp;
	int lvl, exp, money,
		equippedWeapon = 1, weapon, activeBurn = 0,
		enemyHp[4] = {10, 0, 0, 0}, currentTeamSpot = 0, enemyTurn = 0, currentEnemySpot = 0,
		//used for Aeryk's unique
		targetingTeam[4] = {0, 1, 2, 3},
		targetedCharacter,
		//possession
		meleeOwned[NUMOFWEAPONS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		itemsOwned[NUMOFITEMS] = { 0, 5, 0, 0 }, increasedDamage = 0, upgradedEnemies = 0, totalTeam = 0;
	CHARACTERS currentTeam[4] = { CHARACTERS::BLANK,  CHARACTERS::BLANK, CHARACTERS::BLANK, CHARACTERS::BLANK };
	ENEMIES currentEnemies[4] = { ENEMIES::BLANK_E,  ENEMIES::BLANK_E, ENEMIES::BLANK_E, ENEMIES::BLANK_E };

	std::vector<CHARACTERS> team;
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
	/*const wchar_t* tee = L"test";

	sf::String test = tee;*/


	/**
	* int str, dex, hp, natArmor, maxHp;
	int lvl, exp, money,
		equippedWeapon = 1,

	 * Holds the data necessary to define Characters
	 *
	 * @param name_ The name of the character.
	 * @param type_ The type of weapon they can use.
	 *
	 */
	struct Characters
	{
		// The name of the weapon.
		const CHARACTERS name;

		// The type of weapon it is.
		const WEAPONTYPE type;

		int maxHp, hp, armor, str, dex, mag, maxMag, lvl, exp, equippedWeapon;

		Characters(CHARACTERS name_, WEAPONTYPE type_, int maxHp_, int hp_, int armor_, int str_,
			int dex_, int mag_, int maxMag_, int lvl_, int exp_, int equippedWeapon_) : 
			name(name_), type(type_), maxHp(maxHp_), hp(hp_), armor(armor_), str(str_), dex(dex_), 
			mag(mag_), maxMag(maxMag_), lvl(lvl_), exp(exp_), equippedWeapon(equippedWeapon_) {}
	};

	// Weapons
	static Characters PlayableCharacters[8];




	struct Enemies
	{
		// The name of the weapon.
		const ENEMIES enemyName;

		int maxHp, hp, armor, str, dex, mag, lvl, exp, equippedWeapon;

		Enemies(ENEMIES name_, int maxHp_, int hp_, int armor_, int str_,
			int dex_, int mag_, int lvl_, int exp_, int equippedWeapon_) :
			enemyName(name_), maxHp(maxHp_), hp(hp_), armor(armor_), str(str_), dex(dex_),
			mag(mag_), lvl(lvl_), exp(exp_), equippedWeapon(equippedWeapon_) {}
	};

	// Weapons
	Enemies DefaultEnemies[9] =
	{
		//name, max hp, current hp, armor, strength, dexterity, magic slots, level, xp, current weapon
		{ENEMIES::BLANK_E,	0,  0,  1, 1, 0, 1, 1, 0, 10},
		{ENEMIES::BSPEAR,	10, 10, 0, 0, 1, 0, 1, 0, 0},
		{ENEMIES::DAGGER,	10, 10, 0, 0, 1, 0, 1, 0, 4},
		{ENEMIES::STAFF,	15, 15, 0, 1, 0, 0, 1, 0, 9},
		{ENEMIES::SPEAR,	15, 15, 0, 0, 2, 0, 1, 0, 1},
		{ENEMIES::SWORD,	20, 20, 1, 1, 1, 0, 1, 0, 5},
		{ENEMIES::CLUB,		25, 25, 1, 2, 0, 0, 1, 0, 10},
		{ENEMIES::ASHTONE,  100, 100, 2, 4, 0, 0, 5, 0, 7},
		{ENEMIES::SENSEIE,   200, 200, 3, 5, 0, 0, 5, 0, 11}
	}; 

};

