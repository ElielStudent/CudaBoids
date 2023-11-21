#pragma once
#include <SFML/System/Vector2.hpp>

class LogicEntity
{
protected:
	int id_;
	sf::Vector2<float> position_; // World coordinates.
public:
	LogicEntity(int id, sf::Vector2<float> position) :id_(id), position_(position) {}
	virtual void Update() = 0;
	sf::Vector2<float> getPosition() { return sf::Vector2f(position_); }
	int getId() { return id_; }
};

