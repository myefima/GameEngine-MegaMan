#pragma once

#include "GameObject.h"
#include "BusterShot.h"
#include "DrillShot.h"
#include "Game.h"

class Enemy : public GE161::GameObject{
	friend class BusterShot;
public:
	Enemy(int startingX, int startingY, int speed, int frameWidth_, int frameHeight_);

	void update();

	int frameWidth_;
	int frameHeight_;
	int speed;
	int shootTime;
	int timeToNextShot;
	int maxPatrolDistance;
	int currentPatrolPos;
	bool left, right;
	int health;
	
	void destroy();
	void afterDestroy();
	void onCollisionEnter(GameObject& gameObject);
private:
	~Enemy();

};