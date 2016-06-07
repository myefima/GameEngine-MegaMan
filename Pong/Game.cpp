#include "Game.h"

const std::string GE161::Game::START_GAME = "*STARTGAME*";
const std::string GE161::Game::EXIT_GAME = "*EXITGAME*";

//The linker wants this static variable defined here; it will get
// its actual value in main().
GE161::Game* GE161::Game::theGame = nullptr; 

GE161::Game::Game()
{
	// Store a pointer to the game in a static variable for access by main().
	if (theGame == nullptr)
	{
		theGame = this;
		theGame->framerate_ = 60;
	}
	else
	{
		fatalSDLError("More than one game object has been created.");
	}

	//register the collision event with SDL 
	Uint32 collisionEvent = SDL_RegisterEvents(3);
	if (collisionEvent != ((Uint32)-1)) {
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		event.type = GE161::Event::COLLISION;

		SDL_Event event2;
		SDL_memset(&event2, 0, sizeof(event2));
		event2.type = GE161::Event::BALL_COIN_COLLISION;

		SDL_Event event3;
		SDL_memset(&event3, 0, sizeof(event3));
		event3.type = GE161::Event::BOMB_COIN_COLLISION;

		SDL_Event event4;
		SDL_memset(&event4, 0, sizeof(event4));
		event4.type = GE161::Event::FLOOR_COLLISION;
	}

}


GE161::Game::~Game()
{
}

void GE161::Game::addScene(std::string name, Scene* scene)
{
	sceneMap[name] = scene;

}

GE161::Scene* GE161::Game::lookUpScene(std::string name)
{
	if (sceneMap.count(name) == 1)
		return sceneMap[name];

	fatalSDLError("in Game::lookUpScene, scene name not found:", name);

	return nullptr;
}

SDL_Renderer* GE161::Game::getRenderer()
{
	return window_->sdl_renderer;
}

void GE161::Game::delay(int milliseconds)
{
	if (milliseconds <= 0)
		return;
	SDL_Delay(static_cast<unsigned int>(milliseconds));
}

std::string GE161::Game::pathSlash()
{
#ifdef _WIN32
	return std::string("\\");
#else
	return std::string("/");
#endif
}

int GE161::Game::getTicks()
{
	return static_cast<int>(SDL_GetTicks());
}

void GE161::Game::registerAsListener(int eventType, EventListener* listener)
{
	theGame->eventQueue_->registerAsListener(eventType, listener);
}



// Based on res_path.h.
std::string GE161::Game::basePath()
{
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty())
	{
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath)
		{
			baseRes = basePath;
			SDL_free(basePath);
		}
		else
		{
			fatalSDLError("error in Game::basePath", SDL_GetError());
			baseRes = "";
		}
	}
	return baseRes;
}

void GE161::Game::debugOut(std::string message)
{
	OutputDebugString((message + "\n").c_str());
}

GE161::Window* GE161::Game::window()
{
	return window_;
}

GE161::Camera* GE161::Game::camera(){
	return camera_;
}


void GE161::Game::setWindowBackgroundColor(int r, int g, int b, int a){
	if (a < 0)
		theGame->window()->a_ = 0;
	else if (a > 255)
		theGame->window()->a_ = 255;
	else
		theGame->window()->a_ = a;

	if (r < 0)
		theGame->window()->r_ = 0;
	else if (r > 255)
		theGame->window()->r_ = 255;
	else
		theGame->window()->r_ = r;

	if (g < 0)
		theGame->window()->g_ = 0;
	else if (g > 255)
		theGame->window()->g_ = 255;
	else
		theGame->window()->g_ = g;

	if (b < 0)
		theGame->window()->b_ = 0;
	else if (b > 255)
		theGame->window()->b_ = 255;
	else
		theGame->window()->b_ = b;

}

void GE161::Game::setFrameRate(int framerate){
	if (framerate <= 15)
		theGame->framerate_ = 15;
	else
		theGame->framerate_ = framerate;
}

int GE161::Game::framerate(){
	return theGame->framerate_;
}


void GE161::Game::sendEvent(int eventType){
	SDL_Event s;
	s.type = eventType;
	SDL_PushEvent(&s);
}

void GE161::Game::addGameObject(GameObject* gameObject){
	//gameObjects.emplace(gameObjects.begin(), gameObject);
	pendingObjects.emplace(pendingObjects.begin(), gameObject);
}

void GE161::Game::addPending(){
	while (pendingObjects.size() > 0){
		gameObjects.emplace_back(pendingObjects.front());
		pendingObjects.erase(pendingObjects.begin());
	}
}

void GE161::Game::removeGameObject(GameObject* gameObject){
	pendingRemoval.emplace_back(gameObject);
}

void GE161::Game::removePending(){
	for (GE161::GameObject* g : pendingRemoval)
		for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it){
			if (*it == g){
				gameObjects.erase(it);
				g->afterDestroy();
				break;
			}
		}
	pendingRemoval.clear();
}

void GE161::Game::setController(){
	gameController = SDL_GameControllerOpen(0);
	if (!gameController)
		debugOut("Unable to open controller");
}