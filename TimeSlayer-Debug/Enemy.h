#include "header.h"
#include "character.h"


class Enemy :public Character
{
private:


public:
	Enemy();
	~Enemy();

};

Enemy::Enemy() :Character("EnemySprite.png") {

}

Enemy::~Enemy()
{

}