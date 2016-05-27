#pragma once

#include "GE161int.h"
#include "EventListener.h"

namespace GE161
{
	class Scene : public EventListener
	{
	public:
		Scene();
		~Scene();

		virtual bool setup() = 0;
		virtual int draw() = 0;
	};

}

