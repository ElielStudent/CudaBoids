#pragma once
#include "Boid.h"

class NeighborSearchStrategy {
public:
	NeighborSearchStrategy(std::vector<std::weak_ptr<Boid>> allBoids);
	virtual void setAllNeighbors() = 0;
	void addBoid(std::weak_ptr<Boid> boid);
	void setBoids(std::vector < std::weak_ptr<Boid>> newAllBoids);
protected:
	std::vector<std::weak_ptr<Boid>> allBoids_;
};