/*
Pretty messily written Character/Player classes. 
Forgot the intricacies of OOP, if someone could make it 
more elegant that would be fantastic
*/

#pragma once

#include "header.h"

//Default 'Character' abstract. Did I need to type abstract before it? Idunno
class Character 
{
public:
	Character(std::string fileName);
	~Character();

	void drawTo(sf::RenderWindow &window) {
		window.draw(character);
	}

	void move(sf::Vector2f distance) {
		character.move(distance);
	}

	void setPos(sf::Vector2f newPos) {
		character.setPosition(newPos);
	}

	void setSprite(std::string fileName) {
		TheActualSkin.loadFromFile(fileName);
		character.setTexture(TheActualSkin);
	}

	float getMoveSpeed();
	float getGravity();

	bool GetHealth();
	void SetHealth(bool Healths);
	void setMoveSpeed(float ms);
	void setGrav(float gr);

	int retY();
	int retX();

	int maxJump();

	sf::Sprite GetSprite();

protected:
	float moveSpeed;
	float gravity;
	sf::Texture TheActualSkin;
	sf::Sprite character;
	bool Health;
	
};

//Main Player class; Inherits Character traits
class Player : public Character
{
public:
	Player();
	~Player();

	sf::Vector2f GetPos();

	void setJump(bool cool);
	bool isJump();
	
private:
	bool isJumping;
};