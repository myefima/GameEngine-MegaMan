#pragma once

#include "Tile.h"

GE161::Tile::Tile(std::string tileName,int worldX, int worldY, int width, int height, 
	int left, int right, bool collides, int colliderLeftOffset, int colliderTopOffset){
	x_ = worldX;
	y_ = worldY;
	width_ = width;
	height_ = height;
	leftHeight = left;
	rightHeight = right;
	tileName_ = tileName;
	tileType_ = -1;
	if (collides){
		hasCollider_ = true;
		BoxCollider* collider = new BoxCollider(width_, height_,colliderLeftOffset,colliderTopOffset);
		attachComponent("BoxCollider", collider);
	}
	else {
		hasCollider_ = false;
	}
}


GE161::Tile::~Tile(){

}

void GE161::Tile::destroy(){

}