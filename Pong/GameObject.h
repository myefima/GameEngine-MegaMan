#pragma once

#include <string>
#include <map>
#include <vector>
#include "GameObjectStdfx.h"

namespace GE161
{
	class GameObject
	{
	public:

		friend class Component;

		GameObject(int startingX = 0, int startingY = 0);
		~GameObject();

		void setPos(int x, int y);
		void moveX(int delta);
		void moveY(int delta);
		int getX();
		int getY();
		void draw(int frameIndex);
		void draw(std::string sequenceName);
		bool overlapsWith(GameObject& otherGameObject);
		virtual void update();
		GE161::Texty* text();


		GE161::Component* getComponent(std::string componentType); //returns first component of type
		GE161::Component* getComponentWithID(std::string componentType, std::string id);
		std::vector<GE161::Component*> getComponents(std::string componentType); //returns all components of type
		std::vector<GE161::Component*> getComponentsWithID(std::string componentType, std::string id);
		void attachComponent(std::string componentType, GE161::Component* component);

	protected:
		int x_;		// current position of
		int y_;		// this game object
		std::map<std::string, std::vector<GE161::Component*>> components;
	};

}

