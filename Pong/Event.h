#pragma once

#include <queue>
#include <string>
#include "GE161int.h"

namespace GE161
{
	class Event
	{
		friend class EventQueue;

	public:
		Event();
		Event(SDL_Event& e);
		~Event();

		// These fields are public for convenient access.
		int type;
		std::string key;
		int mouseButton;
		int mouseClicks;
		int x;
		int y;

		// event types
		static const int QUIT = SDL_QUIT;
		static const int KEY_DOWN = SDL_KEYDOWN;
		static const int KEY_UP = SDL_KEYUP;
		static const int MOUSE_MOTION = SDL_MOUSEMOTION; 
		static const int MOUSE_BUTTONDOWN = SDL_MOUSEBUTTONDOWN;
		static const int MOUSE_BUTTONUP = SDL_MOUSEBUTTONUP;
		static const int COLLISION = SDL_USEREVENT;
		static const int BALL_COIN_COLLISION = SDL_USEREVENT + 1;
		static const int BOMB_COIN_COLLISION = SDL_USEREVENT + 2;
		static const int FLOOR_COLLISION = SDL_USEREVENT + 3;

	private:
		SDL_Event sdl_event;

	};

}