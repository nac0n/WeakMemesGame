#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 480), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
    while (window.isOpen())
    {

    // check how many buttons joystick number 0 has
    unsigned int buttonCount = sf::Joystick::getButtonCount(0);

    // check if joystick number 0 has a Z axis
    bool hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);
    std::cout << buttonCount << endl;

    std::cout << hasZ << endl;
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}