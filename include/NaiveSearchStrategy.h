#pragma once
#include <NeighborSearchStrategy.h>
#include <VectorUtils.h>

class NaiveSearchStrategy :public NeighborSearchStrategy {
public:
    NaiveSearchStrategy(std::vector<std::weak_ptr<Boid>> allBoids = {})
        : NeighborSearchStrategy(allBoids) {    }
	void setAllNeighbors();
};  