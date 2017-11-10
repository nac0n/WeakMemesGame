#include "Maps.h"
#include <iostream>


using namespace std;

Maps::Maps(std::string a)
{
	ifstream mapFile;
	mapFile.open(a);
	if (!mapFile) {
		perror("Fuck: ");
	}
	cout << a << endl;
	


	mapFile >> x;
	mapFile >> y;
	
	mapFile >> startX;
	mapFile >> startY;

	mapFile >> endX;
	mapFile >> endY;


	Matrix tmp(x, y);

	mat = tmp;

	//mat = Matrix(x, y);
	mat.fillWith(0);

	

	int num{ 0 };
	for (int i{ 0 }; i < y; ++i) {
		for (int j{ 0 }; j < x; ++j) {
			mapFile >> num;

			mat.at(j, i) = num;
		}
	}

	for (int i{ 0 }; i < x; ++i) {
		for (int j{ 0 }; j < y; ++j) {
			cout << mat.at(i, j) << " ";
		}
		cout << endl;
	}

	mapFile.close();
}

void Maps::draw(sf::RenderWindow *window)
{
	sf::RectangleShape tile0(sf::Vector2f(32, 32));
	sf::RectangleShape tile1(sf::Vector2f(32, 32));

	

	window->setActive(true);

	for (int i{ 0 }; i < x; ++i) {
		for (int j{ 0 }; j < y; ++j) {
			if (mat.at(i, j) == 0) {
				tile0.setPosition(i * 32, j * 32);
				cout << 0;
				window->draw(tile0);
			}
			else if (mat.at(i, j) == 1) {
				tile1.setPosition(i * 32, j * 32);
				cout << 1;
				window->draw(tile1);
			}
		}
		cout << endl;
	}

	window->setActive(false);

}
