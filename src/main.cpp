#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boid.h" 

int main()
{
    sf::Clock  deltaClock;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Boid boid = Boid(0, sf::Vector2f(0, 0), 5, 10);
    auto direction = boid.getDirection();
    printf("direction: x=%f y=%f\n", direction.x, direction.y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = deltaClock.restart();
        boid.Update(deltaTime.asSeconds());
        sf::Vector2f position = boid.getPosition();
        printf("x=%f y=%f\n", position.x, position.y);


        window.clear();
        window.draw(shape);
        window.display();
        sf::sleep(sf::seconds(1));
    }
    int a;
    std::cin >> a;
    return 0;
}