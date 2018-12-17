#pragma once
#include "Header.h"
#include "Actor.h"
class Player : public Actor{
public:
	int health;
	int damage;
	Player(sf::Sprite sprite, float x, float y);
};