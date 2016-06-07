
#include <string>
#include "MegaManGame.h"
#include "MegaManGamePlayScene.h"

// Pong.cpp

//An object of the class derived from GE161::Game must be created.
MegaManGame* theGame = new MegaManGame();

// setup() is called once, before the window is created or displayed.
void MegaManGame::setup()
{
	window()->size(500, 250);
	window()->title("MegaMan");
	camera()->setX(0);
	camera()->setY(0);
	theGame->setFrameRate(30);

	//addScene("Instructions", new PongInstructionsScene(this));
	addScene("GamePlay", new MegaManGamePlayScene(this));
}

std::string MegaManGame::chooseScene(std::string prevScene, int prevReturnCode)
{

	if (prevScene == START_GAME)
	{
		return "GamePlay";
	}

	// prevScene must == "GamePlay"
	return EXIT_GAME;
}


