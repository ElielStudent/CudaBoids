#include "Boid.h"

using namespace  sf;

const int BOID_SIZE = 6;
const float SEPARATION_RANGE = 15;
const float TURNFACTOR = 25;
const float SEPARATION_FORCE = 0.2;
const float ALIGNMENT_FORCE = 0.1f;
const float COHESION_FORCE = 0.0005f;
const float MAXSPEED = 420;
const float MINSPEED = 250;


Boid::Boid(int id, Vector2<float> position, float sightRadius, sf::FloatRect boundaryRect) :
	id_(id), position_(position),sightRadius_(sightRadius), boundary_(boundaryRect) {
	float direction_x = static_cast<float>(std::rand()) / RAND_MAX;
	float direction_y = static_cast<float>(std::rand()) / RAND_MAX;
	this->direction_ = Vector2<float>(direction_x, direction_y);

	this->sprite_.setRotation(atan2f(this->direction_.x, -this->direction_.y) * (180 / 3.1415f));
	this->sprite_ = sf::CircleShape(BOID_SIZE, 3);
	this->sprite_.setFillColor(sf::Color(0, 255, 0));
	this->sprite_.setScale(1, 1.5);
	this->sprite_.setOrigin(BOID_SIZE / 2, BOID_SIZE / 2);
}


void Boid::move(float deltaTime) {
	this->evadeBoundary();

	float magnitude = sqrt((this->direction_.x * this->direction_.x) + (this->direction_.y * this->direction_.y));
	if (magnitude > MAXSPEED) {
		this->direction_ = (this->direction_ /magnitude ) * MAXSPEED;
	}
	else if (magnitude < MINSPEED) {
		this->direction_ = (this->direction_ /magnitude) * MINSPEED;
	}

	this->position_ += this->direction_ * deltaTime;

	this->sprite_.setRotation(atan2f(this->direction_.x, -this->direction_.y) * (180 / 3.1415f));
	this->sprite_.setPosition(this->position_);
}


void Boid::evadeBoundary() {
	if (position_.x < boundary_.left) {
		this->direction_.x += TURNFACTOR;
	}
	else if (position_.x > boundary_.width) {
		this->direction_.x -= TURNFACTOR;
	}
	if (position_.y < boundary_.top) {
		this->direction_.y += TURNFACTOR;
	}
	else if (position_.y > boundary_.height) {
		this->direction_.y -= TURNFACTOR;
	}
}

void Boid::calculateDirection() {
	sf::Vector2f alignment(0, 0);	//The average direction of boids around you
	sf::Vector2f cohesion(0, 0);	//The average position of boids around you
	sf::Vector2f separation(0, 0);	//The separation force of boids close to you

	int visibleBoidsCount = closeBoids_.size();

	for (auto it = closeBoids_.begin(); it != closeBoids_.end(); ++it) {
		std::shared_ptr<Boid> otherBoid = (*it).lock();

		sf::Vector2f otherPosition = otherBoid->position();
		alignment += otherBoid->direction();
		cohesion += otherPosition;

		if (arePointsInRadiusRange(this->position_, otherPosition, SEPARATION_RANGE)) {
			separation += this->position_ - otherPosition;
		}
	}

	this->direction_ += separation * SEPARATION_FORCE;

	if (visibleBoidsCount > 0) {
		sf::Vector2f avgAlignment = alignment / (float)visibleBoidsCount;
		this->direction_ += (avgAlignment - this->direction_) * ALIGNMENT_FORCE;

		sf::Vector2f avgCohesion = cohesion / (float)visibleBoidsCount;
		this->direction_ += (avgCohesion - this->position_) * COHESION_FORCE;
	}
}


//Manual turn
//float USERTURN = 0.01f;
//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//	auto direction = boid.getDirection();
//	direction = { cos(USERTURN) * direction.x - sin(USERTURN) * direction.y,
//	cos(USERTURN) * direction.y + sin(USERTURN) * direction.x };
//	boid.setDirection(direction);
//}
//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//	auto direction = boid.getDirection();
//	direction = { cos(-USERTURN) * direction.x - sin(-USERTURN) * direction.y,
//	cos(-USERTURN) * direction.y + sin(-USERTURN) * direction.x };
//	boid.setDirection(direction);
//}