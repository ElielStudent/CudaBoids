#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boid.h" 
#include "VectorUtils.h"
#include <chrono>
#include <random>

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 900;
const int BORDER_SIZE = 50;
const int BOID_COUNT = 30;

int main()
{
	sf::Clock  deltaClock;
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");

	sf::FloatRect boundary(BORDER_SIZE, BORDER_SIZE, SCREEN_WIDTH - BORDER_SIZE, SCREEN_HEIGHT - BORDER_SIZE);

	std::vector<std::shared_ptr<Boid>> boids;

	for (int i = 0; i < BOID_COUNT; i++) {
		int xPos = (rand() % (int(boundary.width- boundary.left))) + boundary.left;
		int yPos = (rand() % (int(boundary.height- boundary.top))) + boundary.top;

		std::shared_ptr<Boid> newBoid(new Boid(i, sf::Vector2f(xPos, yPos), 35,  boundary));
		boids.push_back(newBoid);
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
					std::shared_ptr<Boid> newBoid(new Boid(boids.size(), sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 35,  boundary));
					boids.push_back(newBoid);
				}
			}
			
		}

		for (auto it = begin(boids); it != end(boids); ++it) {
			std::shared_ptr<Boid> boid = (*it);
			std::vector<std::weak_ptr<Boid>> closeBoids;
			float sightRadius = boid->sightRadius();
			int boidId = boid->id();

			for (auto itForBoid = begin(boids); itForBoid != end(boids); ++itForBoid) {
				std::shared_ptr<Boid> boidToCheck = (*itForBoid);
				if (boidId != boidToCheck->id() && arePointsInRadiusRange(boid->position(), boidToCheck->position(), sightRadius)) {
					closeBoids.push_back(std::weak_ptr(boidToCheck));
				}
			}
			boid->setCloseBoids(closeBoids);
		}

		for (auto it = begin(boids); it != end(boids); ++it) {
			std::shared_ptr<Boid> boid = (*it);
			boid->calculateDirection();
		}

		window.clear();

		sf::Time deltaTime = deltaClock.restart();
		/*std::cout << 1/deltaTime.asSeconds() << " fps" << std::endl;*/
		for (auto it = begin(boids); it != end(boids); ++it) {
			std::shared_ptr<Boid> boid = (*it);
			boid->move(deltaTime.asSeconds());
			window.draw(boid->sprite());

			sf::CircleShape range(boid->sightRadius());
			range.setPosition({ boid->position().x - boid->sightRadius()  ,
				boid->position().y - boid->sightRadius()});
			range.setFillColor(sf::Color::Transparent);
			range.setOutlineColor(sf::Color(255,255,255,128));
			range.setOutlineThickness(-1);

			window.draw(range);
		}

		window.display();
	}
	int a;
	std::cin >> a;
	return 0;
}

