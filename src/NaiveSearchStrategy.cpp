#include "NaiveSearchStrategy.h"
std::vector<std::reference_wrapper<Boid>> NaiveSearchStrategy::getNeighborBoids(std::vector<std::shared_ptr<Boid>>& allBoids, Boid& originBoid){
	std::vector<std::reference_wrapper<Boid>> closeBoids;

	float sightRadius = originBoid.sightRadius();
	int boidId = originBoid.id();

	for (auto itForBoid = allBoids.begin(); itForBoid != allBoids.end(); ++itForBoid) {
		std::shared_ptr<Boid> boidToCheck = (*itForBoid);
		if (boidId != boidToCheck->id() && VectorUtils::arePointsInRadiusRange(originBoid.position(), boidToCheck->position(), sightRadius)) {
			closeBoids.push_back(*boidToCheck);
		}
	}
	return closeBoids;
}

