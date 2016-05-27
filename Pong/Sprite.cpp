#include "Sprite.h"
#include "Game.h"


GE161::Sprite::Sprite(int frameWidth, int frameHeight) :
frameWidth_(frameWidth),
frameHeight_(frameHeight)
{
}


GE161::Sprite::~Sprite()
{
}

int GE161::Sprite::makeFrame(std::string fileName, int x, int y, int width, int height)
{
	// Turn this fileName into an SDL_Texture. We only want to do this once,
	// so we store textures in a map, and reuse if needed.
	SDL_Surface* loadedSurface = IMG_Load((fileName).c_str());
	SDL_Texture* tex;
	if (storedTextures.count(fileName) == 1)  // already seen?
	{
		tex = storedTextures[fileName];
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 237, 28, 36));
		//tex = IMG_LoadTexture(GE161::Game::theGame->getRenderer(), fileName.c_str());
		tex = SDL_CreateTextureFromSurface(GE161::Game::theGame->getRenderer(), loadedSurface);
		if (tex == nullptr)
		{
			fatalSDLError("In Sprite::makeFrame(), IMG_LoadTexture: ", SDL_GetError());
			return -1;
		}
		storedTextures[fileName] = tex;
	}

	frames.push_back({ tex, x, y, width, height });
	return frames.size() - 1;
}

void GE161::Sprite::makeFramesFromFile(std::string imageFile, std::string textFile){
	std::ifstream f;
	std::string line;
	std::string token;
	std::vector<std::string> tokens;

	f.open(textFile);
	while (std::getline(f, line)){
		std::istringstream s(line);

		while (s >> token)
			tokens.push_back(token);
		if (tokens.size() < 5) continue;

		int f = makeFrame(imageFile, 
			std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]));
		addFrameToSequence(tokens[0], f);
		tokens.clear();
	}

}



int GE161::Sprite::addFrameToSequence(std::string sequenceName, int frameIndex)
{
	auto p = sequenceList[sequenceName];
	p.first.push_back(frameIndex);
	p.second = 0;
	sequenceList[sequenceName] = p;
	// Note that this method always (re)sets the pointer into the vector
	// of frameIndexes back to 0.  Shouldn't be a problem, since presumably
	// all calls to addFrameToSequence() occur before the sprite starts being drawn.
	return p.first.size();
}

int GE161::Sprite::getNextFrameIndex(std::string sequenceName)
{
	auto p = sequenceList[sequenceName];
	if (p.first.size() == 0)	// sequenceName was not found, so a pair was created.
	{
		fatalSDLError("In Sprite::getNextFrameIndex(), sequenceName was not found: ", sequenceName);
		return 0;
	}
	// Recall that p is a pair; the first part is a vector of frameIndexes, and
	// the second part is an index into that vector, pointing at the next frame to
	// be displayed.
	int frameIndexToReturn = p.first[p.second];
	p.second++;
	if (p.second >= p.first.size())
		p.second = 0;
	sequenceList[sequenceName] = p;
	return frameIndexToReturn;
}

void GE161::Sprite::update(){

}