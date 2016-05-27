#pragma once

#include "GameObject.h"
#include "Game.h"

namespace GE161{
	class Tile : public GameObject {
		friend class TileMap;
	public:
		Tile(std::string tileName, int worldX, int worldY, int width, int height, 
			int left, int right, bool collides = false, int colliderLeftOffset = 0, int colliderTopOffset = 0);
		~Tile();
		int leftHeight, rightHeight;
	private:
		bool hasCollider_;
		int width_, height_;
		std::string tileName_;
		int tileType_;
	};
}