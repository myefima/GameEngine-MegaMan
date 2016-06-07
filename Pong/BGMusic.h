#pragma once

#include "GameObject.h"
#include "Game.h"
#include <string>
class BGMusic : public GE161::GameObject{
	GE161::Audio* song;
public:
	BGMusic(std::string filename);
	void update();
	void destroy();
};