#include "Paddle.h"

Paddle::Paddle(int startingX, int startingY, int speed, int frameWidth_, int frameHeight_){
	x_ = startingX;
	y_ = startingY;
	this->speed = speed;
	this->frameWidth_ = frameWidth_;
	this->frameHeight_ = frameHeight_;
	up = false;
	down = false;
	left = false;
	right = false;

	GE161::Sprite* paddleSprite = new GE161::Sprite(frameWidth_, frameHeight_);
	int f = paddleSprite->makeFrame(GE161::Game::basePath() + "paddle.png", 0, 0, frameWidth_, frameHeight_);
	paddleSprite->addFrameToSequence("Default", f);
	attachComponent("Sprite", paddleSprite);

	GE161::BoxCollider* collider = new GE161::BoxCollider(frameWidth_, frameHeight_);
	attachComponent("BoxCollider", collider);



	GE161::Game::theGame->addGameObject(this);
}

void Paddle::update(){
	draw("Default");
	//moveY(6);



}