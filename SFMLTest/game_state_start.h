#pragma once

#include <SFML/Graphics.hpp>

#include "game_state.h"

class GameStateStart : public GameState
{
private:

	sf::View view;

	void loadGame();

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateStart(Game* game);
};