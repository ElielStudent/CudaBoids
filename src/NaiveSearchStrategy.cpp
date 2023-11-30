#include "NaiveSearchStrategy.h"

void NaiveSearchStrategy::setAllNeighbors() 
{
	for (auto it = this->allBoids_.begin(); it != this->allBoids_.end(); ++it) {
		std::shared_ptr<Boid> boid = it->lock();
		std::vector<std::weak_ptr<Boid>> closeBoids;
		float sightRadius = boid->sightRadius();
		int boidId = boid->id();

		for (auto itForBoid = this->allBoids_.begin(); itForBoid != this->allBoids_.end(); ++itForBoid) {
			std::shared_ptr<Boid> boidToCheck = itForBoid->lock();
			if (boidId != boidToCheck->id() && arePointsInRadiusRange(boid->position(), boidToCheck->position(), sightRadius)) {
				closeBoids.push_back(std::weak_ptr<Boid>(boidToCheck));
			}
		}
		boid->setCloseBoids(closeBoids);
	}
}
