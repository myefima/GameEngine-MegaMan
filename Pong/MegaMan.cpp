#include "MegaMan.h"

MegaMan::MegaMan(int startingX, int startingY, int speed, int frameWidth_, int frameHeight_){
	x_ = startingX;
	y_ = startingY;
	this->speed = speed;
	this->frameWidth_ = frameWidth_;
	this->frameHeight_ = frameHeight_;
	up = false;
	down = false;
	left = false;
	right = false;
	jumping = false;
	charging = false;

	GE161::Sprite* mmSprite = new GE161::Sprite(frameWidth_, frameHeight_);

	mmSprite->makeFramesFromFile(GE161::Game::basePath() + "mmspritesheet.png", 
		GE161::Game::basePath() + "megaman_frames.txt");
	attachComponent("Sprite", mmSprite);

	GE161::BoxCollider* collider = new GE161::BoxCollider(frameWidth_, frameHeight_);
	attachComponent("BoxCollider", collider);



	GE161::Game::theGame->addGameObject(this);
}

void MegaMan::update(){
	if (right || left)		draw("Run");
	else					draw("Idle");

}