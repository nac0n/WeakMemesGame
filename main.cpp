#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maps.h"
#include "Character.h"
#include <chrono>

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
	gui1.setPosition(5, 5);

	sf::RectangleShape gui2(sf::Vector2f(305, 635));
	gui2.setFillColor(sf::Color::Transparent);
	gui2.setOutlineThickness(5);
	gui2.setOutlineColor(sf::Color(100, 150, 100));
	gui2.setPosition(970, 5);

	sf::RectangleShape gui3(sf::Vector2f(1270, 65));
	gui3.setFillColor(sf::Color::Transparent);
	gui3.setOutlineThickness(5);
	gui3.setOutlineColor(sf::Color(100, 150, 0));
	gui3.setPosition(5, 650);

	sf::Font font;
	// Load it from a file
	if (!font.loadFromFile("Content/Fonts/slkscr.ttf"))
	{
		cerr << "nigga that font aint right" << endl;
	    // error...
	}

	sf::Text trumpSpeech;
	trumpSpeech.setFont(font);
	trumpSpeech.setString("We need to\nbuild a wall.\n Don't let those\ndirty immigrants get\ninside our country!");

	trumpSpeech.setCharacterSize(24);
	trumpSpeech.setFillColor(sf::Color::Red);

		

	//--------------------------------------

	//TRUMP SPEECH
	//--------------------------------------

	
	

	//--------------------------------------


	//TOWER HANDLING STUFF
	//--------------------------------------
	Matrix towerMat{ 30,20 };
	towerMat.fillWith(0);
	std::vector<Character> soldiers;
	//--------------------------------------

	//MEHICANS STUFF
	//--------------------------------------
	std::vector<Character> mehicans;
	//--------------------------------------

	sf::RectangleShape(sf::Vector2f(32,32));
    shape.setFillColor(sf::Color::Green);
    
	Maps test{ "map1.txt" };
	
	std::vector<Character> charList;

	cout << test.getX() << " : " << test.getY() << endl;

	//TRUMP SPEECH TEST


	//TEST FOR ANIMATION, REMOVE AFTERWARDS
	//--------------------------------------
	sf::Texture sheet;

	if (!sheet.loadFromFile("Content/spriteSheets/soldierbigsheet.png")) {
		cerr << "Fakku desu yo ne!" << endl;
	}

	sf::IntRect aniRect(0, 0, 32, 32);
	sf::Sprite aniChar(sheet, aniRect);

	aniChar.setPosition(200, 200);

	Character soldier{ "Data/mexican.txt" };
	soldier.setPosMat(test.getStartX(), test.getStartY());

	int ab{ 0 };
	//--------------------------------------

	//TRUMP TESTING
	sf::Texture trump;
	trump.loadFromFile("Content/spriteSheets/trumpfacesheet.png");
	sf::IntRect rectTrump(0, 0, 128, 128);
	sf::Sprite aniTrump(trump, rectTrump);

	//Timer for spawns
	auto spawnTimer = std::chrono::high_resolution_clock::now();

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

		//Events
		//----------------------------------------
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int mX = sf::Mouse::getPosition(window).x;
			int mY = sf::Mouse::getPosition(window).y;

			mX /= (int)(32 * (((double)window.getSize().x) / ((double)1280)));
			mY /= (int)(32 * (((double)window.getSize().y) / ((double)720)));

			if (test.getMat().at(mX, mY) == 0 && towerMat.at(mX, mY) == 0) {
				towerMat.at(mX, mY) = 1;
				Character tmp("Data/soldier.txt");
				tmp.setPosMat(mX, mY);
				soldiers.push_back(tmp);
			}
			
			
		}
		//----------------------------------------

		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsedTime = endTime - spawnTimer;

		auto elapsed = (int)elapsedTime.count();

		
		//SPAWNING THE MEHICANS
		//----------------------------------------
		if (elapsed % 200 == 0) {
			Character tmp("Data/mexican.txt");
			tmp.setPosMat(test.getStartX(), test.getStartY());
			mehicans.push_back(tmp);
			spawnTimer = std::chrono::high_resolution_clock::now();
		}
		//----------------------------------------

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

		for (int i{ 0 }; i < soldiers.size(); ++i) {
			soldiers[i].update(test.getMat());
			

			aniChar.setTexture(soldiers[i].getTex());
			aniRect.left = soldiers[i].getSheetX() * 32;
			aniRect.top = soldiers[i].getSheetY() * 32;
			aniChar.setTextureRect(aniRect);
			aniChar.setPosition(soldiers[i].getX(), soldiers[i].getY());
			window.draw(aniChar);
		}

		for (int i{ 0 }; i < mehicans.size(); ++i) {
			mehicans[i].update(test.getMat());
			
			

			aniChar.setTexture(mehicans[i].getTex());
			aniRect.left = mehicans[i].getSheetX() * 32;
			aniRect.top = mehicans[i].getSheetY() * 32;
			aniChar.setTextureRect(aniRect);
			aniChar.setPosition(mehicans[i].getX(), mehicans[i].getY());
			window.draw(aniChar);

		}

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
		if (ab % 30 == 0) {
			if (rectTrump.left == 384) {
				rectTrump.left = 0;
			}
			else {
				rectTrump.left += 128;
			}
		}
		
		ab++;
		aniTrump.setTextureRect(rectTrump);
		aniTrump.setPosition(970, 5);
		window.draw(aniTrump);
		//----------------------------------------

		//GUI
		//--------------------------------------
		
		trumpSpeech.setPosition(aniTrump.getPosition().x, aniTrump.getPosition().y + 150);

		window.draw(gui1);
		window.draw(gui2);
		window.draw(gui3);
		window.draw(trumpSpeech);
		//--------------------------------------


        //window.draw(shape);
        window.display();
    }

    return 0;
}