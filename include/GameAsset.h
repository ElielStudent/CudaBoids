#pragma once
#include "LogicEntity.h"
#include "Sprite.h"
#include <SFML/Window.hpp>

class GameAsset
{
public:
	GameAsset(LogicEntity logicEntity, Sprite sprite) :
		logicEntity_(logicEntity), sprite_(sprite) {}
	virtual void UpdateAsset();
	Sprite getSprite();	// Even if its by copy, is the best way to get the sprite every time?
	LogicEntity getLogicEntity(); // What is the correct way to access the logic entity?
private:
	LogicEntity logicEntity_;
	Sprite sprite_;
};

