#include "NeighborSearchStrategy.h"

NeighborSearchStrategy::NeighborSearchStrategy(std::vector<std::weak_ptr<Boid>> allBoids = {})
{
	this->setBoids(allBoids);
}

void NeighborSearchStrategy::addBoid(std::weak_ptr<Boid> boid)
{
	this->allBoids_.push_back(std::weak_ptr(boid));
}

void NeighborSearchStrategy::setBoids(std::vector<std::weak_ptr<Boid>> newAllBoids)
{
	this->allBoids_ = std::vector<std::weak_ptr<Boid>>(newAllBoids);
}
