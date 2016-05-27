#pragma once

#include <string>
#include "Component.h"
#include "SDL_mixer.h"
#include "Game.h"

namespace GE161{

	class Audio : public GE161::Component{
	public:
		enum Type { MUSIC, SAMPLE };
		Audio(std::string file, Type);
		~Audio();
		void play(int repeatCount);
		void stop();
	private:
		static int numChannels;
		int this_channel;
		Type t;
		Mix_Music* audioFile;
		Mix_Chunk* soundChunk;
	};
}