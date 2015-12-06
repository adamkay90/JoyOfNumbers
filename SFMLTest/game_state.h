#pragma once

#include "game.h"


// Base class for all the various states we might have in our game
// This is stuff like "Main Menu", "Level Select", "Level 2", etc.
class GameState {
public:
	Game* game;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;
};