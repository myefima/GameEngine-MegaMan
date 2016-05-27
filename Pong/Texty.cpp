// Texty.cpp

#include "Texty.h"


GE161::Texty::Texty(std::string fontName, int fontSize, bool visible) :
fontName_(fontName),
fontSize_(fontSize),
visible_(visible)
{

	error_ = false;
	if (!TTF_WasInit())
	{
		int s = TTF_Init();
		if (s)
		{
			yikes("Failed on TTF_Init()");
			return;
		}
	}

	// Open the font
	font_ = TTF_OpenFont((GE161::Game::basePath() + fontName).c_str(), fontSize_);
	if (font_ == nullptr)
	{
		yikes("TTF_OpenFont can't open " + fontName);
		return;
	}
	color_ = { 0, 0, 0, 255 };

	nextX_ = nextY_ = 10;
	lineStartX_ = nextX_;

	renderer_ = GE161::Game::theGame->getRenderer();
}

GE161::Texty::~Texty()
{
	if (error_)
		return;
	TTF_CloseFont(font_);
}

void GE161::Texty::write(std::string text, writeOption_t option)
{

	text_ = text;
	if (error_)
		return;
	if (text.length() == 0)
	{
		if (option == NEXT_LINE)
		{
			nextX_ = lineStartX_;
			nextY_ += TTF_FontHeight(font_) + 1;
		}
		// nop if CONTINUE
		return;
	}
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surface = TTF_RenderText_Blended(font_, text.c_str(), color_);
	if (surface == nullptr)
	{
		TTF_CloseFont(font_);
		yikes("TTF_RenderText error");
		return;
	}
	texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
	if (texture_ == nullptr){
		yikes(std::string("SDL_CreateTextureFromSurface errror ") + SDL_GetError());
		return;
	}

	int w, h;
	SDL_QueryTexture(texture_, NULL, NULL, &w, &h);
	SDL_Rect dest;
	if (option == CONTINUE)
	{
		dest.x = nextX_;
		dest.y = nextY_;
	}
	else // option == NEXT_LINE
	{
		dest.x = lineStartX_;
		dest.y = nextY_ + h;
	}
	dest.w = w;
	dest.h = h;
	SDL_RenderCopy(renderer_, texture_, NULL, &dest);
	nextX_ += w;
	nextY_ = dest.y;
	//std::cout << dan << " x " << dest.x << " y " << dest.y << " w " << dest.w << " h " << dest.h << "    " << text << std::endl; dan++;

	//Clean up the surface and texture
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture_);

}

void GE161::Texty::write(std::string text, int x, int y)
{
	text_ = text;
	nextX_ = x;
	nextY_ = y;
	lineStartX_ = x;

	write(text, CONTINUE);
}


void GE161::Texty::yikes(std::string message)
{
	debugOut("**Texty error " + message + " SDL_GetError: " + SDL_GetError() + "\n");
	error_ = true;

}

std::string GE161::Texty::text(){
	return text_;
}

void GE161::Texty::update(){

}