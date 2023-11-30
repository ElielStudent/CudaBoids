#pragma once
#include <SFML/Graphics.hpp>
#include <Flock.h>
#include <NeighborSearchStrategy.h>

const int BORDER_SIZE = 50;
const int BOID_COUNT = 30;
const float SIGHT_RADIUS = 35;
const int STARTING_BOIDS = 20;

class Game {
private:
	sf::RenderWindow window_;
	sf::Clock gameClock_;
	std::unique_ptr<Flock> flock_;
	sf::FloatRect gameBoundary_;
	void Update();
	void Draw();
public:
	Game(int screen_width,int screen_height,std::unique_ptr<NeighborSearchStrategy>&& searchStrategy);
	void start();
};