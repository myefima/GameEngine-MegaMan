#pragma once

#include <string>
#include "Component.h"
#include "Game.h"
#include "GameObject.h"

namespace GE161{
	class BoxCollider : public GE161::Component {
		int width, height, leftOffset, topOffset;
	public:
		BoxCollider(int w, int h);
		BoxCollider(int w, int h, int leftOffset, int topOffset);
		~BoxCollider();
		int left();
		int right();
		int top();
		int bottom();
		int tOffset();
		int lOffset();
	};
}