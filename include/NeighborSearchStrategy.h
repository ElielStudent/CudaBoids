#pragma once
#include <Boid.h>

class NeighborSearchStrategy {
public:
	virtual std::vector<std::reference_wrapper<Boid>> getNeighborBoids(std::vector<std::shared_ptr<Boid>>& allBoids,Boid& originBoid)=0;
};