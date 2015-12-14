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

/* Draws the window */
void QuizState::draw(const float dt)
{
	this->game->window.setView(this->view);

	// Make the window black
	this->game->window.clear(sf::Color::Black);
	// Draw the background picture
	this->game->window.draw(this->game->background);
	// Render the gui on top of everything
	gui->draw();
	return;
}


/* Updates the base SFML GUI */
void QuizState::update(const float dt)
{
	// clear screen
	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);
	
}

/* Handles events based on callback ID that is set up when each GUI element is created */
void QuizState::handleInput()
{
	sf::Event event;

	// window closing
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
			// change the submit button to be next
			tgui::Button::Ptr next = gui->get("Submit");
			next->setText("Next");
			next->setCallbackId(6);
			
			
		}
		// If the A radiobox was clicked
		else if (callback.id == 2) {
			this->currentChoice = Selection::A;
			// enable the submit button
			tgui::Button::Ptr submitNextButton = gui-> get("Submit");
			submitNextButton->enable();
			submitNextButton->setTransparency(255);
			
		}
		// If the B radiobox was clicked
		else if (callback.id == 3) {
			this->currentChoice = Selection::B;
			// enable the submit button
			tgui::Button::Ptr submitNextButton = gui->get("Submit");
			submitNextButton->enable();
			submitNextButton->setTransparency(255);

		}
		// If the C radiobox was clicked
		else if (callback.id == 4) {
			this->currentChoice = Selection::C;
			// enable the submit button
			tgui::Button::Ptr submitNextButton = gui->get("Submit");
			submitNextButton->enable();
			submitNextButton->setTransparency(255);
		}
		// If the D radiobox was clicked
		else if (callback.id == 5) {
			this->currentChoice = Selection::D;
			// enable the submit button
			tgui::Button::Ptr submitNextButton = gui->get("Submit");
			submitNextButton->enable();
			submitNextButton->setTransparency(255);
		}

		// if next is clicked
		else if (callback.id == 6) {
			
			// return back to main menu
			if (quizNumber == 11){
				this->game->poppedState = true;
				this->game->popState();
				return;

			}
			// fire up the next question
			processQuestionGuiState();

			// set submitNextButton back to submit
			tgui::Button::Ptr submitNextButton = gui->get("Submit");
			submitNextButton->setText("Submit");
			submitNextButton->setCallbackId(1);
			submitNextButton->disable();
			submitNextButton->setTransparency(150);
		}

		// if answerbox is enabled in the written answer state of the quiz
		else if (callback.id == 7) {

			tgui::TextBox::Ptr answerBox = gui->get("answerBox");
			


			// fire up the next question
			processQuestionGuiState();
				
			tgui::Button::Ptr submitNextButton = gui->get("Submit");
			submitNextButton->enable();
			submitNextButton->setTransparency(150);

		}
	}

	return;
}

/* Sets up the initial GUI*/
void QuizState::setupGui() {


	// pass in the arguements to the questions (either multipleChoice, or typed answer)
	// TODO: process question

	setupMultipleChoiceQuestion(1, "asd;lfja;sdkjfasj;dkfja;sd", "1122", "123", "12312", "123123");
	setupWrittenAnswerQuestion(1, quizQuestion);
	hideAllTGuiElements();
	processQuestionGuiState();


	// Create the submit button
	tgui::Button::Ptr submitNextButton(*gui, "Submit");
	submitNextButton->load("TGUI-0.6/widgets/Black.conf");
	submitNextButton->setSize(260, 60);
	submitNextButton->setPosition(900, 700);
	submitNextButton->setText("Submit");
	submitNextButton->bindCallback(tgui::Button::LeftMouseClicked);
	submitNextButton->setCallbackId(1);
	submitNextButton->disable();
	submitNextButton->setTransparency(150);
}

/* Injects the right questions and question styles into the GUI */
void QuizState::processQuestionGuiState(){

	// figure out what type of question (multiple choice, written answer) it is and pass the value in
	// process questions
	switch (quizNumber)
	{
	case 1:
	{
			  updateMultipleChoiceQuestion(quizNumber, "What is the smalles natural number", " -1", " 1", " 0", " -inf");
			  correctAnswer = Selection::A;
			  quizNumber++;
			  break;
	}
	case 2:
	{
			  updateMultipleChoiceQuestion(quizNumber, "What natural number is 87 fallowed by?", " 85", " 86", " 87", " 88");
			  correctAnswer = Selection::D;
			  quizNumber++;
			  break;
	}
	case 3:
	{
			  updateMultipleChoiceQuestion(quizNumber, "What is the negation of -212", " 212", " 213", " 200", " 123");
			  correctAnswer = Selection::B;
			  quizNumber++;
			  break;
	}
	case 4:
	{
			  updateMultipleChoiceQuestion(quizNumber, "What is 58 in binary?", " 11111", " 101010", " 111010", " 100101");
			  correctAnswer = Selection::C;
			  quizNumber++;
			  break;
	}
	case 5:
	{
			  updateMultipleChoiceQuestion(quizNumber, "What is 10 in binary?", " 1011", " 1010", " 1111", " 1011");
			  correctAnswer = Selection::B;
			  quizNumber++;
			  break;
	}
	case 6:
	{
			  updateMultipleChoiceQuestion(quizNumber, "What operator can you use to get the remainder of a division operation?", " *", " %", " ^", " &");
			  correctAnswer = Selection::B;
			  quizNumber++;
			  break;
	}
	case 7:
	{
			  updateMultipleChoiceQuestion(quizNumber, "Convert 37 in decimal to binary notation.", " 100101", " 101001", " 100011", " 101011");
			  correctAnswer = Selection::A;
			  quizNumber++;
			  break;
	}
	case 8:
	{
			  updateMultipleChoiceQuestion(quizNumber, "What is the quotient and remainder of 37/5?", " quotient: 7, remainder 2", " quotient: 6, remainder: 2", " quotient: 7, remainder: 3", " quotient: 6, remainder: 4");
			  correctAnswer = Selection::A;
			  quizNumber++;
			  break;
	}
	case 9:
	{
			  updateMultipleChoiceQuestion(quizNumber, "Convert -37 to 8-bit thwo's compliment binary notation", " 11011101", " 11011011", " 11011001", " 00100101");
			  correctAnswer = Selection::B;
			  quizNumber++;
			  break;
	}
	case 10:
	{
			  updateMultipleChoiceQuestion(quizNumber, "Which of the fallowing is best represented as a negative number?", " debt", " circus elephants", " number of apples", " days left till Christmas");
			  correctAnswer = Selection::A;
			  quizNumber++;
			  break;
	}
	default: break;
	}

	

}

void QuizState::showCorrectAnswer(QuizState::Selection correctAnswer) {

	//TODO: check if it is multiple choice or a string answer and based on that
	// show the answer.
	// if users pick is the correct answer highlight it green
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
		// highlight correct answer green
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

		// if the user selected the wrong choice highlight his choice red
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

/* Checks if the written answer is correct */
bool checkWrittenAnswer(sf::String userAnswer, sf::String correctAnswer){
	// check if the two words passed in are equal

	return userAnswer == correctAnswer;

}



/* updates multiple choice answer gui */
void QuizState::updateMultipleChoiceQuestion(sf::Uint64 questionNumber, sf::String question, sf::String answer1, sf::String answer2, sf::String answer3, sf::String answer4){
	
	//resetButtonColor
	resetRadioButton();

	// Create the username label
	tgui::Label::Ptr labelQuestionTitle = gui->get("labelQuestionTitle");
	labelQuestionTitle->setText("Question: " + std::to_string(questionNumber));
	labelQuestionTitle->setTextSize(32);
	labelQuestionTitle->setPosition(70, 70);
	labelQuestionTitle->show();

	// Where the question is displayed
	tgui::TextBox::Ptr questionBox = gui -> get("questionTextbox");
	questionBox->setSize(1000, 150);
	questionBox->setPosition(140, 150);
	questionBox->setBackgroundColor(sf::Color(50, 50, 50, 100));
	questionBox->setTextColor(sf::Color(255, 255, 255));
	questionBox->setBorders(30, 30, 30, 30);
	questionBox->setBorderColor(sf::Color(50, 50, 50, 100));
	questionBox->setSize(1000, 250);
	questionBox->setText(question);
	questionBox->setReadOnly(true);
	questionBox->show();

	// setups up the MultipleChoiceButtons
	tgui::RadioButton::Ptr radioButtonA = gui-> get("A");
	radioButtonA->load("TGUI-0.6/widgets/Black.conf");
	radioButtonA->setPosition(200, 500);
	radioButtonA->setText(answer1);
	radioButtonA->bindCallback(tgui::RadioButton::Checked);
	radioButtonA->setCallbackId(2);
	radioButtonA->setSize(32, 32);
	radioButtonA->show();

	tgui::RadioButton::Ptr radioButtonB = gui-> get("B");
	radioButtonB->setPosition(200, 550);
	radioButtonB->setCallbackId(3);
	radioButtonB->setText(answer2);
	radioButtonB->show();

	tgui::RadioButton::Ptr radioButtonC = gui->get("C");
	radioButtonC->setPosition(200, 600);
	radioButtonC->setCallbackId(4);
	radioButtonC->setText(answer3); 
	radioButtonC->show();

	tgui::RadioButton::Ptr radioButtonD = gui->get("D");
	radioButtonD->setPosition(200, 650);
	radioButtonD->setCallbackId(5);
	radioButtonD->setText(answer4);
	radioButtonD->show();

}

/* updates up the written answer gui */
void QuizState::updateWrittenAnswerQuestion(sf::Uint64 questionNumber, sf::String question){

	// Create the username label
	tgui::Label::Ptr labelQuestionTitle = gui-> get("labelQuestionTitle");
	labelQuestionTitle->setText("Question: " + std::to_string(questionNumber));
	labelQuestionTitle->setTextSize(32);
	labelQuestionTitle->setPosition(70, 70);
	labelQuestionTitle->show();

	// Where the question is displayed
	tgui::TextBox::Ptr questionBox = gui -> get("questionTextbox");
	questionBox->setSize(1000, 150);
	questionBox->setPosition(140, 150);
	questionBox->setBackgroundColor(sf::Color(50, 50, 50, 100));
	questionBox->setTextColor(sf::Color(255, 255, 255));
	questionBox->setBorders(30, 30, 30, 30);
	questionBox->setBorderColor(sf::Color(50, 50, 50, 100));
	questionBox->setSize(1000, 250);
	questionBox->setText(question);
	questionBox->setReadOnly(true);
	questionBox->show();

	// Answer textbox
	tgui::TextBox::Ptr answerBox = gui-> get("answerBox");
	answerBox->setSize(480, 10);
	answerBox->setPosition(500, 500);
	answerBox->setBackgroundColor(sf::Color(255, 255, 255, 150));
	answerBox->setTextColor(sf::Color(50, 50, 50));
	answerBox->setBorders(170, 25, 20, 15);
	answerBox->setBorderColor(sf::Color(255, 255, 255, 150));
	answerBox->setReadOnly(false);
	answerBox->show();
	

	// Answer:
	tgui::Label::Ptr labelAnswerTextBox = gui -> get("labelAnswerTextBox");
	labelAnswerTextBox->setText("Answer:");
	labelAnswerTextBox->setTextColor(sf::Color(50, 50, 50, 150));
	labelAnswerTextBox->setTextSize(34);
	labelAnswerTextBox->setPosition(350, 500);
	answerBox->show();

	// Info Answer label
	tgui::Label::Ptr infoAnswerTextBox = gui -> get("infoAnswerTextBox");
	infoAnswerTextBox->setText("*Info: Please enter your answer and click on submit once finished.");
	infoAnswerTextBox->setTextColor(sf::Color(180, 64, 16, 200));
	infoAnswerTextBox->setTextSize(24);
	infoAnswerTextBox->setPosition(300, 600);
	answerBox->show();

}

/* Hides all TGUI elements */
void QuizState::hideAllTGuiElements(){

	// Hide answerTextBox elements
	tgui::Label::Ptr labelQuestionTitle = gui->get("labelQuestionTitle");
	labelQuestionTitle->hide();

	tgui::TextBox::Ptr questionBox = gui->get("questionTextbox");
	questionBox->hide();

	tgui::TextBox::Ptr answerBox = gui->get("answerBox");
	answerBox->hide();

	tgui::Label::Ptr labelAnswerTextBox = gui->get("labelAnswerTextBox");
	labelAnswerTextBox->hide();

	tgui::Label::Ptr infoAnswerTextBox = gui->get("infoAnswerTextBox");
	infoAnswerTextBox->hide();

	// Hide multiple choice elements
	tgui::RadioButton::Ptr radioButtonA = gui->get("A");
	radioButtonA->hide();

	tgui::RadioButton::Ptr radioButtonB = gui->get("B");
	radioButtonB->hide();

	tgui::RadioButton::Ptr radioButtonC = gui->get("C");
	radioButtonC->hide();

	tgui::RadioButton::Ptr radioButtonD = gui->get("D");
	radioButtonD->hide();

}

// resets the radio buttons color
void QuizState::resetRadioButton() {

	tgui::RadioButton::Ptr radioButtonA = gui->get("A");
	radioButtonA->setTextColor(sf::Color::White);
	radioButtonA->uncheck();

	tgui::RadioButton::Ptr radioButtonB = gui->get("B");
	radioButtonB->setTextColor(sf::Color::White);
	radioButtonB->uncheck();

	tgui::RadioButton::Ptr radioButtonC = gui->get("C");
	radioButtonC->setTextColor(sf::Color::White);
	radioButtonC->uncheck();

	tgui::RadioButton::Ptr radioButtonD = gui->get("D");
	radioButtonD->setTextColor(sf::Color::White);
	radioButtonD->uncheck();
}

//* changes the text of the quiz question as well as the multiple choice options */
void QuizState::setupMultipleChoiceQuestion(sf::Uint64 questionNumber, sf::String question, sf::String answerA, sf::String answerB, sf::String answerC, sf::String answerD) {

	// Create the username label
	tgui::Label::Ptr labelQuestionTitle(*gui, "labelQuestionTitle");
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
	//tgui::Label::Ptr labelQuestionTitle(*gui, "labelQuestionTitle");
	//labelQuestionTitle->setText("Question: " + std::to_string(quizNumber));
	//labelQuestionTitle->setTextSize(32);
	//labelQuestionTitle->setPosition(70, 70);

	// Where the question is displayed
	//tgui::TextBox::Ptr questionBox(*gui, "questionTextbox");
	//questionBox->setSize(1000, 150);
	//questionBox->setPosition(140, 150);
	//questionBox->setBackgroundColor(sf::Color(50, 50, 50, 100));
	//questionBox->setTextColor(sf::Color(255, 255, 255));
	//questionBox->setBorders(30, 30, 30, 30);
	//questionBox->setBorderColor(sf::Color(50, 50, 50, 100));
	//questionBox->setSize(1000, 250);
	//questionBox->setText(quizQuestion);
	//questionBox->setReadOnly(true);

	// Answer textbox
	tgui::TextBox::Ptr answerBox(*gui, "answerBox");
	answerBox->setSize(480, 10);
	answerBox->setPosition(500, 500);
	answerBox->setBackgroundColor(sf::Color(255, 255, 255, 150));
	answerBox->setTextColor(sf::Color(50, 50, 50));
	answerBox->setBorders(170, 25, 20, 15);
	answerBox->setCallbackId(7);
	answerBox->setBorderColor(sf::Color(255, 255, 255, 150));
	answerBox->setReadOnly(false);

	// Answer:
	tgui::Label::Ptr labelAnswerTextBox(*gui, "labelAnswerTextBox");
	labelAnswerTextBox->setText("Answer:");
	labelAnswerTextBox->setTextColor(sf::Color(50, 50, 50, 150));
	labelAnswerTextBox->setTextSize(34);
	labelAnswerTextBox->setPosition(350, 500);

	// Info Answer label
	tgui::Label::Ptr infoAnswerTextBox(*gui, "infoAnswerTextBox");
	infoAnswerTextBox->setText("*Info: Please enter your answer and click on submit once finished.");
	infoAnswerTextBox->setTextColor(sf::Color(180, 64, 16, 200));
	infoAnswerTextBox->setTextSize(24);
	infoAnswerTextBox->setPosition(300, 600);

}





QuizState::~QuizState() {
	delete gui;
}