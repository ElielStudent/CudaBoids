#pragma once
#include <GameAsset.h>
#include <SFML/Graphics.hpp>
#include <VectorUtils.h>

const int BOID_SIZE = 6;
const float SEPARATION_RANGE = 15;
const float TURNFACTOR = 25;
const float SEPARATION_FORCE = 0.2;
const float ALIGNMENT_FORCE = 0.1f;
const float COHESION_FORCE = 0.0005f;
const float MAXSPEED = 420;
const float MINSPEED = 250;

class Boid {
public:
	Boid(int id, sf::Vector2f position, float sightRadius, sf::FloatRect boundaryRect);

	void calculateDirection();
	void move(float deltaTime);


	int id() { return id_; }
	sf::Vector2f position() { return position_; }
	sf::Vector2f direction() { return direction_; }
	float sightRadius() { return sightRadius_; }
	sf::CircleShape sprite() { return sprite_; }

	void setCloseBoids(std::vector<std::weak_ptr<Boid>> closeBoids) {
		this->closeBoids_ = std::vector<std::weak_ptr<Boid>>(closeBoids);
	}
private:
	int id_;
	sf::CircleShape sprite_;

	sf::Vector2f direction_; // Normalized vector of direction
	sf::Vector2f position_;
	float sightRadius_; //Radius of area boid can "see" other boids
	sf::FloatRect boundary_;

	std::vector<std::weak_ptr<Boid>> closeBoids_;

	void evadeBoundary();

};