#pragma once

#include <SFML/Graphics.hpp>

#include "game_state.h"
#include "quiz_state.h"

class QuizState : public GameState
{
private:

	sf::View view;
	sf::CircleShape s1, s2, s3, s4;
	void loadGame();

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	QuizState(Game* game);
};