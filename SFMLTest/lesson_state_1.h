#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <TGUI\TGUI.hpp>
#include <iostream>

#include "game_state.h"
#include "register_state.h"
#include "quiz_state.h"
#include "animation_handler.h"

class LessonState1 : public GameState
{
private:

	sf::View view;

	int dialogID;
	sf::Sprite face;
	sf::Sprite textBubble;
	sf::Text text;
	tgui::Gui* gui;
	void setupGui();
	void nextDialog();
	void previousDialog();
	std::vector<std::string> dialog;

	AnimationHandler faceAniHandler;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	LessonState1(Game* game);
	~LessonState1();
};