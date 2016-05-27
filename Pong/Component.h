#pragma once

#include <string>

namespace GE161{

	class Component {
		friend class GameObject;

		std::string component_id = "";
	protected:
		GE161::GameObject* g;
	public:
		Component();
		void setID(std::string id);
		std::string getID();
		void setGameObject(GE161::GameObject* gameObject);
		GE161::GameObject* GameObject();
	};

}