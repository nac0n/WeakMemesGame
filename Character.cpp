#include "Character.h"
#include <fstream>
#include <iostream>
#include <string>

Character::Character(std::string conf)
{
	//loadFile = conf;
	std::ifstream confFile;
	confFile.open(conf);

	std::string fileName;

	std::getline(confFile, fileName);

	if (!sheet.loadFromFile(fileName)) {
		std::cerr << "Error loading sprite" << std::endl;
	}

	confFile >> aniStepX;
	confFile >> aniStepY;

	confFile >> canAttack;
	confFile >> canMove;

	confFile >> damage;
	confFile >> health;
	confFile >> range;
	confFile >> firerate;

}

void Character::update(Matrix mat)
{

	if (canMove && !moving) {
		//Find new go
		//std::cout << "Finding new go" << std::endl;
		if (mat.at(goX, goY - 1) == 1 && goY - 1 != startY && goY-1 >= 0) {
				//Up
				startX = goX;
				startY = goY;
				goY -= 1;
				moveX = 0;
				moveY = -1;


		}
		else if (mat.at(goX + 1, goY) == 1 && goX+1 != startX) {
			//Right
			startX = goX;
			startY = goY;
			goX += 1;
			moveX = 1;
			moveY = 0;
			facing = 1;
		}
		else if (mat.at(goX, goY + 1) == 1 && goY+1 != startY) {
			//Down
			startX = goX;
			startY = goY;
			goY += 1;
			moveX = 0;
			moveY = 1;
			
		}
		else if (mat.at(goX - 1, goY) == 1 && goX-1 != startX) {
			//Left
			startX = goX;
			startY = goY;
			goX -= 1;
			moveX = -1;
			moveY = 0;
			facing = 0;
		}

		moving = true;
	}

	if (moving) {
		x += moveX;
		y += moveY;

		if ( ((double)x) / 32 == ((double)goX) && ((double)y) / 32 == ((double)goY)) {
			moving = false;
		}
	}


	if (canAttack) {

	}


	if (counter == speed) {
		if (aniX == aniStepX) {
			aniX = 0;
		}
		else {
			++aniX;
		}
			
		
		counter = -1;
	}

	++counter;

	aniY = facing;

}
bool Character::hasInRange(Character mexican) {
	if(canAttack) 
	{
		if() 
		{

		}
	}
	return true;
}
void Character::shootOnce(Character mexican) {

}



