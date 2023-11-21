#include "Boid.h"

using namespace  sf;

Boid::Boid(int id, Vector2<float> position, float sightRadius, float speed, sf::FloatRect boundaryRect) :
	id_(id), position_(position), sightRadius_(sightRadius), speed_(speed), boundaryRect_(boundaryRect) {
	float direction_x = static_cast<float>(std::rand()) / RAND_MAX;
	float direction_y = static_cast<float>(std::rand()) / RAND_MAX;
	direction_ = Vector2<float>(direction_x, direction_y);

	sprite_ = sf::CircleShape(10, 3);
}

void Boid::Update(float deltaTime) {
	RecalculateDirection();

	Vector2f velocity = speed_ * direction_;
	position_ += velocity * deltaTime;

	sprite_.setPosition(position_);
}

void Boid::RecalculateDirection() {

}

void Boid::setCloseBoids(std::vector<std::shared_ptr<Boid>> closeBoidLogics)
{
	// Should i remove myself from the list here or before passing the list?
	closeBoidLogics = std::vector<std::shared_ptr<Boid>>(closeBoidLogics);
}