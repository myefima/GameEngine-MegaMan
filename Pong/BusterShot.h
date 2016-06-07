#pragma once

#include "GameObject.h"
#include "Game.h"

class BusterShot : public GE161::GameObject{
	friend class Enemy;
	friend class MegaMan;
public:
	BusterShot(int startingX, int startingY, int speed, int damage, int frameWidth, int frameHeight);

	void update();

	int frameWidth_;
	int frameHeight_;
	int damage;
	int speed;
	int travelDistance;
	void onCollisionEnter(GE161::GameObject& otherGameObject);
	void destroy();
	void afterDestroy();
private:
	~BusterShot();

};