#pragma once

#include <SFML/Graphics.hpp>

#include "game_state.h"

class GameStateEditor : public GameState
{
private:

	// Here we have two different views, or two different "cameras"
	// One is for the actual game world itself
	// One is for the GUI, which is rendered on top of the game
	sf::View gameView;
	sf::View guiView;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateEditor(Game* game);
};