#pragma once
#include "GameAsset.h"
#include <SFML/Graphics.hpp>


class Boid : sf::Transformable {
private:
	int id_;
	sf::CircleShape sprite_;

	float speed_;
	sf::Vector2f direction_; // Normalized vector of direction
	sf::Vector2f position_;
	float sightRadius_; //Radius of area boid can "see" other boids
	sf::FloatRect boundaryRect_;

	std::vector<std::shared_ptr<Boid>> closeBoids;

	void RecalculateDirection();
public:
	Boid(int id, sf::Vector2f position, float sightRadius, float speed, sf::FloatRect boundaryRect_);
	
	void Update(float deltaTime);

	int getId() { return id_; }
	sf::Vector2f getDirection() { return direction_; }
	float getSightRadius() { return sightRadius_; }
	void setCloseBoids(std::vector<std::shared_ptr<Boid>> closeBoids);
};