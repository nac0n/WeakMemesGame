#include <string>
#include <SFML/Graphics.hpp>
#pragma once
#ifndef CHARACTER_H
#define CHARACHER_H

class Character {

public:
	Character(std::string conf);
	~Character() = default;

private:
	sf::Texture sheet;

	int x{ 0 }, y{ 0 };
	int startX{ 0 }, startY{ 0 };
	int goX{ 0 }, goY{ 0 };

};

#endif