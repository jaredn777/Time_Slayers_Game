/*
Any functions related to characters should go in here.
*/
#pragma once
#include "character.h"

//----Getters----
//Gets the character's movespeed
float Character::getMoveSpeed(){
	return moveSpeed;
}

//Gets the character's gravity
float Character::getGravity(){
	return gravity;
}



//----Setters----
//Sets the character's move speed
void Character::setMoveSpeed(float ms){
	moveSpeed = ms;
}

//Sets the characters gravity
void Character::setGrav(float gr){
	gravity = gr;
}



//Gets the Player character type
sf::Vector2f Player::GetPos()
{
	sf::Vector2f Position;
	Position.x = this->retX();
	Position.y = this->retY();
	return Position;
}

sf::Sprite Character::GetSprite()
{
	return character;
}

bool Character::GetHealth()
{
	return Health;
}
void Character::SetHealth(bool Healths)
{
	Health = Healths;
}



//----Constructors & Destructors----
Player::Player() : Character("MainCharacter.png") {
	//calls the character contructor then makes the variables unique for player
	isJumping = false;

}

Player::~Player() {

}


Character::Character(std::string fileName) {
	TheActualSkin.loadFromFile(fileName);
	character.setTexture(TheActualSkin);
	character.scale(3, 3);
	setMoveSpeed(.2);
	setGrav(.3);
	Health = true;

}

Character::~Character(){

}


//----Other Functions----
void Player::setJump(bool cool) {
	isJumping = cool;
}

int Character::retY() {
	return character.getPosition().y;
}

int Character::retX() {
	return character.getPosition().x;
}

bool Player::isJump() {
	return isJumping;
}

int Character::maxJump() {
	return character.getPosition().y - 150;
}

