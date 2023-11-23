#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boid.h" 
#include "VectorUtils.h"
#include <chrono>
#include <random>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BORDER_SIZE = 50;


int main()
{
	sf::Clock  deltaClock;
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");

	sf::FloatRect boundary(BORDER_SIZE, BORDER_SIZE, SCREEN_WIDTH - BORDER_SIZE, SCREEN_HEIGHT - BORDER_SIZE);

	std::vector<std::shared_ptr<Boid>> boids;

	for (int i = 0; i < 10; i++) {
		int xPos = (rand() % (int(boundary.width))) + boundary.left;
		int yPos = (rand() % (int(boundary.height))) + boundary.top;

		std::shared_ptr<Boid> newBoid(new Boid(i, sf::Vector2f(xPos, yPos), 40, 250, boundary));
		boids.push_back(newBoid);
	}


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (auto it = begin(boids); it != end(boids); ++it) {
			std::shared_ptr<Boid> boid = (*it);
			std::vector<std::shared_ptr<Boid>> closeBoids;
			float sightRadius = boid->sightRadius();
			int boidId = boid->id();
			for (auto itForBoid = begin(boids); itForBoid != end(boids); ++itForBoid) {
				std::shared_ptr<Boid> boidToCheck = (*it);
				if (boidId != boidToCheck->id() && arePointsInRadiusRange(boid->position(), boidToCheck->position(), sightRadius)) {
					closeBoids.push_back(boidToCheck);
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
		for (auto it = begin(boids); it != end(boids); ++it) {
			std::shared_ptr<Boid> boid = (*it);
			boid->move(deltaTime.asSeconds());
			window.draw(boid->sprite());
		}

		window.display();
	}
	int a;
	std::cin >> a;
	return 0;
}

