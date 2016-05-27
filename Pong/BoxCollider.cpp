#include "BoxCollider.h"

GE161::BoxCollider::BoxCollider(int w, int h){
	width = w;
	height = h;
	leftOffset = 0;
	topOffset = 0;
}

GE161::BoxCollider::BoxCollider(int w, int h, int leftOffset, int topOffset){
	width = w;
	height = h;
	this->leftOffset = leftOffset;
	this->topOffset = topOffset;
}

GE161::BoxCollider::~BoxCollider(){

}

int GE161::BoxCollider::left(){
	return g->getX() + leftOffset;
}

int GE161::BoxCollider::right(){
	return g->getX() + leftOffset + width;
}
int GE161::BoxCollider::top(){
	return g->getY() + topOffset;
}
int GE161::BoxCollider::bottom(){
	return g->getY() + topOffset + height;
}

int GE161::BoxCollider::tOffset(){
	return topOffset;
}

int GE161::BoxCollider::lOffset(){
	return leftOffset;
}