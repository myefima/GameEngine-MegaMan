#pragma once

#include "DrillShot.h"

DrillShot::DrillShot(int startingX, int startingY, int speed, int damage, int frameWidth, int frameHeight){
	x_ = startingX;
	y_ = startingY;
	this->speed = speed;
	this->damage = damage;
	this->frameHeight_ = frameHeight;
	this->frameWidth_ = frameWidth;
	travelDistance = 0;

	GE161::Sprite* busterSprite = new GE161::Sprite(30, 14);
	int f = busterSprite->makeFrame(GE161::Game::basePath() + "enemies1.png", 115, 1003, 30, 14);
	busterSprite->addFrameToSequence("Default", f);
	attachComponent("Sprite", busterSprite);

	GE161::BoxCollider* collider = new GE161::BoxCollider(frameWidth_, frameHeight_);
	attachComponent("BoxCollider", collider);

	GE161::Game::theGame->addGameObject(this);
}

void DrillShot::update(){
	if (speed > 0) draw("Default", true);
	else draw("Default");
	moveX(speed);
	travelDistance += speed;

	if (travelDistance >= 600 || travelDistance <= -600)
		destroy();
}

void DrillShot::onCollisionEnter(GE161::GameObject& otherGameObject){
	if (typeid(otherGameObject) == typeid(Enemy)) return;
	else destroy();
}

void DrillShot::destroy(){
	GE161::Game::theGame->removeGameObject(this);
}
void DrillShot::afterDestroy(){
	this->~DrillShot();
}
DrillShot::~DrillShot(){

}