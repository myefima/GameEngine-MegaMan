#pragma once

#include "GameObject.h"
#include "Game.h"

class MegaMan : public GE161::GameObject{
public:
	MegaMan(int startingX, int startingY, int speed, int frameWidth_, int frameHeight_);

	void update();

	int frameWidth_;
	int frameHeight_;
	int speed;
	bool jumping, up, down, left, right, charging;
private:
	~MegaMan();

};