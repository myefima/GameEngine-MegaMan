#include "GameObject.h"
#include "Game.h"


GE161::GameObject::GameObject(int startingX, int startingY) :
x_(startingX),
y_(startingY)
{
}


GE161::GameObject::~GameObject()
{
}

void GE161::GameObject::setPos(int x, int y)
{
	x_ = x;
	y_ = y;
}

void GE161::GameObject::moveX(int delta)
{
	x_ += delta;
}

void GE161::GameObject::moveY(int delta)
{
	y_ += delta;
}

int GE161::GameObject::getX()
{
	return x_;
}

int GE161::GameObject::getY()
{
	return y_;
}

void GE161::GameObject::draw(int frameIndex, bool flip)
{
	Sprite* sprite_ = (GE161::Sprite*) getComponent("Sprite");

	if (sprite_ == nullptr)
	{
		debugOut("GameObject::draw called, but no Sprite is attached.");
		return;
	}
	
	SDL_Rect srcrect = {sprite_->frames[frameIndex].x, sprite_->frames[frameIndex].y, 
		sprite_->frames[frameIndex].width, sprite_->frames[frameIndex].height};

	SDL_Rect destrect = { x_ - GE161::Game::theGame->camera()->getX(), y_ - GE161::Game::theGame->camera()->getY(), sprite_->frameWidth_, sprite_->frameHeight_ };
	//int success = SDL_RenderCopy(GE161::Game::theGame->getRenderer(), sprite_->frames[frameIndex].texture, &srcrect, &destrect);
	int success = flip ? SDL_RenderCopyEx(GE161::Game::theGame->getRenderer(), sprite_->frames[frameIndex].texture, &srcrect, &destrect, 0, nullptr, SDL_FLIP_HORIZONTAL)
		: SDL_RenderCopy(GE161::Game::theGame->getRenderer(), sprite_->frames[frameIndex].texture, &srcrect, &destrect);
	if (success != 0)
	{
		fatalSDLError("In GameObject::draw, SDL_RenderCopy: ", SDL_GetError());
	}

}

void GE161::GameObject::draw(std::string sequenceName, bool flip)
{
	Sprite* sprite_ = (GE161::Sprite*) getComponent("Sprite");

	draw(sprite_->getNextFrameIndex(sequenceName), flip);
}


//deprecate in megaman clone
GE161::Texty* GE161::GameObject::text(){
	return (GE161::Texty*) getComponent("Text");
}

bool GE161::GameObject::overlapsWith(GameObject& otherGameObject){

	BoxCollider* our = (BoxCollider*) getComponent("BoxCollider");
	BoxCollider* other = (BoxCollider*) otherGameObject.getComponent("BoxCollider");

	if (our == nullptr || other == nullptr)
		return false;

	return our->right() > other->left() &&
		our->left() < other->right() &&
		our->bottom() > other->top() &&
		our->top() < other->bottom();

}

void GE161::GameObject::update(){
	debugOut("in game object update");
}

void GE161::GameObject::attachComponent(std::string componentType, GE161::Component* component){
	components[componentType].emplace_back(component);
	component->setGameObject(this);
}


GE161::Component* GE161::GameObject::getComponent(std::string componentType){
	if (components[componentType].size() != 0)
		return components[componentType][0];
	//debugOut("No components of type <" + componentType + ">");
	return nullptr;
}

GE161::Component* GE161::GameObject::getComponentWithID(std::string componentType, std::string id){
	std::vector<GE161::Component*> comps = getComponents(componentType);
	
	for (Component* c : comps)
		if (c->getID() == id)
			return c;
	//debugOut("No components of type <" + componentType + "> with ID: " + id);
	return nullptr;

}

std::vector<GE161::Component*> GE161::GameObject::getComponents(std::string componentType){
	return components[componentType];
}

std::vector<GE161::Component*> GE161::GameObject::getComponentsWithID(std::string componentType, std::string id){
	std::vector<GE161::Component*> comps = getComponents(componentType);
	std::vector<GE161::Component*> answer;

	for (Component* c : comps)
		if (c->getID() == id)
			answer.push_back(c);

	return answer;
}

void GE161::GameObject::onCollisionEnter(GameObject& otherGameObject){
	debugOut("in base collision enter");
}

void GE161::GameObject::destroy(){

}

void GE161::GameObject::afterDestroy(){

}