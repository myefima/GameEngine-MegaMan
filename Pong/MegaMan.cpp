#include "MegaMan.h"

MegaMan::MegaMan(int startingX, int startingY, int speed, int frameWidth_, int frameHeight_){
	x_ = startingX;
	y_ = startingY;
	this->speed = speed;
	velocityY = 0;
	terminalVelocity = 15;
	this->frameWidth_ = frameWidth_;
	this->frameHeight_ = frameHeight_;
	up = false;
	down = false;
	left = false;
	right = false;
	jumping = false;
	charging = false;
	chargeTime = 0;
	health = 100;
	b = nullptr;
	GE161::Sprite* mmSprite = new GE161::Sprite(frameWidth_, frameHeight_);

	mmSprite->makeFramesFromFile(GE161::Game::basePath() + "mmspritesheet.png", 
		GE161::Game::basePath() + "megaman_frames.txt");
	attachComponent("Sprite", mmSprite);

	GE161::BoxCollider* collider = new GE161::BoxCollider(frameWidth_, frameHeight_);
	attachComponent("BoxCollider", collider);

	GE161::Game::theGame->addGameObject(this);

}

void MegaMan::update(){

	if (right)				draw("Run");
	else if (left)			draw("Run", true);
	else					draw("Idle");

	if (jumping){
		if (velocityY < terminalVelocity)
			velocityY++;
	}
	if (charging) chargeTime++;
	if (!charging && chargeTime > 0){
		int speed = 9;
		if (left) speed *= -1;
		BusterShot* shot = new BusterShot(x_ + 5, y_, speed, 5, 15, 15);
		chargeTime = 0;
		debugOut("shot fired");
	}

}

void MegaMan::destroy(){

}