#include "stdafx.h"
#include "Game.h"

Game& Game::instance() {
	static Game* instance = new Game();
	return *instance;
}