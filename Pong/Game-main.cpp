#pragma once

#include "Game.h"
#include "GameObject.h"
#include "SDL_mixer.h"
#include <vector>

void GE161::Game::main(int x)
{
	if (x != 8675309)
	{
		fatalSDLError("Do not invoke GE161::Game::main()");
		return;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fatalSDLError("SDL_Init(SDL_INIT_EVERYTHING) Error in main(): ", SDL_GetError());
		return;
	}

	if (SDL_NumJoysticks() < 1)
		debugOut("No joysticks connected.");
	else {
		setController();
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(16000, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return;
	}
	


	// Invoke the game's overridden setup() method, and create the SDL window.
	window_ = new GE161::Window();
	theGame->camera_ = new GE161::Camera(0, 0, window_->clientWidth(), window_->clientHeight());
	setup();
	window_->initialize();
	window_->clearBackground();

	eventQueue_ = new GE161::EventQueue();

	std::string sceneName = GE161::Game::START_GAME;
	int returnCode = CONTINUE_SCENE;

	// Loop through the outer while loop once per scene.
	// A negative return code from a scene says "Stop the program!"
	while (returnCode >= 0)
	{
		// Ask the game which scene to do next.
		sceneName = GE161::Game::theGame->chooseScene(sceneName, returnCode);
		GE161::Scene* scene = GE161::Game::theGame->lookUpScene(sceneName);
		
		//GE161::Game::addPending();

		// Now we have the scene to use.  First, run its setup().
		bool success = scene->setup();
		if (!success)
		{
			fatalSDLError("error in main(), setup failed for scene", sceneName);
			return;
		}

		int MS_PER_FRAME = 1000 / theGame->framerate();
		std::vector<int> fps;
		int frameCounter = 0;
		int timeDelta = 0;


		// setup() succeeded.  Run its draw() until a non-zero return code.
		returnCode = CONTINUE_SCENE;
		// Loop through the inner while loop once per frame in scene.
		while (returnCode == CONTINUE_SCENE)
		{

			GE161::Game::addPending();

			int startTime = getTicks();
			int secondTimer = startTime;
			eventQueue_->getSDLEvents();
			eventQueue_->callEventListeners();

			window_->clearBackground();
			returnCode = scene->draw();


			for (GE161::GameObject* g : theGame->gameObjects){
				g->update();
			}

			for (GE161::GameObject* g : theGame->gameObjects){
				for (GE161::GameObject* o : theGame->gameObjects){
					if (g == o) continue;
					else if (g->overlapsWith(*o)) {
						g->onCollisionEnter(*o);
					}
				}
			}

			removePending();

			window_->drawToScreen();

			delay(startTime + MS_PER_FRAME - getTicks());

			timeDelta += (getTicks() - secondTimer);
			frameCounter++;

			//if it's been one second
			if (timeDelta >= 1000) {
				//reset the timeDelta
				secondTimer = getTicks();
				timeDelta = 0;
				//log how many frames elapsed and reset
				fps.push_back(frameCounter);
				frameCounter = 0;
				//if we've got 5 numbers, get the average, and clear out the vector
				if (fps.size() >= 5){
					int avgFramesRendered = 0;
					for (int x : fps)
						avgFramesRendered += x;
					avgFramesRendered /= fps.size();
					debugOut(std::to_string(avgFramesRendered));
					fps.clear();
				}
			}

		}
		std::string m = std::string("return code from ") + sceneName + std::string(": ") + std::to_string(returnCode);
		debugOut(m);
	}

	SDL_Quit();
	return;
}