//PongGamePlayScene.h

#pragma once

#include "MegaManGame.h"
#include "Scene.h"
#include "GameObject.h"
#include "MegaMan.h"
#include "BGMusic.h"
#include "Event.h"
#include "SDL_mixer.h"
#include "Audio.h"
#include "Camera.h"
#include "TileMap.h"

class MegaManGamePlayScene : public GE161::Scene
{
public:
	MegaManGamePlayScene(MegaManGame* theGame);
	~MegaManGamePlayScene();

	bool setup();
	int draw();

	void onEvent(GE161::Event& event);
	GE161::TileMap* tm;
	GE161::TileMap* renderTop;
private:
	MegaManGame* theGame;
	MegaMan* megaMan;
	BGMusic* music;

	int frameWidth_;
	int frameHeight_;

	int level_width;
	int level_height;
	int x_delta, y_delta;

	bool exitRequested;
};

