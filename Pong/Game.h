#pragma once

#include <string>
#include <map>
#include "Window.h"
#include "Camera.h"
#include "Scene.h"
#include "EventQueue.h"
#include "GameObject.h"
#include <vector>
#include <queue>

namespace GE161
{
	class Game
	{
		friend class Sprite;
		friend class GameObject;
		friend class Texty;
		friend class Audio;
		friend class Camera;
		friend class Tile;
		friend class TileMap;
	public:
		Game();
		~Game();


		// These functions are called by the game code.
		void addScene(std::string name, Scene* scene);
		Scene* lookUpScene(std::string name);
		Window* window();
		Camera* camera();
		static void registerAsListener(int eventType, EventListener* listener);

		// Helpful functions exposed to the game programmer.
		static void delay(int milliseconds);
		static std::string pathSlash();
		static std::string basePath();
		static void debugOut(std::string);
		static int getTicks();
		static void setWindowBackgroundColor(int r, int g, int b, int a);
		static void setFrameRate(int framerate);
		static int framerate();

		// These functions have to be overridden by the game code.
		virtual void setup() = 0;
		virtual std::string chooseScene(std::string prevScene, int prevReturnCode) = 0;

		// This function should be called exactly once by main().
		void main(int x);

		static const std::string START_GAME;
		static const std::string EXIT_GAME;

		static Game* theGame;
		static const int CONTINUE_SCENE = 0;
		static void sendEvent(int eventType);

		void addGameObject(GameObject* gameObject);
		void addPending();
		void removeGameObject(GameObject* gameObject);
		void removePending();
		
		std::vector<GameObject*> gameObjects;
		std::vector<GameObject*> pendingObjects;
		std::vector<GameObject*> pendingRemoval;
		void setController();

	private:
		SDL_Renderer* getRenderer();
		SDL_GameController* gameController;

		Window* window_;
		Camera* camera_;
		std::map<std::string, Scene*> sceneMap;
		EventQueue* eventQueue_;
		int framerate_;
	};

}
