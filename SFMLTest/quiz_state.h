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
	sf::Uint64 correctAnswerCount;
	sf::Uint64 quizNumber; 
	sf::String quizQuestion;
	sf::String correctWrittenAnswer;
	bool multipleChoiceBool; // if 1 it's a multiple choice question else, an answer must be typed in
	sf::View view;
	void setupGui();



	tgui::Gui* gui;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	QuizState(Game* game);
	~QuizState();

	void updateMultipleChoiceQuestion(sf::Uint64 questionNumber, sf::String question, sf::String answer1, sf::String answer2, sf::String answer3, sf::String answer4);
	void updateWrittenAnswerQuestion(sf::Uint64 questionNumber, sf::String question);
	//void setupMultipleChoiceButtons(sf::String answer1, sf::String answer2, sf::String answer3, sf::String answer4);
	void showCorrectAnswer(Selection correctAnswer);
	void resetRadioButton();
	void setupMultipleChoiceQuestion(sf::Uint64 questionNumber, sf::String question, sf::String answerA, sf::String answerB, sf::String answerC, sf::String answerD);
	void setupWrittenAnswerQuestion(sf::Uint64 questionNumber, sf::String question);
	void hideAllTGuiElements();
	void processQuestionGuiState();
};