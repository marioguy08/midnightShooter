#include "Enemies.h"

Monster::Monster(sf::Sprite sprite, int x, int y) : Actor(sprite, x, y) {
	this->damage = 5;
	this->health = 100;
	this->direction = sf::Vector2f(0, 0);
}

Monster::Monster() {
	this->damage = 5;
	this->health = 100;
}

void Monster::setDirection(sf::Vector2f playerPosition) {// sets the direction in which the monster should move...this function is called every frame
	float SlopeX = playerPosition.x - this->x;
	float SlopeY = playerPosition.y - this->y;
	sf::Vector2f normal(SlopeX, SlopeY);
	normal = normalizeV(normal);
	this->direction = normal;
}

Monster::Monster(const Monster & monster) {// copy constructor
	this->damage = monster.damage;
	this->direction = monster.direction;
	this->sprite = monster.sprite;
	this->x = monster.x;
	this->y = monster.y;
	this->sprite.setOrigin(225, 225);
	this->health = monster.health;
}