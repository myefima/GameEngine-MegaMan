#pragma once

#include "Enemy.h"

Enemy::Enemy(int startingX, int startingY, int speed, int frameWidth_, int frameHeight_){
	x_ = startingX;
	y_ = startingY;
	this->speed = speed;
	this->frameWidth_ = frameWidth_;
	this->frameHeight_ = frameHeight_;
	shootTime = 120;
	timeToNextShot = 0;
	health = 30;
	maxPatrolDistance = 50;
	currentPatrolPos = 0;
	left = true;
	right = false;
	
	GE161::Sprite* busterSprite = new GE161::Sprite(frameWidth_, frameHeight_);
	int f = busterSprite->makeFrame(GE161::Game::basePath() + "enemies1.png", 0, 1000, 54, 36);
	busterSprite->addFrameToSequence("Default", f);
	attachComponent("Sprite", busterSprite);

	GE161::BoxCollider* collider = new GE161::BoxCollider(frameWidth_, frameHeight_);
	attachComponent("BoxCollider", collider);

	GE161::Game::theGame->addGameObject(this);
}

void Enemy::update(){
	if (left) draw("Default");
	if (right) draw("Default", true);

	if (left) {
		moveX(-2);
		currentPatrolPos -= 2;
	}
	if (right) {
		moveX(2);
		currentPatrolPos += 2;
	}

	if (currentPatrolPos <= maxPatrolDistance * -1){
		left = false;
		right = true;
	}
	if (currentPatrolPos >= maxPatrolDistance) {
		left = true;
		right = false;
	}

	timeToNextShot++;

	if (timeToNextShot > shootTime){
		int speed = 6;
		if (left) speed *= -1;
		DrillShot* d = new DrillShot(x_, y_, speed, 5, 8, 8);
		timeToNextShot = 0;
	}

	if (health <= 0)
		destroy();
}

void Enemy::onCollisionEnter(GameObject& gameObject){
	if (typeid(gameObject) == typeid(BusterShot)){
		BusterShot* b = (BusterShot*)&gameObject;
		health -= b->damage;
		b->destroy();
	}
}

void Enemy::destroy(){
	GE161::Game::theGame->removeGameObject(this);
}

void Enemy::afterDestroy(){
	this->~Enemy();
}

Enemy::~Enemy(){

}