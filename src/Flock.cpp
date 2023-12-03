#include "Flock.h"

void Flock::updateBoids(float deltatime)
{
	// Update the neighbors of all boids
	this->searchStrategy_->setAllNeighbors();

	//Updatae the direction of all boids
	for (auto it = this->boids_.begin(); it != this->boids_.end(); ++it) {
		std::shared_ptr<Boid> boid = (*it);
		boid->calculateDirection();
	}

	//Updatae the direction of all boids
	for (auto it = this->boids_.begin(); it != this->boids_.end(); ++it) {
		std::shared_ptr<Boid> boid = (*it);
		boid->updatePosition(deltatime);
	}
}

void Flock::drawBoids(sf::RenderWindow& window)
{
	for (auto it = this->boids_.begin(); it != this->boids_.end(); ++it) {
		std::shared_ptr<Boid> boid = (*it);
		window.draw(boid->sprite());

		sf::CircleShape range(boid->sightRadius());
		range.setPosition({ boid->position().x - boid->sightRadius()  ,
			boid->position().y - boid->sightRadius() });
		range.setFillColor(sf::Color::Transparent);
		range.setOutlineColor(sf::Color(255, 255, 255, 128));
		range.setOutlineThickness(-1);

		window.draw(range);
	}
}

//Adds a boid to the game
void Flock::addBoid(std::shared_ptr<Boid> boid)
{
	this->boids_.push_back(boid);
	this->searchStrategy_->addBoid(boid);
}

//Adds a boid to a specific position in the game
void Flock::addBoid(sf::Vector2f boid_position)
{
	std::shared_ptr<Boid> boid = std::make_shared<Boid>(boids_.size(), sf::Vector2f(boid_position), this->boidSightRadius_, this->boundary_);
	this->boids_.push_back(boid);
	this->searchStrategy_->addBoid(boid);
}

//Adds a boid to a random position in the game
void Flock::addBoid()
{
	int xPos = (rand() % (int(boundary_.width - boundary_.left))) + boundary_.left;
	int yPos = (rand() % (int(boundary_.height - boundary_.top))) + boundary_.top;

	std::shared_ptr<Boid> boid = std::make_shared<Boid>(this->boids_.size(), sf::Vector2f(xPos, yPos), this->boidSightRadius_, this->boundary_);
	this->boids_.push_back(boid);
	this->searchStrategy_->addBoid(boid);

}
