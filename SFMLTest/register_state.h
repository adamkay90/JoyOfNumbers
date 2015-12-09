#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <TGUI\TGUI.hpp>
#include <iostream>

#include "game_state.h"
#include "game_state_login.h"

class RegisterState : public GameState
{
private:

	sf::View view;

	void loadMenu();
	void onLoginButtonClick();
	void onRegisterButtonClick();
	void getDataFromTextBoxes();

	void SetupGui();

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	RegisterState(Game* game);
	~RegisterState();

	tgui::Gui* gui;
};