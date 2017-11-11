
#include <string>
#include <SFML/Graphics.hpp>
#include "Matrix.h"
#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

class Character {


public:
	Character(std::string conf);
	~Character() = default;

	void update(Matrix mat);
	void attack();

	int getSheetX() { return aniX; };
	int getSheetY() { return aniY; };

	int getX() { return x; };
	int getY() { return y; };

	int getStartX() { return startX; };
	int getStartY() { return startY; };

	void setPosMat(int x, int y) { startX = goX = x; startY = goY = y; this->x = startX * 32; this->y = startY * 32; };


	sf::Texture& getTex() { return sheet; };

private:
	sf::Texture sheet;

	int x{ 0 }, y{ 0 };
	int startX{ 0 }, startY{ 0 };
	int goX{ 0 }, goY{ 0 };

	const int speed{ 20 };
	int counter{ 0 };

	//Specifies which row/column to take from in Sprite Sheet
	int aniX{ 0 };
	int aniY{ 0 };
	int aniStepX{ 0 };
	int aniStepY{ 0 };
	int facing{ 0 }; //0 = up, 1 = right, 2 = down, 3 = left

	std::string loadFile;

	bool canAttack{ false };
	bool canMove{ false };
	bool moving{ false };
	bool attacking{ false };

	int moveX{ 0 };
	int moveY{ 0 };
};

#endif