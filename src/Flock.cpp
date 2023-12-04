#include "Flock.h"

Flock::Flock(std::unique_ptr<NeighborSearchStrategy>&& searchStrategy, float boidSightRadius, sf::FloatRect boundary) :searchStrategy_(std::move(searchStrategy)), boidSightRadius_(boidSightRadius), boundary_(boundary) {}

Flock::~Flock()
{
	this->clearBoids();
}

void Flock::updateBoids(float deltatime)
{

	//Update the direction of all boids
	for (auto it = this->boids_.begin(); it != this->boids_.end(); ++it) {
		std::shared_ptr<Boid> boid = (*it);

		// Get the neighbor of the boid
		std::vector<std::reference_wrapper<Boid>> closeBoids = this->searchStrategy_->getNeighborBoids(boids_,*boid);
		boid->calculateDirection(closeBoids);
	}

	//Update the direction of all boids
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
}

//Adds a boid to a specific position in the game
void Flock::addBoid(sf::Vector2f boid_position)
{
	std::shared_ptr<Boid> boid = std::make_shared<Boid>(boids_.size(), sf::Vector2f(boid_position), this->boidSightRadius_, this->boundary_);
	this->boids_.push_back(boid);
}

//Adds a boid to a random position in the game
void Flock::addBoid()
{
	int xPos = (rand() % (int)(boundary_.width - boundary_.left + boundary_.left));
	int yPos = (rand() % (int)(boundary_.height - boundary_.top + boundary_.top));

	std::shared_ptr<Boid> boid = std::make_shared<Boid>(this->boids_.size(), sf::Vector2f(xPos, yPos), this->boidSightRadius_, this->boundary_);
	this->boids_.push_back(boid);
}

void Flock::clearBoids()
{
	this->boids_.clear();
}
