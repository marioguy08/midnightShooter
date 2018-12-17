#pragma once
#include "Header.h"
#include "Player.h"

class Bullet : public Actor {
public:
	Bullet();
	Bullet(const Bullet &bullet);
	Bullet(sf::Sprite sprite3,sf::Vector2f start, sf::Vector2f mousePosition);
	void addFrame();
	sf::Vector2f direction;
	sf::Vector2f startPos;
	float angle;
	int framesAlive = 0;

};