#include "Boid.h"
#include "VectorUtils.h"

using namespace  sf;

const int BOID_SIZE = 10;
const float SEPARATION_RANGE = 8;
const float TURNFACTOR = 0.1;
const float SEPARATION_FORCE = 0.05f;
const float ALIGNMENT_FORCE = 0.05f;
const float COHESION_FORCE = 0.0005f;
const float MAXSPEED = 0.1f;
const float MINSPEED = 0.1f;

Boid::Boid(int id, Vector2<float> position, float sightRadius, float speed, sf::FloatRect boundaryRect) :
	id_(id), position_(position), sightRadius_(sightRadius), speed_(speed), boundaryRect_(boundaryRect) {
	float direction_x = static_cast<float>(std::rand()) / RAND_MAX;
	float direction_y = static_cast<float>(std::rand()) / RAND_MAX;
	this->direction_ = Vector2<float>(direction_x, direction_y);
	this->nextDirection_ = this->direction_;

	this->sprite_.setRotation(atan2f(this->direction_.x, -this->direction_.y) * (180 / 3.1415f));
	this->sprite_ = sf::CircleShape(BOID_SIZE, 3);
	this->sprite_.setFillColor(sf::Color(0, 255, 0));
	this->sprite_.setScale(1, 1.5);
	this->sprite_.setOrigin(BOID_SIZE / 2, BOID_SIZE / 2);
}


void Boid::move(float deltaTime) {
	this->direction_ = this->nextDirection_;

	Vector2f velocity = this->speed_ * this->direction_;

	float currentSpeed = fastMagnitudeAprox(velocity.x, velocity.y);

	if (currentSpeed) {

	}

	this->position_ += velocity * deltaTime;

	this->sprite_.setRotation(atan2f(this->direction_.x, -this->direction_.y) * (180 / 3.1415f));
	this->sprite_.setPosition(this->position_);
}


void Boid::evadeBoundary() {
	if (position_.x < boundaryRect_.left) {
		this->nextDirection_.x += TURNFACTOR;
	}
	else if (position_.x > boundaryRect_.width) {
		this->nextDirection_.x -= TURNFACTOR;
	}
	if (position_.y < boundaryRect_.top) {
		this->nextDirection_.y += TURNFACTOR;
	}
	else if (position_.y > boundaryRect_.height) {
		this->nextDirection_.y -= TURNFACTOR;
	}
}

void Boid::calculateDirection() {
	this->evadeBoundary();

	sf::Vector2f alignment(0, 0);	//The average direction of boids around you
	sf::Vector2f cohesion(0, 0);	//The average position of boids around you
	sf::Vector2f separation(0, 0);	//The separation force of boids close to you

	int visibleBoidsCount = closeBoids_.size();
	int separationBoidsCount = 0;

	for (auto it = begin(closeBoids_); it != end(closeBoids_); ++it) {
		std::shared_ptr<Boid> otherBoid = *it;

		sf::Vector2f otherPosition = otherBoid->position();
		alignment += otherBoid->direction();
		cohesion += otherPosition;
		if (arePointsInRadiusRange(this->position_, otherPosition, SEPARATION_RANGE)) {
			separation += this->position_ - otherPosition;
			separationBoidsCount++;
		}
	}

	this->nextDirection_ += separation * SEPARATION_FORCE;

	if (visibleBoidsCount > 0) {
		sf::Vector2f avgAlignment = alignment / (float)visibleBoidsCount;
		this->nextDirection_ += (avgAlignment - this->direction_) * ALIGNMENT_FORCE;

		sf::Vector2f avgCohesion = cohesion / (float)visibleBoidsCount;
		this->nextDirection_ += (avgCohesion - this->position_) * COHESION_FORCE;
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