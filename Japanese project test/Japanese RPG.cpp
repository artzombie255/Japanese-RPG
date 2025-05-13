#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Level.h"
#include "DoubleSubscriptedArray.h"
#include "Npc.h"
#include "Enemy.h"
#include "Encounter.h"
#include "Intaractable.h"
#include "globals.h"


const int WINDOWX = 600, WINDOWY = 600, NUMOFCHUNKS = 24, SIZEOFCHUNK = 25;


int main()
{
    srand(time(NULL));

    //create everything
    sf::View viewport;
    sf::Font font;
    sf::String hdr;
    sf::Text text;
    Player player;
    Level level;
    Encounter encounter;
    int xScreen = 1, yScreen = 3, enemyEncounterNum = 0, enemySpawn = 0;
    DoubleSubscriptedArray arr(NUMOFCHUNKS, NUMOFCHUNKS);
    std::vector<Intaractable*> Npcs;
    std::vector<Intaractable*> Enemies;
    std::vector<Intaractable*> wallVec;
    bool inMenu = false, printWalls = false, addedCharacter[4] = {}, startedAshton = false, startedSensei = false, upgradedEnemies = false;

    viewport.setSize(600, 600);
    viewport.setCenter(300, 1500);

    //create entities
  
    Npcs.push_back(new Npc(BLANK));
    Npcs.push_back(new Npc(AERYK));
    Npcs.push_back(new Npc(AUBREY));
    Npcs.push_back(new Npc(ROWAN));
    Npcs.push_back(new Npc(BOOK));
    Npcs.push_back(new Npc(STEVE));
    Npcs.push_back(new Npc(CHARACTERS::ASHTON));
    Npcs.push_back(new Npc(CHARACTERS::SENSEI));

    //for (int i = 0; i < 1; i++)

    Enemies.push_back(new Enemy(0, 0, 3430));
    Enemies.push_back(new Enemy(0, 60, 3430));
    Enemies.push_back(new Enemy(0, 120, 3430));
    Enemies.push_back(new Enemy(0, 180, 3430));
    Enemies.push_back(new Enemy(0, 240, 3430));
    Enemies.push_back(new Enemy(0, 300, 3430));
    Enemies.push_back(new Enemy(0, 360, 3430));
    Enemies.push_back(new Enemy(0, 420, 3430));
    Enemies.push_back(new Enemy(0, 480, 3430));
    Enemies.push_back(new Enemy(0, 0, 3370));
    Enemies.push_back(new Enemy(0, 0, 3310));
    Enemies.push_back(new Enemy(0, 0, 3250));
    Enemies.push_back(new Enemy(0, 0, 3200));
    Enemies.push_back(new Enemy(0, 480, 3370));
    Enemies.push_back(new Enemy(0, 480, 3310));
    Enemies.push_back(new Enemy(0, 480, 3250));
    Enemies.push_back(new Enemy(0, 480, 3200));

    Enemies.push_back(new Enemy(2, -1000, 3200));
    //Enemies.push_back(new Enemy(2, 500, 1800));


    //set up doing tect and window name
    font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
    hdr = L"日本語プロジェクト";
    text.setFont(font);
    //make window
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), hdr);
    window.setView(viewport);

    window.setFramerateLimit(60);

    //load the first level
    level.loadLevel(arr, "1level3", wallVec, 1, 3, viewport);

    level.addWalls(5);
    wallVec.push_back(new Intaractable);
    wallVec.at(wallVec.size() - 1)->setSize(sf::Vector2f(5400, 7));
    wallVec.at(wallVec.size() - 1)->setPosition(-2400, -600);

    wallVec.push_back(new Intaractable);
    wallVec.at(wallVec.size() - 1)->setSize(sf::Vector2f(5400, 7));
    wallVec.at(wallVec.size() - 1)->setPosition(-2400, 3593);

    wallVec.push_back(new Intaractable);
    wallVec.at(wallVec.size() - 1)->setSize(sf::Vector2f(7, 5400));
    wallVec.at(wallVec.size() - 1)->setPosition(2993, -600);

    wallVec.push_back(new Intaractable);
    wallVec.at(wallVec.size() - 1)->setSize(sf::Vector2f(7, 5400));
    wallVec.at(wallVec.size() - 1)->setPosition(-2400, -600);

    wallVec.push_back(new Intaractable);
    wallVec.at(wallVec.size() - 1)->setSize(sf::Vector2f(100, 600));
    wallVec.at(wallVec.size() - 1)->setPosition(-175, 3000);

    /*for (int i = 0; i <= wallVec.size() - 1; i++)
    {
        wallVec.push_back(new Intaractable);
        wallVec.at(i) = level.getWalls(i);
    }*/

    //main loop
    while (window.isOpen() && encounter.playerAlive() == true)
    {

        //sets if in encounter
        for (int i = 0; i < Enemies.size(); i++)
        {
            if (Enemies.at(i)->getInteraction() == true)
            {
                enemyEncounterNum = i;
                encounter.setEncounter(0);
                Enemies.at(i)->setInteraction(false);
            }
        }

        //events go here
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //checks the player movement
            player.moveCheck();
            //opens the esc menu
            player.escMenu(window);

            //click to keep talking
            for (int i = 0; Npcs.size() > i; i++)
            {
                if (player.getEscMenuOpen() == false)
                    Npcs.at(i)->continueTalking(window);
            }

            //encounter
            if (encounter.getInEncounter() == true)
            {
                viewport.setCenter(300, 300);
                encounter.playEncounter(window);
                if (encounter.endEncounter() == true)
                {
                    std::cout << "end encounter: " << enemyEncounterNum;
                    if (enemyEncounterNum < Enemies.size() && Enemies.size() != 1)
                    {
                        for (int i = enemyEncounterNum; i < Enemies.size() - 1; i++)
                        {
                            Enemies.at(i) = Enemies.at(i + 1);
                        }
                    }
                    Enemies.pop_back();

                }
            }
            else
            {
                viewport.setCenter((600.f * player.getScreenX()) - 300, (600.f * player.getScreenY()) - 300);
            }

            window.setView(viewport);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                printWalls = true;
                window.setFramerateLimit(240);
            }
            else
            {
                printWalls = false;
                window.setFramerateLimit(60);
            }

        }


        if (encounter.getInEncounter() == false)
        {
            //std::cout << "out of enmcopnter\n";
            if (rand() % 1800 + 600 <= enemySpawn && addedCharacter[0] == true)
            {
                Enemies.push_back(new Enemy(1, xScreen, yScreen));
                enemySpawn = 0;
            }
            else
                enemySpawn++;
        }
        inMenu = false;
        //sets if in esc menu
        for (int i = 0; Npcs.size() > i; i++)
        {
            if (Npcs.at(i)->getInteraction() == true)
                inMenu = true;
        }
        if (player.getEscMenuOpen() == true)
            inMenu = true;
  

        //check collisions
        //move the player
        if (inMenu == false && encounter.getInEncounter() == false &&
            player.collision(Npcs, INTERACTIONTYPE::NPC) == false &&
            player.collision(Enemies, INTERACTIONTYPE::ENEMY) == false &&
            player.collision(wallVec, INTERACTIONTYPE::WALL) == false
            )
        {
            player.move();
        }
        if (inMenu == false && encounter.getInEncounter() == false)
            for (int i = 0; i < Enemies.size(); i++)
            {
                Enemies.at(i)->move(player.getPosition().x, player.getPosition().y, wallVec);
            }

        //checks the screen the player is on
        if (xScreen != player.getScreenX() || yScreen != player.getScreenY())
        {
            /*for (int i = wallVec.size() - 1; i > 0; i--)
            {
                delete wallVec.at(i);
            }*/
            //wallVec.clear();
            std::cout << "switchLevel";
            xScreen = player.getScreenX();
            yScreen = player.getScreenY();
            level.loadLevel(arr, std::to_string(xScreen) + "level" + std::to_string(yScreen), wallVec, xScreen, yScreen, viewport);
            window.setView(viewport);
            /*for (int i = 0; i <= wallVec.size() - 1; i++)
            {
                wallVec.push_back(new Intaractable);
                wallVec.at(i) = level.getWalls(i);
            }*/
        }

        //prints the next window
        window.clear();

        level.print(window, arr);
        for (int i = 0; i < Enemies.size(); i++)
        {
            //window.draw(*Enemies.at(i));
            Enemies.at(i)->print(window);
        }

        if (printWalls == true)
            for (int i = wallVec.size() - 1; i >= 0; i--)
                window.draw(*wallVec.at(i));

        window.draw(player);


        //print npcs
        for (int i = Npcs.size() - 1; i >= 0; i--)
        {
            Npcs.at(i)->print(window);
        }

        for (int i = Enemies.size() - 1; i >= 0; i--)
        {
            Enemies.at(i)->print(window);
        }

        level.printF(window, arr);

        //interactions with entities
        for (int i = 0; Npcs.size() > i; i++)
        {
            if (Npcs.at(i)->getInteraction() == true)
            {
                Npcs.at(i)->talk(window, xScreen, yScreen);
                //std::cout << Npcs.at(i)->getCurrentInteraction();
             

            }
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 1)
        {
            Npcs.at(0)->setSize(sf::Vector2f(0, 0));
            Npcs.at(0)->setPosition(-1000, -1000);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 2)
        {
            level.updateRoom(1, 1);
            Npcs.at(1)->setPosition(-1000, -1000);
            Npcs.at(1)->setSize(sf::Vector2f(0, 0));
            Npcs.at(2)->setPosition(-1000, -1000);
            Npcs.at(2)->setSize(sf::Vector2f(0, 0));
            Npcs.at(0)->setSize(sf::Vector2f(1200, 25));
            Npcs.at(0)->setPosition(-300, 3000);
            if (addedCharacter[0] == false)
            {
                encounter.addToTeam(CHARACTERS::AUBREY);
                addedCharacter[0] = true;
            }
            if (addedCharacter[1] == false)
            {
                encounter.addToTeam(CHARACTERS::AERYK);
                addedCharacter[1] = true;
            }
        }
        
        if (Npcs.at(0)->getCurrentInteraction() >= 3)
        {
            Npcs.at(0)->setSize(sf::Vector2f(500, 600));
            Npcs.at(0)->setPosition(1870, -600);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 4)
        {
            Npcs.at(0)->setSize(sf::Vector2f(0, 0));
            Npcs.at(0)->setPosition(-1000, -1000);
            Npcs.at(3)->setPosition(2210, -157);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 5)
        {   
            Npcs.at(4)->setSize(sf::Vector2f(25, 25));
            Npcs.at(4)->setPosition(2210, 2100);
            Npcs.at(3)->setPosition(-1000, -1000);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 6)
        {
            Npcs.at(4)->setSize(sf::Vector2f(0, 0));
            Npcs.at(4)->setPosition(-1000, -1000);
            Npcs.at(3)->setPosition(2210, -157);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 7)
        {
            Npcs.at(3)->setSize(sf::Vector2f(0, 0));
            Npcs.at(3)->setPosition(-1000, -1000);
            if (addedCharacter[2] == false)
            {
                encounter.addToTeam(CHARACTERS::ROWAN);
                addedCharacter[2] = true;
                encounter.upgradeEnemies();
            }
            Npcs.at(0)->setSize(sf::Vector2f(600, 600));
            Npcs.at(0)->setPosition(0, 3100);
            Npcs.at(5)->setPosition(275, 3500);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 8)
        {
            Npcs.at(0)->setSize(sf::Vector2f(0, 0));
            Npcs.at(0)->setPosition(-1000, -1000);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 9)
        {
            Npcs.at(5)->setSize(sf::Vector2f(0, 0));
            Npcs.at(5)->setPosition(-1000, -1000);
            level.updateRoom(0, 6);
            Npcs.at(6)->setSize(sf::Vector2f(50, 50));
            Npcs.at(6)->setPosition(-300, 3200);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 10)
        {
            if (startedAshton == false)
            {
                encounter.setEncounter(1);
                startedAshton = true;
            }
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 11)
        {
            Npcs.at(6)->setPosition(-3000, -1000);
            if (addedCharacter[3] == false)
            {
                encounter.addToTeam(CHARACTERS::ASHTON);
                addedCharacter[3] = true;
            }
            Npcs.at(0)->setSize(sf::Vector2f(540, 600));
            Npcs.at(0)->setPosition(-1200, 3000);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 12)
        {
            Npcs.at(0)->setSize(sf::Vector2f(0, 0));
            Npcs.at(0)->setPosition(-1200, -1000);
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 13)
        {
            if (startedSensei == false)
            { 
                encounter.setEncounter(2);
                startedSensei = true;
            }
            if (encounter.getInEncounter() == false)
            {
                Npcs.at(0)->setSize(sf::Vector2f(540, 600));
                Npcs.at(0)->setPosition(-1200, 3000);
            }
        }

        if (Npcs.at(0)->getCurrentInteraction() >= 14)
        {
            Npcs.at(7)->setPosition(-1200, -1000);
        }

        //std::cout << "x: " << xScreen << "\ny: " << yScreen << "\n";
        //std::cout << level.getInCave();

        for (int i = 0; i < 4; i++)
        {
            //encounter.printTeamSpot(i);
        }

        //display encounters
        if (encounter.getInEncounter() == true)
            encounter.displayEncounter(window);

        player.printEscMenu(window);
        window.display();
    }

    //clean up
    for (int i = Npcs.size() - 1; i >= 0; i--)
    {
        delete Npcs.at(i);
    }

    for (int i = Enemies.size() - 1; i >= 0; i--)
    {
        delete Enemies.at(i);
    }

    for (int i = wallVec.size() - 1; i >= 0; i--)
    {
        delete wallVec.at(i);
    }
    return 0;
}