#include "Game.h"

int main(int, char**)
{
	// The magic number is meant to prevent Game::main() from being called
	// by the subclassed game program.
	GE161::Game::theGame->main(8675309);
	return 0;
}

