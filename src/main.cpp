#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boid.h" 
#include "VectorUtils.h"
#include <chrono>
#include <random>
#include "Flock.h"
#include "NaiveSearchStrategy.h"

#include "Game.h"

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 900;

int main()
{
	std::cout.precision(15);
	Game game(SCREEN_WIDTH, SCREEN_HEIGHT, std::make_unique<NaiveSearchStrategy>());
	game.start();
}

