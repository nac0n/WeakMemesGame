#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maps.h"
#include "Character.h"
#include <chrono>
#include <SFML/Audio.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "MTD: GA 3");
    sf::CircleShape shape(100.f);

	//sf::RectangleShape tile0(sf::Vector2f(32, 32));
	//sf::RectangleShape tile1(sf::Vector2f(32, 32));
	//tile0.setFillColor(sf::Color::Green);
	//tile1.setFillColor(sf::Color::Yellow);

	sf::Texture tex1;
	if (!tex1.loadFromFile("Content/spriteSheets/grass.png")) {

	}

	sf::Texture tex2;
	if (!tex2.loadFromFile("Content/spriteSheets/ground.png")) {

	}

	sf::Texture tex3;
	if (!tex3.loadFromFile("Content/spriteSheets/staket.png")) {

	}

	sf::Sprite tile0(tex1);
	sf::Sprite tile1(tex2);
	sf::Sprite tile2(tex3);

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

	//--------------------------------------
	//TRUMP SPEECH
	//--------------------------------------

	sf::Text trumpSpeech;
	trumpSpeech.setFont(font);
	trumpSpeech.setString("We need to\nbuild a wall.\n Don't let those\ndirty immigrants get\ninside our country!");

	trumpSpeech.setCharacterSize(24);
	trumpSpeech.setFillColor(sf::Color::Red);
	

	//--------------------------------------
	//TOWER HANDLING STUFF
	//--------------------------------------
	Matrix towerMat{ 30,20 }; //Matrix that keeps a check on all the soldiers for building
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
	int mapCounter{ 1 };
	

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

	//Timer for phases
	auto phaseTimer = std::chrono::high_resolution_clock::now();

	//Counter for waves
	
	int escaped{ 0 };
	const int tooMany{ 50 };
	int gone{ 0 };
	int spawned{ 0 };
	int currentWave[10];
	int curWave{ 0 };

	
	ifstream wave;
	wave.open("waves1.txt");
	if (!wave) {
		perror("Fuck: ");
	}
	for (int i{ 0 }; i < 10; ++i)
		wave >> currentWave[i];

	wave.close();
	

	sf::Music music;
	if (!music.openFromFile("Content/Sound/music_mexican.ogg")) {

	}
	music.play();


	bool buildPhase{ true };

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
		if (buildPhase) {
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
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = endTime - phaseTimer;

			if ((int)elapsed.count() >= 2000) {
				buildPhase = false;
			}

			//----------------------------------------
		}
		else {
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedTime = endTime - spawnTimer;

			auto elapsed = (int)elapsedTime.count();


			//SPAWNING THE MEHICANS
			//----------------------------------------
			if (elapsed % 200 == 0 && spawned < currentWave[curWave]) {
				Character tmp("Data/mexican.txt");
				tmp.setPosMat(test.getStartX(), test.getStartY());
				mehicans.push_back(tmp);
				spawnTimer = std::chrono::high_resolution_clock::now();
				spawned++;
			}
			//----------------------------------------
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
				else if (test.getMat().at(i, j) == 2) {
					tile0.setPosition(i * 32, j * 32);
					window.draw(tile0);
					tile2.setPosition(i * 32, j * 32);
					window.draw(tile2);
				}
			}
		}
		//----------------------------------------



		//CHARACTERS
		//----------------------------------------

		for (int i{ 0 }; i < soldiers.size(); ++i) {
			soldiers[i].update(test.getMat());
			

			aniChar.setTexture(soldiers[i].getTex());
			aniRect.left = soldiers[i].getSheetX() * 32;
			aniRect.top = soldiers[i].getSheetY() * 32;
			aniChar.setTextureRect(aniRect);
			aniChar.setPosition(soldiers[i].getX(), soldiers[i].getY());
			window.draw(aniChar);
			
			for(int m{0}; m < mehicans.size(); ++m) 
			{
				if(!mehicans[i].getGone()) 
				{
					if(soldiers[i].hasInRange(mehicans[i])) 
					{
						soldiers[i].shootOnce(mehicans[i]);
						break;
						//break is needed to not shoot more than one mexican
					}	
				}
			}
			
		}

		for (int i{ 0 }; i < mehicans.size(); ++i) {
			mehicans[i].update(test.getMat());

			//MEHICAN GOT THROUGH, WHAT ARE YOU EVEN DOING?!
			int sX = mehicans[i].getStartX();
			int sY = mehicans[i].getStartY();

			if ((sX == test.getEndX()) && (sY == test.getEndY()) && mehicans[i].getGone() == false) {
				mehicans[i].setGone(true);
				cout << i << endl;
				escaped++;
				gone++;
			}

			//cout << mehicans[i].getStartX() << " : " << mehicans[i].getStartY() << endl;

			aniChar.setTexture(mehicans[i].getTex());
			aniRect.left = mehicans[i].getSheetX() * 32;
			aniRect.top = mehicans[i].getSheetY() * 32;
			aniChar.setTextureRect(aniRect);
			aniChar.setPosition(mehicans[i].getX(), mehicans[i].getY());
			
			if(mehicans[i].getGone() == false)
				window.draw(aniChar);



			
		}

		//END THE GAME YOU FUCKING ARYAN FAILURE
		
		if (gone == currentWave[curWave]) {
			cout << gone << " : " << currentWave[curWave] << " : " << curWave << endl;
			buildPhase = true;
			phaseTimer = std::chrono::high_resolution_clock::now();
			gone = 0;
			curWave++;
			spawned = 0;
			mehicans.clear();

			if (curWave == 10) {
				mapCounter++;
				std::string nextMap{ "map" + mapCounter };
				test = Maps{ nextMap };



				curWave = 0;
				towerMat.fillWith(0);
			}
		}

		if (escaped >= tooMany) {


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