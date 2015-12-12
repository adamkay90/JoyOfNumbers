#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "menu_state.h"
#include "game_state_editor.h"
#include "game_state.h"
#include "quiz_state.h"

class MenuState : public GameState
{
private:

	sf::View view;
	void setupGui();
	std::vector<bool> unlockedMenus;
	void unlockMenu(int menuToUnlock);


public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	tgui::Gui* gui;
	MenuState(Game* game);
	~MenuState();
};