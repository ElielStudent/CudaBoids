#pragma once
#include <SFML/Graphics.hpp>
#include <Flock.h>
#include <NeighborSearchStrategy.h>
#include <NaiveSearchStrategy.h>

const int BORDER_SIZE = 50;
const float SIGHT_RADIUS = 35;
const int STARTING_BOIDS = 0;

class Game {
public:
	Game(int screen_width,int screen_height);
	void start();
private:
	sf::RenderWindow window_;
	sf::Clock gameClock_;
	std::unique_ptr<Flock> flock_;
	sf::FloatRect gameBoundary_;
	void Update();
	void Draw();
};