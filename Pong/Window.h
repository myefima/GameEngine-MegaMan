#pragma once

#include "GE161int.h"
#include <string>

namespace GE161
{
	class Window
	{
		friend class Game;
		friend class Camera;
	public:
		// The constructor creates an object, but doesn't create an
		// SDL_WINDOW or an SDL_RENDERER.
		Window();
		~Window();

		// These methods set the size and title
		void size(int width, int height);
		void title(std::string t);

		int clientWidth();
		int clientHeight();

	private:
		// The following methods are called by the Game class
		// initialize() creates an SDL_WINDOW and SDL_RENDERER
		bool initialize();
		void clearBackground();
		void drawToScreen();

		int width_;
		int height_;
		std::string title_;

		int r_;
		int g_;
		int b_;
		int a_;

		SDL_Window* sdl_window;
		SDL_Renderer* sdl_renderer;

		bool isInitialized;

		const int MIN_WINDOW_DIMENSION = 100;
		const int MAX_WINDOW_DIMENSION = 2000;
		const int DEFAULT_WINDOW_DIMENSION = 100;

	};

}