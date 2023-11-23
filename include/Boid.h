#pragma once
#include "GameAsset.h"
#include <SFML/Graphics.hpp>


class Boid {
private:
	int id_;
	sf::CircleShape sprite_;

	float speed_;
	sf::Vector2f direction_; // Normalized vector of direction
	sf::Vector2f nextDirection_; //Direction saved for after all other boids have set their direction
	sf::Vector2f position_;
	float sightRadius_; //Radius of area boid can "see" other boids
	sf::FloatRect boundaryRect_;

	std::vector<std::shared_ptr<Boid>> closeBoids_;

	void evadeBoundary();
public:
	Boid(int id, sf::Vector2f position, float sightRadius, float speed, sf::FloatRect boundaryRect_);
	
	void calculateDirection();
	void move(float deltaTime);


	int id() { return id_; }
	sf::Vector2f position() { return position_; }
	sf::Vector2f direction() { return direction_; }
	float sightRadius() { return sightRadius_; }
	sf::CircleShape sprite() { return sprite_; }

	void setCloseBoids(std::vector<std::shared_ptr<Boid>> closeBoids) {
		this->closeBoids_ = std::vector<std::shared_ptr<Boid>>(closeBoids);
	}
};