#pragma once
#include "LogicEntity.h"
#include "Sprite.h"
#include <SFML/Window.hpp>

class GameAsset
{
protected:
	virtual void UpdateAsset() = 0;
};