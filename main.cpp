#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maps.h"
#include "Character.h"
#include <chrono>
#include <SFML/Audio.hpp>
#include <cmath>

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

	//GAME LOGIC VARIABLES
	//--------------------------------------
	int current_currency = 300;


	//--------------------------------------
	
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

	//TRUMP TEXT
	sf::Text trumpSpeech;
	trumpSpeech.setFont(font);
	trumpSpeech.setString("We need to\nbuild a wall.\n Keep those\ndirty immigrants out\nuntil we're done!");
	trumpSpeech.setCharacterSize(22);
	trumpSpeech.setFillColor(sf::Color::Red);

	//INFORMATION GUI
	sf::Text currencyValueTextLabel;
	currencyValueTextLabel.setFont(font);
	currencyValueTextLabel.setString("Dollars: ");
	currencyValueTextLabel.setCharacterSize(16);
	currencyValueTextLabel.setFillColor(sf::Color::White);

	sf::Text currencyValueText;
	currencyValueText.setFont(font);
	currencyValueText.setString(to_string(current_currency));
	currencyValueText.setCharacterSize(16);
	currencyValueText.setFillColor(sf::Color::White);

	sf::Text mexicansLeftLabel;
	mexicansLeftLabel.setFont(font);
	mexicansLeftLabel.setString("Meheecans left: ");
	mexicansLeftLabel.setCharacterSize(16);
	mexicansLeftLabel.setFillColor(sf::Color::Green);

	sf::Text mexicansLeftCounter;
	mexicansLeftCounter.setFont(font);
	mexicansLeftCounter.setCharacterSize(16);
	mexicansLeftCounter.setFillColor(sf::Color::Green);

	//TRUMP ANIMATION
	sf::Texture trump;
	trump.loadFromFile("Content/spriteSheets/trumpfacesheet.png");
	sf::IntRect rectTrump(0, 0, 128, 128);
	sf::Sprite aniTrump(trump, rectTrump);


	
	//Positions for Portrait & Text
	aniTrump.setPosition(970, 5);
	trumpSpeech.setPosition(aniTrump.getPosition().x + 5, aniTrump.getPosition().y + 150);
	currencyValueTextLabel.setPosition(aniTrump.getPosition().x + 5, aniTrump.getPosition().y + 300);
	currencyValueText.setPosition(currencyValueTextLabel.getPosition().x + 100, aniTrump.getPosition().y + 300);
	mexicansLeftLabel.setPosition(aniTrump.getPosition().x + 5, aniTrump.getPosition().y + 350);
	mexicansLeftCounter.setPosition(mexicansLeftLabel.getPosition().x + 170, aniTrump.getPosition().y + 350);
	
	//AMERICAN FLAG
	sf::Texture flag;
	if (!flag.loadFromFile("Content/spriteSheets/americanflag.png")) {
		cerr << "couldn't load flag" << endl;
	}

	sf::IntRect flagRect(0, 0, 128, 75);

	sf::Sprite aniFlag{ flag, flagRect};
	aniFlag.setPosition(aniTrump.getPosition().x, 7);

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
	

	//cout << test.getX() << " : " << test.getY() << endl;
	//cout << test.getStartX() << " : " << test.getStartY() << endl;

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

	//currentWave[curewave] - gone

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
	music.setLoop(true);
	music.play();


	bool buildPhase{ true };

	auto gameTimer = std::chrono::high_resolution_clock::now();

	int spawnCD{ 800 };

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

				//Adds new tower/soldier
				if (test.getMat().at(mX, mY) == 0 && towerMat.at(mX, mY) == 0 && current_currency >= 100) {
					towerMat.at(mX, mY) = 1;
					Character tmp("Data/soldier.txt");
					tmp.setPosMat(mX, mY);
					soldiers.push_back(tmp);
					current_currency -= 100;
					currencyValueText.setString(to_string(current_currency));
				}

			}
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = endTime - phaseTimer;

			if ((int)elapsed.count() >= 4000) {
				buildPhase = false;
			}

			//----------------------------------------
		}
		else {
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedTime = endTime - spawnTimer;
			mexicansLeftCounter.setString(to_string(currentWave[curWave] - gone));
			auto elapsed = (int)elapsedTime.count();


			//SPAWNING THE MEHICANS
			//----------------------------------------
			if (elapsed > spawnCD && spawned < currentWave[curWave]) {
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

					if (i == test.getStartX() && j == test.getStartY()) {
						tile1.setPosition(i * 32, j * 32);
						window.draw(tile1);
					}
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
				if(mehicans[m].getGone() == false) 
				{
					
						if (soldiers[i].hasInRange(mehicans[m]))
						{
							//soldiers[i].shoot(mehicans[m]);

							//cout << soldiers[i].getAttackCooldown() << endl;

							int dy = mehicans[m].getY() - soldiers[i].getY();
							int dx = mehicans[m].getX() - soldiers[i].getX();

							double v{ 0 };
							double v2{ 0 };

							if (dx != 0) {
								v = atan2(dy, dx) * 180 / 3.14;

							}


							//v = v * 180 / 3.14;

							if (v > -135 && v <= -45) {
								soldiers[i].setAniY(1); //up
														//cout << "looking up" << endl;
							}
							else if (v < -135 || v > 135) {
								soldiers[i].setAniY(5); //left
														//cout << "looking left" << endl;
							}
							else if (v >= 45 && v < 135) {
								soldiers[i].setAniY(3); //down
														//cout << "looking down" << endl;
							}
							else {
								soldiers[i].setAniY(7); //right
														//cout << "looking right" << endl;
							}


							//cout << soldiers[i].getSheetY() << endl;

							if (mehicans[m].getHealth() > 0 && soldiers[i].getAttackCooldown() == false) {
								mehicans[m].setHealth(mehicans[m].getHealth() - soldiers[i].getDamage());
								//cout << mehicans[m].getHealth() << endl;

								if (mehicans[m].getHealth() <= 0) {
									mehicans[m].setGone(true);
									gone += 1;
									current_currency += mehicans[m].getCurrencyValue();
									cout << current_currency << endl;
									mexicansLeftCounter.setString(to_string(currentWave[curWave] - gone));
									currencyValueText.setString(to_string(current_currency));

								}
								soldiers[i].setAttackCooldown(true);
								//cout << soldiers[i].getAttackCooldown() << endl;

							}

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

		
		
		if (gone == currentWave[curWave]) {
			cout << gone << " : " << currentWave[curWave] << " : " << curWave << endl;
			buildPhase = true;
			phaseTimer = std::chrono::high_resolution_clock::now();
			gone = 0;
			curWave++;
			spawned = 0;

			spawnCD -= 20;

			mehicans.clear();

			if (curWave == 10) {
				mapCounter++;
				std::string nextMap{ "map" + mapCounter };
				test = Maps{ nextMap };



				curWave = 0;
				towerMat.fillWith(0);
			}
		}


		//END THE GAME YOU FUCKING ARYAN FAILURE
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
		
		window.draw(aniFlag);
		window.draw(aniTrump);
		
		window.draw(trumpSpeech);
		window.draw(currencyValueTextLabel);
		window.draw(currencyValueText);
		window.draw(mexicansLeftLabel);
		window.draw(mexicansLeftCounter);
		//----------------------------------------

		//GUI
		//--------------------------------------
		
		

		window.draw(gui1);
		window.draw(gui2);
		window.draw(gui3);
		//--------------------------------------


        //window.draw(shape);
        window.display();

		//Game Delay
		while (true) {
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = endTime - gameTimer;
			if ((int)elapsed.count() > 3) {
				gameTimer = std::chrono::high_resolution_clock::now();
				break;
			}
		}

    }

    return 0;
}