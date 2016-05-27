#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Tile.h"
#include <fstream>
#include <sstream>

namespace GE161 {
	class TileMap: public GameObject{
	public:
		TileMap(std::string file, int sheetWidth, int sheetHeight);
		~TileMap();
		/*void mapTileNames(std::map < std::string, int> tile_numbers);
		void mapTileName(std::string name, int number);
		void setTileMap(std::vector<std::vector<int>> map);*/

		int createTile(std::string tileName, int sheetX, int sheetY, int width, int height); //creates tile and returns number of tiles
		int createTiles(std::string fileName);									//create tiles from a file
		void setTile(std::string name, int worldX, int worldY, 
			int leftHeight, int rightHeight, bool collides, int colliderLeftOffset = 0, int colliderTopOffset = 0);	//place a tile in the world
		void setTiles(std::string fileName);									//place tiles in world from a file
		void reloadTiles(std::string tileSetFile, std::string tileMapFile);
		//draw the tiles in update
		void drawTiles();
		void update();
		
		std::vector<Tile*> tiles;

	private:
		int num_tiles;
		std::string tileFile;
		Sprite* tileSheet;
	};
}