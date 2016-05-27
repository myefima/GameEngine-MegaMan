#pragma once

#include "GameObject.h"
#include "Game.h"

class Paddle : public GE161::GameObject{
public:
	Paddle(int startingX, int startingY, int speed, int frameWidth_, int frameHeight_);

	void update();

	int frameWidth_;
	int frameHeight_;
	int speed;
	bool up, down, left, right;
private:
	~Paddle();

};