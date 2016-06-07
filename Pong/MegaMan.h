#pragma once

#include "GameObject.h"
#include "Game.h"
#include "BusterShot.h"

class MegaMan : public GE161::GameObject{
public:
	MegaMan(int startingX, int startingY, int speed, int frameWidth_, int frameHeight_);

	void update();
	void destroy();

	int frameWidth_;
	int frameHeight_;
	int speed;
	int chargeTime;
	int health;
	bool jumping, up, down, left, right, charging;
	int velocityY;
	int terminalVelocity;
	BusterShot* b;
private:
	~MegaMan();

};