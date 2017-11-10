#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maps.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 640), "MTD: GA 3");
    sf::CircleShape shape(100.f);

	sf::RectangleShape tile0(sf::Vector2f(32, 32));
	sf::RectangleShape tile1(sf::Vector2f(32, 32));
	tile0.setFillColor(sf::Color::Blue);
	tile1.setFillColor(sf::Color::Red);

	sf::RectangleShape(sf::Vector2f(32,32));
    shape.setFillColor(sf::Color::Green);
    
	Maps test{ "map1.txt" };
	cout << "Fuck?" << endl;
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


		for (int i{ 0 }; i < test.getX(); ++i) {
			for (int j{ 0 }; j < test.getX(); ++j) {
				if (test.getMat().at(i, j) == 0) {
					tile0.setPosition(i * 32, j * 32);
					window.draw(tile0);
				}
				else if (test.getMat().at(i, j) == 1) {
					tile1.setPosition(i * 32, j * 32);
					window.draw(tile1);
				}
			}
			cout << endl;
		}

        //window.draw(shape);
        window.display();
    }

    return 0;
}