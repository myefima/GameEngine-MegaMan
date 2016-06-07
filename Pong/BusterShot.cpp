#pragma once

#include "BusterShot.h"

BusterShot::BusterShot(int startingX, int startingY, int speed, int damage, int frameWidth, int frameHeight){
	x_ = startingX;
	y_ = startingY;
	this->speed = speed;
	this->damage = damage;
	this->frameHeight_ = frameHeight;
	this->frameWidth_ = frameWidth;
	travelDistance = 0;
	
	GE161::Sprite* busterSprite = new GE161::Sprite(frameWidth_, frameHeight_);
	int f = busterSprite->makeFrame(GE161::Game::basePath() + "mmspritesheet.png", 457, 316, 8, 8);
	busterSprite->addFrameToSequence("Default", f);
	attachComponent("Sprite", busterSprite);

	GE161::BoxCollider* collider = new GE161::BoxCollider(frameWidth_, frameHeight_);
	attachComponent("BoxCollider", collider);

	GE161::Game::theGame->addGameObject(this);
}

void BusterShot::update(){
	draw("Default");
	moveX(speed);
	travelDistance += speed;

	if (travelDistance >= 600  || travelDistance <= -600)
		destroy();
}

void BusterShot::onCollisionEnter(GE161::GameObject& otherGameObject){
	if (typeid(otherGameObject) == typeid(MegaMan)) return;
	else destroy();
}

void BusterShot::destroy(){
	debugOut("buster destroy");
	GE161::Game::theGame->removeGameObject(this);
}
void BusterShot::afterDestroy(){
	debugOut("buster afterdestroy");

	this->~BusterShot();
}
BusterShot::~BusterShot(){
	debugOut("buster destructor");

}