#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "game_state.h"
#include "game_state_editor.h"
#include "game_state.h"

class QuizState : public GameState
{
private:

	enum Selection {A = 0, B = 1, C = 2, D = 3};

	Selection currentChoice;
	Selection correctAnswer;

	sf::View view;
	sf::CircleShape s1, s2, s3, s4;
	void setupGui();



	tgui::Gui* gui;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	QuizState(Game* game);
	~QuizState();

	void showCorrectAnswer(Selection correctAnswer);
	void resetRadioButtonColor();
	void changeText(std::string questionNumber, std::string question, std::string answerA, std::string answerB, std::string answerC, std::string answerD);
};