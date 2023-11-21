#pragma once
#include <iostream>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "LogicEntity.h"

class Boid :LogicEntity {
private:
	float speed_;
	sf::Vector2<float> direction_; // Normalized vector of direction
	float sightRadius_; //Radius of area boid can "see" other boids
	std::vector<std::shared_ptr<Boid>> closeBoids;

	void RecalculateDirection();
	void Move();
public:
	Boid(int id, sf::Vector2<float> position, float sightRadius, float speed);
	void Update() override;

	float getSightRadius() { return sightRadius_; }
	void setCloseBoids(std::vector<std::shared_ptr<Boid>> closeBoids);
};