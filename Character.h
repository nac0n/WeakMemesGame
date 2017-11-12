
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
	bool hasInRange(Character mexican);
	float calculatedDistance(Character mexican);
	void shoot(Character mexican);
	int getSheetX() { return aniX; };
	int getSheetY() { return aniY; };

	int getX() { return x; };
	int getY() { return y; };

	int getHealth() { return health;};
	void setHealth(int newHealth) { health = newHealth;};

	int getStartX() { return startX; };
	int getStartY() { return startY; };

	void setPosMat(int x, int y) { startX = goX = x; startY = goY = y; this->x = startX * 32; this->y = startY * 32; };

	bool getGone() { return gone; };
	void setGone(bool a) { gone = a; };

	bool getAttackCooldown() { return attackCooldown; };
	bool setAttackCooldown(bool setBool) {attackCooldown = setBool;};

	int getCooldownTimer() { return cooldownTimer;};
	void setCooldownTimer(int newTimerValue) { cooldownTimer = newTimerValue;};

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
	int damage{ 0 };
	int health{ 0 };
	float range{ 0 };
	int firerate{ 0 };
	int facing{ 0 }; //0 = up, 1 = right, 2 = down, 3 = left
	int cooldownTimer {0};

	std::string loadFile;

	bool attackCooldown {false};
	bool canAttack{ false };
	bool canMove{ false };
	bool moving{ false };
	bool attacking{ false };

	int moveX{ 0 };
	int moveY{ 0 };

	bool gone{ false };
};

#endif