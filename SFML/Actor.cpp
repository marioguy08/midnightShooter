#include "Actor.h"

Actor::Actor() {
	this->x = 0;
	this->y = 0;
}

Actor::Actor(sf::Sprite sprite1, float xPos, float yPos) {
	this->x = xPos;
	this->y = yPos;
	this->sprite = sprite1;
	this->sprite.setPosition(this->x, this->y);
}
void Actor::move(float x, float y) {// updates the position of actor
	this->sprite.move(x, y);
	this->x += x;
	this->y += y;
}
void Actor::draw(sf::RenderWindow & window) {// draws whichever sprite actor currently contains to the render window passed
	window.draw(this->sprite);
}
void Actor::rotate(float degrees) {// rotates actor
	this->sprite.rotate(degrees);
}
void Actor::setRotate(float degrees) {// rotates actor
	this->sprite.setRotation(degrees);
}