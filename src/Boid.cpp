#include "Boid.h"

Boid::Boid(int id, sf::Vector2<float> position, float sightRadius, float speed) : LogicEntity(id, position) {
	sightRadius_ = sightRadius;
	speed_ = speed;

}

void Boid::Update() {
	RecalculateDirection();
	Move();
}

void Boid::RecalculateDirection() {

}


void Boid::Move() {
	position_ += speed_ * direction_;
}


void Boid::setCloseBoids(std::vector<std::shared_ptr<Boid>> closeBoids)
{
	// Should i remove myself from the list here or before passing the list?
	closeBoids = std::vector<std::shared_ptr<Boid>>(closeBoids);
}