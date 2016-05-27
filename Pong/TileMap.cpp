#pragma once

#include "TileMap.h"

GE161::TileMap::TileMap(std::string file, int sheetWidth, int sheetHeight){
	num_tiles = 0;
	tileFile = file;
	tileSheet = new Sprite(sheetWidth, sheetHeight);
	GE161::Game::theGame->addGameObject(this);
}

int GE161::TileMap::createTile(std::string tileName,int sheetX, int sheetY, int width, int height){
	int f = tileSheet->makeFrame(GE161::Game::basePath() + tileFile, sheetX, sheetY, width, height);
	tileSheet->addFrameToSequence(tileName, f);	
	return num_tiles++;
}

int GE161::TileMap::createTiles(std::string fileName){
	std::ifstream f;
	std::string line;
	std::string token;
	std::vector<std::string> tokens;
	int lineCount = 0;

	f.open(GE161::Game::basePath() + fileName);
	while (std::getline(f, line)){
		std::istringstream s(line);
		lineCount++;

		tokens.clear();

		while (s >> token)
			tokens.push_back(token);

		if (tokens.size() < 5) { 
			debugOut("Error in " + fileName);
			debugOut("Line: " + std::to_string(lineCount) + " \"" + line + "\"");
			continue; 
		}

		createTile(tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]));
		num_tiles++;
	}

	f.close();

	return num_tiles;
}

void GE161::TileMap::setTile(std::string tileName, int worldX, int worldY, 
	int leftHeight, int rightHeight, bool collides, int colliderLeftOffset, int colliderTopOffset){
	int frameIndex = tileSheet->getNextFrameIndex(tileName);
	Tile* t = new Tile(tileName, worldX, worldY, tileSheet->frames[frameIndex].width, tileSheet->frames[frameIndex].height, 
		leftHeight, rightHeight, collides, colliderLeftOffset, colliderTopOffset);
	tiles.emplace_back(t);
}

void GE161::TileMap::reloadTiles(std::string tileSetFile, std::string tileMapFile) {
	tiles.clear();
	createTiles(tileSetFile);
	setTiles(tileMapFile);
}


void GE161::TileMap::setTiles(std::string fileName){
	std::ifstream f;
	std::string line;
	std::string token;
	std::vector<std::string> tokens;
	int lineCount = 0;
	f.open(GE161::Game::basePath() + fileName);
	while (std::getline(f, line)){
		lineCount++;

		std::istringstream s(line);
		tokens.clear();

		while (s >> token)
			tokens.push_back(token);
		if (tokens.size() < 7) {
			debugOut("Error in " + fileName);
			debugOut("Line: " + std::to_string(lineCount) + " \"" + line + "\"");
			tokens.clear();
			continue;
		}

		if (std::stoi(tokens[5]) == 1)
			setTile(tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), 
				std::stoi(tokens[3]), std::stoi(tokens[4]), true, std::stoi(tokens[6]), std::stoi(tokens[7]));
		else
			setTile(tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), 
				std::stoi(tokens[3]), std::stoi(tokens[4]), false, std::stoi(tokens[6]), std::stoi(tokens[7]));
	}

	f.close();

}

void GE161::TileMap::drawTiles(){
	Camera* camera = GE161::Game::theGame->camera();
	Window* window = GE161::Game::theGame->window();

	int left = camera->getX();
	int right = left + window->clientWidth();
	int top = camera->getY();
	int bottom = top + window->clientHeight();
	
	for (Tile* t : tiles){
		if (t->getX() + t->width_ < left ||
			t->getX() > right ||
			t->getY() > bottom ||
			t->getY() + t->height_ < top) continue;

		if (tileSheet == nullptr)
		{
			debugOut("GameObject::draw called, but no Sprite is attached.");
			return;
		}

		int frameIndex = tileSheet->getNextFrameIndex(t->tileName_);
		SDL_Rect srcrect = { tileSheet->frames[frameIndex].x, tileSheet->frames[frameIndex].y,
			tileSheet->frames[frameIndex].width, tileSheet->frames[frameIndex].height };

		SDL_Rect destrect = { t->getX() - GE161::Game::theGame->camera()->getX(), t->getY() - GE161::Game::theGame->camera()->getY(), 
			t->width_, t->height_ };
		int success = SDL_RenderCopy(GE161::Game::theGame->getRenderer(), tileSheet->frames[frameIndex].texture, &srcrect, &destrect);
		if (success != 0)
		{
			fatalSDLError("In GameObject::draw, SDL_RenderCopy: ", SDL_GetError());
		}
	}
}


void GE161::TileMap::update(){
	drawTiles();
}