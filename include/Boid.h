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
	void updatePosition(float deltaTime);


	int id() const  { return id_; }
	sf::Vector2f position() const { return position_; }
	sf::Vector2f direction() const { return direction_; }
	float sightRadius() const { return sightRadius_; }
	sf::CircleShape sprite() const { return sprite_; }

	void setCloseBoids(const std::vector<Boid&> closeBoids) {
		this->closeBoids_ = std::vector<Boid&>(closeBoids);
	}
private:
	int id_;
	sf::CircleShape sprite_;

	sf::Vector2f direction_; // Normalized vector of direction
	sf::Vector2f position_;
	float sightRadius_; //Radius of area boid can "see" other boids
	sf::FloatRect boundary_;

	std::vector<Boid&> closeBoids_;

	void evadeBoundary();

};