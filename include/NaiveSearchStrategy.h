#pragma once
#include <NeighborSearchStrategy.h>
#include <VectorUtils.h>

class NaiveSearchStrategy :public NeighborSearchStrategy {
public:
	std::vector<std::reference_wrapper<Boid>> getNeighborBoids(std::vector<std::shared_ptr<Boid>>& allBoids, Boid& originBoid) ;
};