#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <TGUI\TGUI.hpp>
#include <iostream>

#include "game_state.h"
#include "register_state.h"
#include "quiz_state.h"

class LessonState : public GameState
{
private:

	sf::View view;

	int dialogID;
	sf::Sprite face;
	sf::Sprite textBubble;
	sf::Text text;
	tgui::Gui* gui;
	void setupGui();

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	LessonState(Game* game);
	~LessonState();
};