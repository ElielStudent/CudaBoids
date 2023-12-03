#pragma once

#include <SFML/Graphics.hpp>

namespace VectorUtils {
	bool arePointsInRadiusRange(sf::Vector2f v1, sf::Vector2f v2, float radius);

	const float  alpha = 0.960433870103f; // (2 * cos(3.14159/8)) / (1 + cos(3.14159/8));;
	const float  beta = 0.397824734759f; // (2 * sin(3.14159/8)) / (1 + cos(3.14159/8));
	float fastMagnitudeAprox(float num1, float num2);
}