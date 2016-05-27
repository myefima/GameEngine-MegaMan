// Pong.h

#pragma once

#include "Game.h"

class MegaManGame: public GE161::Game
{
public:

	// All game classes must override these two Game methods.
	void setup();
	std::string chooseScene(std::string prevScene, int prevReturnCode);

};