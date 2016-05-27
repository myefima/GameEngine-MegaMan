#include "Window.h"


GE161::Window::Window()
{
	width_ = height_ = DEFAULT_WINDOW_DIMENSION;  // default values

	r_ = 255;
	g_ = 255;
	b_ = 255;
	a_ = SDL_ALPHA_OPAQUE;

	title_ = "<No title>";
	isInitialized = false;
}


GE161::Window::~Window()
{
	if (isInitialized)
		SDL_DestroyWindow(sdl_window);
}

void GE161::Window::size(int width, int height)
{
	if (width >= MIN_WINDOW_DIMENSION && width <= MAX_WINDOW_DIMENSION && 
		height >= MIN_WINDOW_DIMENSION && height <= MAX_WINDOW_DIMENSION)
	{
		width_ = width;
		height_ = height;
	}
}

void GE161::Window::title(std::string t)
{
	title_ = t;
}

bool GE161::Window::initialize()
{
	// Only initialize the window once.
	if (isInitialized)
	{
		return true;
	}

	sdl_window = SDL_CreateWindow(title_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width_, height_, SDL_WINDOW_SHOWN);
	if (sdl_window == nullptr)
	{
		fatalSDLError("In Window::initialize(), SDL_CreateWindow: ", SDL_GetError());
		return false;
	}

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (sdl_renderer == nullptr)
	{
		fatalSDLError("In Window::initialize(), SDL_CreateRenderer: ", SDL_GetError());
		return false;
	}

	isInitialized = true;

	return true;
}

void GE161::Window::clearBackground()
{
	int rc = SDL_SetRenderDrawColor(sdl_renderer, r_, g_, b_, a_);
	if (rc != 0)
	{
		fatalSDLError("In Window::clearBackground(), SDL_SetRenderDrawColor returned non-zero: ", SDL_GetError());
		return;
	}
	rc = SDL_RenderClear(sdl_renderer);
	if (rc != 0)
	{
		fatalSDLError("In Window::clearBackground(), SDL_RenderClear returned non-zero: ", SDL_GetError());
		return;
	}
}

void GE161::Window::drawToScreen()
{
	SDL_RenderPresent(sdl_renderer);
}

int GE161::Window::clientWidth()
{
	int w1, w2, h1, h2;
	SDL_GetWindowSize(sdl_window, &w1, &h1);
	SDL_GetRendererOutputSize(sdl_renderer, &w2, &h2);
	// The next line is for my (Frost's) curiousity.  Do these two functions ever return
	// different results?  So far, no.
	if (w1 != w2 || h1 != h2)
		debugOut(std::string("**** GetWindowSize and GetRendererOutputSize are not in sync ") +
		std::to_string(w1) + " " +
		std::to_string(w2) + ", " +
		std::to_string(h1) + " " +
		std::to_string(h2) + " ");
	return w1;
}

int GE161::Window::clientHeight()
{
	int w1, w2, h1, h2;
	SDL_GetWindowSize(sdl_window, &w1, &h1);
	SDL_GetRendererOutputSize(sdl_renderer, &w2, &h2);
	if (w1 != w2 || h1 != h2)
		debugOut(std::string("**** GetWindowSize and GetRendererOutputSize are not in sync ") +
		std::to_string(w1) + " " +
		std::to_string(w2) + ", " +
		std::to_string(h1) + " " +
		std::to_string(h2) + " ");
	return h1;
}
