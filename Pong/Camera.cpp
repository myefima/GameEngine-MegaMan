#pragma once

#include "Camera.h"

GE161::Camera::Camera(int startX, int startY, int clientWidth, int clientHeight){
	x = startX;
	y = startY;
	width = clientWidth;
	height = clientHeight;
}

int GE161::Camera::getX(){
	return x;
}

int GE161::Camera::getY(){
	return y;
}

void GE161::Camera::setX(int newX){
	if (newX < 0)
		x = 0;
	else
		x = newX;
}

void GE161::Camera::setY(int newY){
	if (newY < 0)
		y = 0;
	else
		y = newY;
}

int GE161::Camera::camWidth(){
	return width;
}

int GE161::Camera::camHeight(){
	return height;
}