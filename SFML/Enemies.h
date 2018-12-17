#pragma once
#include "Header.h"
#include "Player.h"
class Monster : public Actor {
public:
	int damage;
	int health;
	sf::Vector2f direction;
	Monster(sf::Sprite sprite,int x, int y);
	Monster(const Monster &monster);
	Monster();
	void setDirection(sf::Vector2f playerPosition);
};