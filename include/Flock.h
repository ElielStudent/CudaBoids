#pragma once
#include <iostream>
#include <Boid.h>
#include <vector>
#include <NeighborSearchStrategy.h>

class Flock {
public:
	Flock(std::unique_ptr<NeighborSearchStrategy>&& searchStrategy, float boidSightRadius, sf::FloatRect boundary);
	~Flock();
	void updateBoids(float deltatime);
	void drawBoids(sf::RenderWindow& window);
	void addBoid(std::shared_ptr<Boid> boid);
	void addBoid(sf::Vector2f boid_position);
	void addBoid();
	void clearBoids();

	int getBoidCount() const { return boids_.size(); }
private:
	std::vector<std::shared_ptr<Boid>> boids_;
	std::unique_ptr<NeighborSearchStrategy> searchStrategy_;
	float boidSightRadius_;
	sf::FloatRect boundary_;
};