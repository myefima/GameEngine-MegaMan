#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include "Component.h"
#include "GE161int.h"

namespace GE161
{
	class Sprite : public GE161::Component
	{
		friend class GameObject;
	private:
		void update();


		int frameWidth_, frameHeight_;

		struct frame
		{
			SDL_Texture* texture;
			int x;		// x and y indicate the upper left hand corner
			int y;		// of the frame in the SDL_Texture
			int width;
			int height;
		};

	public:
		Sprite(int frameWidth, int frameHeight);
		~Sprite();

		int makeFrame(std::string fileName, int x, int y, int width, int height);
		void makeFramesFromFile(std::string imageFile, std::string textFile);
		int addFrameToSequence(std::string sequenceName, int frameIndex);
		int getNextFrameIndex(std::string sequenceName);
		std::vector<frame> frames;

		// The sequenceList map is use to map a sequenceName string to both
		// a vector of frameIndexes, and the index of the current frameIndex.
		std::map<std::string, std::pair<std::vector<int>, unsigned int>> sequenceList;
		std::map<std::string, SDL_Texture*> storedTextures;
	};

}

