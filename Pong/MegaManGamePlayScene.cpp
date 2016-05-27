#include "MegaManGamePlayScene.h"

#include <stdlib.h>		// srand, rand
#include <time.h>		// time
#include <cmath>
//PongGamePlayScene.cpp

MegaManGamePlayScene::MegaManGamePlayScene(MegaManGame* m) :
theGame(m)
{
}

MegaManGamePlayScene::~MegaManGamePlayScene()
{
}

bool MegaManGamePlayScene::setup()
{
	level_width = level_height = 800;
	
	renderTop = new GE161::TileMap("x3_tileset.png", 1317, 1387);
	renderTop->createTiles("tiles.txt");
	renderTop->setTiles("top_tiles.txt");

	megaMan = new MegaMan(60, 323, 5, 34, 32);
	
	tm = new GE161::TileMap("x3_tileset.png", 1317, 1387);
	tm->createTiles("tiles.txt");
	tm->setTiles("tilemap.txt");


	GE161::Game::registerAsListener(GE161::Event::KEY_DOWN, this);
	GE161::Game::registerAsListener(GE161::Event::KEY_UP, this);
	GE161::Game::registerAsListener(GE161::Event::COLLISION, this);

	exitRequested = false;

	music = new BGMusic("MM2Fortress1.mp3");

	return true;
}

int MegaManGamePlayScene::draw()
{

	theGame->camera()->setX(megaMan->getX() - theGame->window()->clientWidth() / 2);
	theGame->camera()->setY(24 + theGame->window()->clientHeight() / 2);

	//mm tile collision
	GE161::BoxCollider *our = (GE161::BoxCollider*) megaMan->getComponent("BoxCollider");
	if (megaMan->left)  megaMan->moveX(-5);
	if (megaMan->right) megaMan->moveX(5);

	int resolveX = 0, resolveY = 0;
	for (GE161::Tile* t : tm->tiles){
		if (megaMan->overlapsWith(*t)){
			GE161::BoxCollider *their = (GE161::BoxCollider*) t->getComponent("BoxCollider");
			if (t->leftHeight - t->rightHeight != 0) continue;
			//check from right
			if (our->left() < their->right() && our->right() > their->right())
				resolveX = their->right() - our->left();
			//check from left
			else if (our->right() > their->left() && our->left() < their->left())
				resolveX = their->left() - our->right();	
			megaMan->moveX(resolveX);
			break;
			}
		}
	
	if (megaMan->up) megaMan->moveY(-15);
	if (megaMan->down) megaMan->moveY(3);

	//gravity
	megaMan->moveY(4);

	for (GE161::Tile* t : tm->tiles){
		if (megaMan->overlapsWith(*t)){
			GE161::BoxCollider *their = (GE161::BoxCollider*) t->getComponent("BoxCollider");
			if (t->leftHeight - t->rightHeight != 0){//if on a slope

					float h, w, pos, offset;
					//convert left and right heights to "world" values
					int lower = t->leftHeight < t->rightHeight ? t->leftHeight : t->rightHeight;
					int higher = t->leftHeight > t->rightHeight ? t->leftHeight : t->rightHeight;
					lower = their->bottom() - lower;
					higher = their->bottom() - higher;

					if (our->bottom() > higher - 2 && our->bottom() < their->bottom() && 
						our->left() < their->right() && our->right() > their->left()) {
						//get sides of the triangle
						h = lower - higher;
						bool leftIsHigher = t->leftHeight > t->rightHeight;
						if (leftIsHigher)
							w = their->left() - their->right();
						else
							w = their->right() - their->left();
						//get the angle
						float theta = atan(h / w);
						//upward slope
						if (!leftIsHigher)
							pos = their->right() - our->right();
						//downward slope
						else
							pos = our->left() - their->left();
						//height offset
						offset = theta * pos;
						//upward right
						if (leftIsHigher)
							megaMan->setPos(megaMan->getX(), their->top() - offset - megaMan->frameHeight_);
						//upward left
						//else
						//	megaMan->setPos(megaMan->getX(), their->top() + offset);
						break;
					}
			} else {
				//check from above
				if (our->bottom() > their->top() && our->top() < their->top() && our->left() < their->right() && our->right() > their->left())
					resolveY = their->top() - our->bottom();
				//check from below
				else if (our->top() < their->bottom() && our->bottom() > their->bottom() && our->left() < their->right() && our->right() > their->left())
					resolveY = their->bottom() - our->top();
				megaMan->moveY(resolveY);
			}
		}
	}
	
	if ( !exitRequested)
	{
		//reset bounce count in case we want to change functionality later to restart the game
		return GE161::Game::CONTINUE_SCENE;
	}
	else     // bounced out
	{
		return -1;  // stop game
	}

}

void MegaManGamePlayScene::onEvent(GE161::Event& event){

	if (event.type == GE161::Event::KEY_DOWN)
	{
		if (event.key == "X")
			exitRequested = true;
		else if (event.key == "DOWN"){
			megaMan->down = true;
		}
		else if (event.key == "UP"){
			megaMan->up = true;
		}
		else if (event.key == "LEFT"){
			megaMan->left = true;
		}
		else if (event.key == "RIGHT"){
			megaMan->right = true;
		}
		else if (event.key == "R"){
			tm->reloadTiles("tiles.txt", "tilemap.txt");
			renderTop->reloadTiles("tiles.txt", "top_tiles.txt");
		}
}
	
	if (event.type == GE161::Event::KEY_UP){
		if (event.key == "DOWN")
			megaMan->down = false;
		else if (event.key == "UP")
			megaMan->up = false;
		else if (event.key == "LEFT")
			megaMan->left = false;
		else if (event.key == "RIGHT")
			megaMan->right = false;
	}
	


	if (event.type == GE161::Event::COLLISION){
		//debugOut("Collision!");
	}

}

