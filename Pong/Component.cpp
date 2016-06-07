#pragma once

#include "Component.h"

GE161::Component::Component(){

}

void GE161::Component::setID(std::string id){
	component_id = id;
}

std::string GE161::Component::getID(){
	return component_id;
}

void GE161::Component::setGameObject(GE161::GameObject* gameObject){
	g = gameObject;
}

GE161::GameObject* GE161::Component::GameObject(){
	return g;
}

void GE161::Component::destroy(){

}