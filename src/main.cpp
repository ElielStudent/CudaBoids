#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boid.h" 
#include "VectorUtils.h"
#include <chrono>
#include <random>
#include "Flock.h"
#include "NaiveSearchStrategy.h"
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 900;
const int BORDER_SIZE = 50;
const int BOID_COUNT = 30;
const float SIGHT_RADIUS = 35;

int main()
{
	sf::Clock  deltaClock;
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");

	sf::FloatRect boundary(BORDER_SIZE, BORDER_SIZE, SCREEN_WIDTH - BORDER_SIZE, SCREEN_HEIGHT - BORDER_SIZE);
	std::shared_ptr<Flock > flock = std::make_shared<Flock>(std::make_unique<NaiveSearchStrategy>(), SIGHT_RADIUS, boundary);

	for (int i = 0; i < BOID_COUNT; i++) {
		flock->addBoid();
	}
	
	std::cout.precision(15);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					flock->addBoid(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
				}
			}
			
		}

		window.clear();
		sf::Time deltatime = deltaClock.restart();
		flock->updateBoids(deltatime.asSeconds());

		flock->drawBoids(window);

		/*std::cout << 1/deltaTime.asSeconds() << " fps" << std::endl;*/

		window.display();
	}
	int a;
	std::cin >> a;
	return 0;
}

