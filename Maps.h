#include "Matrix.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#pragma once
#ifndef MAPS_H
#define MAPS_H

class Maps {
public:
	Maps(std::string a);
	~Maps() = default;

	int getX() { return x; }
	int getY() { return y; }

	int getStartX() { return startX; };
	int getStartY() { return startY; };

	int getEndX() { return endX; };
	int getEndY() { return endY; };

	Matrix getMat() { return mat; }

	void draw(sf::RenderWindow* window);

private:
	Matrix mat;

	int x{ 0 };
	int y{ 0 };

	int startX{ 0 };
	int startY{ 0 };

	int endX{ 0 };
	int endY{ 0 };

};

#endif
