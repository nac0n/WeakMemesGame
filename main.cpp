#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maps.h"
#include "Character.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "MTD: GA 3");
    sf::CircleShape shape(100.f);

	sf::RectangleShape tile0(sf::Vector2f(32, 32));
	sf::RectangleShape tile1(sf::Vector2f(32, 32));
	tile0.setFillColor(sf::Color::Green);
	tile1.setFillColor(sf::Color::Yellow);

	//GUI
	//--------------------------------------
	sf::RectangleShape gui1(sf::Vector2f(955, 635));
	gui1.setFillColor(sf::Color::Transparent);
	gui1.setOutlineThickness(5);
	gui1.setOutlineColor(sf::Color(250, 150, 100));
	//--------------------------------------


	sf::RectangleShape(sf::Vector2f(32,32));
    shape.setFillColor(sf::Color::Green);
    
	Maps test{ "map1.txt" };
	
	std::vector<Character> charList;

	cout << test.getX() << " : " << test.getY() << endl;
	//TEST FOR ANIMATION, REMOVE AFTERWARDS
	//--------------------------------------
	sf::Texture sheet;

	if (!sheet.loadFromFile("Content/spriteSheets/soldierbigsheet.png")) {
		cerr << "Fakku desu yo ne!" << endl;
	}

	sf::IntRect aniRect(0, 0, 32, 32);
	sf::Sprite aniChar(sheet, aniRect);

	aniChar.setPosition(200, 200);

	Character soldier{ "Data/soldier.txt" };
	soldier.setPosMat(test.getStartX(), test.getStartY());

	int ab{ 0 };
	//--------------------------------------

	//TRUMP TESTING
	sf::Texture trump;
	trump.loadFromFile("Content/spriteSheets/trumpfacesheet.png");
	sf::IntRect rectTrump(0, 0, 128, 128);
	sf::Sprite aniTrump(trump, rectTrump);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();

		
		//MAP
		//----------------------------------------
		for (int i{ 0 }; i < test.getX(); ++i) {
			for (int j{ 0 }; j < test.getY(); ++j) {
				if (test.getMat().at(i, j) == 0) {
					tile0.setPosition(i * 32, j * 32);
					window.draw(tile0);
				}
				else if (test.getMat().at(i, j) == 1) {
					tile1.setPosition(i * 32, j * 32);
					window.draw(tile1);
				}
			}
			
		}
		//----------------------------------------



		//CHARACTERS
		//----------------------------------------
		aniChar.setTexture(soldier.getTex());
		aniRect.left = soldier.getSheetX() * 32;
		aniRect.top = soldier.getSheetY() * 32;
		aniChar.setTextureRect(aniRect);
		aniChar.setPosition(soldier.getX(), soldier.getY());
		window.draw(aniChar);

		soldier.update(test.getMat());

		/*
		if (ab % 20 == 0) {
			if (aniRect.left == 0) {
				aniRect.left += 32;
			}
			else {
				aniRect.left = 0;
			}
		}
		if (ab % 40 == 0) {
			if (aniRect.top != 160) {
				aniRect.top += 32;
			}
			else
				aniRect.top = 0;
		}
		*/
		
		//----------------------------------------

		//TRUMP
		//----------------------------------------
		if (ab % 40 == 0) {
			if (rectTrump.left == 128) {
				rectTrump.left = 0;
			}
			else {
				rectTrump.left = 128;
			}
		}
		
		ab++;
		aniTrump.setTextureRect(rectTrump);
		aniTrump.setPosition(1000, 50);
		window.draw(aniTrump);
		//----------------------------------------

		//GUI
		//--------------------------------------
		gui1.setPosition(5, 5);
		window.draw(gui1);

		//--------------------------------------


        //window.draw(shape);
        window.display();
    }

    return 0;
}