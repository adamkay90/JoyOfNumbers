#include "quiz_state.h"

// Constructor
QuizState::QuizState(Game* game)
{

	// DATA FOR THE QUIZ
	//TODO QUIZNUMBER and QUIZ qeuestion must be passed as a constructor argument
	this->quizNumber = 1;
	this->quizQuestion = "What is the binary representation of the decimal number 5 ?";
	correctAnswer = Selection::A;

	// Setting up the state and the window
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
	QuizState::gui = new tgui::Gui(this->game->window);
	gui->setGlobalFont("media/arial.ttf");

	setupGui();

}

// Draws the window
void QuizState::draw(const float dt)
{
	this->game->window.setView(this->view);

	// Make the window black
	this->game->window.clear(sf::Color::Black);
	//this->background.setTexture(this->texManager.getRef("background"));
	this->game->window.draw(this->game->background);
	// Render the gui on top of everything
	gui->draw();
	return;
}

void QuizState::update(const float dt)
{
	// clear screen
	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	// set up the correct question design (either multiple choice or textbox that reads in values)
	if (multipleChoiceBool == 1){
		//setupMultipleChoiceQuestion(1, "" , "", "", "", "");

	}
	else {
		//setupWrittenAnswerQuestion(1, "");



	}
	// reset the button colors

	// set up the question again
	// set up the answers again
	


}

void QuizState::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type) {
		
	     // If the user closes the window
		case sf::Event::Closed: {
			game->window.close();
			break;
		}
		
		// If the user presses any key
		case sf::Event::KeyPressed: {
			// If the key was the Esc key
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
		}

		}

		gui->handleEvent(event);
	}

	// Handle the gui callbacks
	tgui::Callback callback;

	if (gui == nullptr) return;

	while (gui->pollCallback(callback))
	{
		// Make sure tha callback comes from the button
		if (callback.id == 1)
		{
			// For the submit button
			std::cout << "Submit button clicked!" << std::endl;
			showCorrectAnswer(correctAnswer);
		}
		// If the A radiobox was clicked
		else if (callback.id == 2) {
			this->currentChoice = Selection::A;
		}
		// If the B radiobox was clicked
		else if (callback.id == 3) {
			this->currentChoice = Selection::B;
		}
		// If the C radiobox was clicked
		else if (callback.id == 4) {
			this->currentChoice = Selection::C;
		}
		// If the D radiobox was clicked
		else if (callback.id == 5) {
			this->currentChoice = Selection::D;
		}
	}

	return;
}


void QuizState::setupGui() {


	//tgui::Label::Ptr labelQuestionNumber(*gui, "Question Number");
	//labelQuestionNumber->setText(std::to_string(quizNumber));
	//labelQuestionNumber->setTextSize(32);
	//labelQuestionNumber->setPosition(this->game->window.getSize().x / 2.f - labelQuestionTitle->getSize().x / 2.f + labelQuestionTitle->getSize().x + 5, 100);
	

	//tgui::Label::Ptr labelQuestionText(*gui, "Question Text");
	//labelQuestionText->setText(quizQuestion);
	//labelQuestionText->setTextSize(28);
	//labelQuestionText->setPosition(10, 150);

	// pass in the answers to the questions
	//setupMultipleChoiceButtons("101", "011", "111", "001");
	//setupMultipleChoiceQuestion(1, "asd;lfja;sdkjfasj;dkfja;sd", "1122", "123", "12312", "123123");
	setupWrittenAnswerQuestion(1, quizQuestion);

	// Create the submit button
	tgui::Button::Ptr button(*gui);
	button->load("TGUI-0.6/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(900, 700);
	button->setText("Submit");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(1);
}


/* Sets up the Quiz based on multiple choice questions, where each answer (option) is passed in as a parameter */
void QuizState::setupMultipleChoiceButtons(sf::String answer1, sf::String answer2, sf::String answer3, sf::String answer4) {

	// setups up the MultipleChoiceButtons
	tgui::RadioButton::Ptr radioButtonA(*gui, "A");
	radioButtonA->load("TGUI-0.6/widgets/Black.conf");
	radioButtonA->setPosition(200, 500);
	radioButtonA->setText(answer1);
	radioButtonA->bindCallback(tgui::RadioButton::Checked);
	radioButtonA->setCallbackId(2);
	radioButtonA->setSize(32, 32);

	tgui::RadioButton::Ptr radioButtonB = gui->copy(radioButtonA, "B");
	radioButtonB->setPosition(200, 550);
	radioButtonB->setCallbackId(3);
	radioButtonB->setText(answer2);

	tgui::RadioButton::Ptr radioButtonC = gui->copy(radioButtonA, "C");
	radioButtonC->setPosition(200, 600);
	radioButtonC->setCallbackId(4);
	radioButtonC->setText(answer3);

	tgui::RadioButton::Ptr radioButtonD = gui->copy(radioButtonA, "D");
	radioButtonD->setPosition(200, 650);
	radioButtonD->setCallbackId(5);
	radioButtonD->setText(answer4);

	return;
}



void QuizState::showCorrectAnswer(QuizState::Selection correctAnswer) {
	
	if (currentChoice == correctAnswer) {
		switch (correctAnswer)
		{
		case Selection::A:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("A");
			radioButton->setTextColor(sf::Color::Green);
			break;
		}
		case Selection::B:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("B");
			radioButton->setTextColor(sf::Color::Green);
			break;
		}
		case Selection::C:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("C");
			radioButton->setTextColor(sf::Color::Green);
			break;
		}
		case Selection::D:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("D");
			radioButton->setTextColor(sf::Color::Green);
			break;
		}
		default: break;
		}
	}
	else {
		switch (correctAnswer)
		{
		case Selection::A:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("A");
			radioButton->setTextColor(sf::Color::Green);
			break;
		}
		case Selection::B:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("B");
			radioButton->setTextColor(sf::Color::Green);
			break;
		}
		case Selection::C:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("C");
			radioButton->setTextColor(sf::Color::Green);
			break;
		}
		case Selection::D:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("D");
			radioButton->setTextColor(sf::Color::Green);
			break;
		}
		default: break;
		}

		switch (currentChoice)
		{
		case Selection::A:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("A");
			radioButton->setTextColor(sf::Color::Red);
			break;
		}
		case Selection::B:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("B");
			radioButton->setTextColor(sf::Color::Red);
			break;
		}
		case Selection::C:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("C");
			radioButton->setTextColor(sf::Color::Red);
			break;
		}
		case Selection::D:
		{
			tgui::RadioButton::Ptr radioButton = gui->get("D");
			radioButton->setTextColor(sf::Color::Red);
			break;
		}
		default:break;
		}
	}
}

void QuizState::resetRadioButtonColor() {
	tgui::RadioButton::Ptr radioButtonA = gui->get("A");
	radioButtonA->setTextColor(sf::Color::White);

	tgui::RadioButton::Ptr radioButtonB = gui->get("B");
	radioButtonB->setTextColor(sf::Color::White);

	tgui::RadioButton::Ptr radioButtonC = gui->get("C");
	radioButtonC->setTextColor(sf::Color::White);

	tgui::RadioButton::Ptr radioButtonD = gui->get("D");
	radioButtonD->setTextColor(sf::Color::White);
}


// changes the text of the quiz question as well as the multiple choice options
void QuizState::setupMultipleChoiceQuestion(sf::Uint64 questionNumber, sf::String question, sf::String answerA, sf::String answerB, sf::String answerC, sf::String answerD) {
	
	// Create the username label
	tgui::Label::Ptr labelQuestionTitle(*gui);
	labelQuestionTitle->setText("Question: " + std::to_string(quizNumber));
	labelQuestionTitle->setTextSize(32);
	labelQuestionTitle->setPosition(70, 70);

	// Where the question is displayed
	tgui::TextBox::Ptr questionBox(*gui, "questionTextbox");
	questionBox->setSize(1000, 150);
	questionBox->setPosition(140, 150);
	questionBox->setBackgroundColor(sf::Color(50, 50, 50, 100));
	questionBox->setTextColor(sf::Color(255, 255, 255));
	questionBox->setBorders(30, 30, 30, 30);
	questionBox->setBorderColor(sf::Color(50, 50, 50, 100));
	questionBox->setSize(1000, 250);
	questionBox->setText(question);
	questionBox->setReadOnly(true);

	// setups up the MultipleChoiceButtons
	tgui::RadioButton::Ptr radioButtonA(*gui, "A");
	radioButtonA->load("TGUI-0.6/widgets/Black.conf");
	radioButtonA->setPosition(200, 500);
	radioButtonA->setText(answerA);
	radioButtonA->bindCallback(tgui::RadioButton::Checked);
	radioButtonA->setCallbackId(2);
	radioButtonA->setSize(32, 32);

	tgui::RadioButton::Ptr radioButtonB = gui->copy(radioButtonA, "B");
	radioButtonB->setPosition(200, 550);
	radioButtonB->setCallbackId(3);
	radioButtonB->setText(answerB);

	tgui::RadioButton::Ptr radioButtonC = gui->copy(radioButtonA, "C");
	radioButtonC->setPosition(200, 600);
	radioButtonC->setCallbackId(4);
	radioButtonC->setText(answerC);

	tgui::RadioButton::Ptr radioButtonD = gui->copy(radioButtonA, "D");
	radioButtonD->setPosition(200, 650);
	radioButtonD->setCallbackId(5);
	radioButtonD->setText(answerD);


}


/*Sets up the written answer gui*/
void QuizState::setupWrittenAnswerQuestion(sf::Uint64 questionNumber, sf::String question){
	
	// Create the username label
	tgui::Label::Ptr labelQuestionTitle(*gui);
	labelQuestionTitle->setText("Question: " + std::to_string(quizNumber));
	labelQuestionTitle->setTextSize(32);
	labelQuestionTitle->setPosition(70, 70);

	// Where the question is displayed
	tgui::TextBox::Ptr questionBox(*gui, "questionTextbox");
	questionBox->setSize(1000, 150);
	questionBox->setPosition(140, 150);
	questionBox->setBackgroundColor(sf::Color(50, 50, 50, 100));
	questionBox->setTextColor(sf::Color(255, 255, 255));
	questionBox->setBorders(30, 30, 30, 30);
	questionBox->setBorderColor(sf::Color(50, 50, 50, 100));
	questionBox->setSize(1000, 250);
	questionBox->setText(quizQuestion);
	questionBox->setReadOnly(true);

	// Answer textbox
	tgui::TextBox::Ptr answerBox(*gui, "answerBox");
	answerBox->setSize(480, 10);
	answerBox->setPosition(500, 500);
	answerBox->setBackgroundColor(sf::Color(255, 255, 255, 150));
	answerBox->setTextColor(sf::Color(50, 50, 50));
	answerBox->setBorders(170, 25, 20, 15);
	answerBox->setBorderColor(sf::Color(255, 255, 255, 150));
	answerBox->setReadOnly(false);

	// Answer:
	tgui::Label::Ptr labelAnswerTextBox(*gui);
	labelAnswerTextBox->setText("Answer:");
	labelAnswerTextBox->setTextColor(sf::Color(50, 50, 50, 150));
	labelAnswerTextBox->setTextSize(34);
	labelAnswerTextBox->setPosition(350, 500);

	// Info Answer label
	tgui::Label::Ptr infoAnswerTextBox(*gui);
	infoAnswerTextBox->setText("*Info: Please enter your answer and click on submit once finished.");
	infoAnswerTextBox->setTextColor(sf::Color(180, 64, 16, 200));
	infoAnswerTextBox->setTextSize(24);
	infoAnswerTextBox->setPosition(300, 600);

}

QuizState::~QuizState() {
	delete gui;
}