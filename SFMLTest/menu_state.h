#pragma once

#include <SFML/Graphics.hpp>

#include "menu_state.h"
#include "game_state_editor.h"
#include "game_state.h"
#include "quiz_state.h"

class MenuState : public GameState
{
private:

	sf::View view;
	void loadQuiz();

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	MenuState(Game* game);
};