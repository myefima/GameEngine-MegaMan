#pragma once
#include "Component.h"
#include "GE161int.h"
#include "Game.h"
#include "SDL_ttf.h"

namespace GE161 {
	class Texty: public Component {
		friend class GameObject;
		friend class Game;

	public:
		Texty(std::string fontName, int fontSize, bool visible);
		void Texty::write(std::string text,int x, int y);
		enum writeOption_t { CONTINUE, NEXT_LINE };
		void GE161::Texty::write(std::string text, writeOption_t option);
		std::string text();



	private:
		void Texty::yikes(std::string message);
		void update();
		~Texty();

		TTF_Font* font_;
		int fontSize_;
		std::string fontName_;
		bool visible_;
		bool error_;
		SDL_Color color_;
		int nextX_, nextY_, lineStartX_;
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		std::string text_;
	};

}