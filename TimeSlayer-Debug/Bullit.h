#pragma once
#include "header.h"

class Bullet : public sf::RectangleShape
{

public:

	bool shot;

	Bullet(const sf::Color & color = sf::Color::Black, const sf::Vector2f & size = sf::Vector2f(8,4), sf::Vector2f & position = sf::Vector2f(1000,1000))//default values 
	{
		this->setFillColor(color);
		this->setSize(size);
		this->setPosition(position);
		shot = false;
	}

	~Bullet();
	
};

Bullet::~Bullet()
{

}