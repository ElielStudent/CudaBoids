#include "VectorUtils.h"
#include <cmath>

bool VectorUtils::arePointsInRadiusRange(sf::Vector2f v1, sf::Vector2f v2, float radius) {
	float deltaX = (v2.x - v1.x);
	float deltaY = (v2.y - v1.y);
	float distanceSquared = (deltaX * deltaX) + (deltaY * deltaY);
	return radius * radius > distanceSquared;
}



float VectorUtils::fastMagnitudeAprox(float num1, float num2) {
	//Implementation of the alpha max plus beta min algorithm
	double max_value = std::max(num1, num2);
	double min_value = std::min(num1, num2);
	return std::max(max_value, (alpha * max_value + beta * min_value));
}