#pragma once

#include "Window.h"

namespace GE161 {
	class Camera{
	public:
		Camera(int startX, int startY, int clientWidth, int clientHeight);
		~Camera();
		int getX();
		int getY();
		void setX(int newX);
		void setY(int newY);
		int camWidth();
		int camHeight();
	private:
		int x, y, width, height;
	};
}
