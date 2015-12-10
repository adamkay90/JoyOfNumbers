#include "quiz_state.h"

// Constructor
QuizState::QuizState(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	correctAnswer = Selection::A;
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

	// Render the gui on top of everything
	gui->draw();
	return;
}

void QuizState::update(const float dt)
{


}

void QuizState::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			// If the user closes the window
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
			// If the user presses any key
		case sf::Event::KeyPressed:
		{
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

	// Create the username label
	tgui::Label::Ptr labelQuestionTitle(*gui);
	labelQuestionTitle->setText("Question: ");
	labelQuestionTitle->setTextSize(32);
	labelQuestionTitle->setPosition(this->game->window.getSize().x / 2.f - labelQuestionTitle->getSize().x / 2.f, 100);

	tgui::Label::Ptr labelQuestionNumber(*gui, "Question Number");
	labelQuestionNumber->setText("1");
	labelQuestionNumber->setTextSize(32);
	labelQuestionNumber->setPosition(this->game->window.getSize().x / 2.f - labelQuestionTitle->getSize().x / 2.f + labelQuestionTitle->getSize().x + 5, 100);

	tgui::Label::Ptr labelQuestionText(*gui, "Question Text");
	labelQuestionText->setText("What is the binary representation of the decimal number 5?");
	labelQuestionText->setTextSize(28);
	labelQuestionText->setPosition(10, 150);

	tgui::RadioButton::Ptr radioButtonA(*gui, "A");
	radioButtonA->load("TGUI-0.6/widgets/Black.conf");
	radioButtonA->setPosition(this->game->window.getSize().x * (1 / 4.f), 300);
    radioButtonA->setText("101");
	radioButtonA->bindCallback(tgui::RadioButton::Checked);
	radioButtonA->setCallbackId(2);
    radioButtonA->setSize(32, 32);

	tgui::RadioButton::Ptr radioButtonB = gui->copy(radioButtonA, "B");
	radioButtonB->setPosition(this->game->window.getSize().x * (3 / 4.f), 300);
	radioButtonB->setCallbackId(3);
	radioButtonB->setText("011");

	tgui::RadioButton::Ptr radioButtonC = gui->copy(radioButtonA, "C");
	radioButtonC->setPosition(this->game->window.getSize().x * (1 / 4.f), 400);
	radioButtonC->setCallbackId(4);
	radioButtonC->setText("111");

	tgui::RadioButton::Ptr radioButtonD = gui->copy(radioButtonA, "D");
	radioButtonD->setPosition(this->game->window.getSize().x * (3 / 4.f), 400);
	radioButtonD->setCallbackId(5);
	radioButtonD->setText("001");

	// Create the submit button
	tgui::Button::Ptr button(*gui);
	button->load("TGUI-0.6/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(this->game->window.getSize().x * (2 / 3.f) - 130, this->game->window.getSize().y - 70);
	button->setText("Submit");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(1);
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

void QuizState::changeText(std::string questionNumber, std::string question, std::string answerA, std::string answerB, std::string answerC, std::string answerD) {
	tgui::Label::Ptr labelQuestionNumber = gui->get("Question Number");
	labelQuestionNumber->setText(questionNumber);

	tgui::Label::Ptr labelQuestionText = gui->get("Question Text");
	labelQuestionText->setText(question);

	tgui::RadioButton::Ptr radiobuttonA = gui->get("A");
	radiobuttonA->setText(answerA);

	tgui::RadioButton::Ptr radiobuttonB = gui->get("B");
	radiobuttonA->setText(answerB);

	tgui::RadioButton::Ptr radiobuttonC = gui->get("C");
	radiobuttonA->setText(answerC);

	tgui::RadioButton::Ptr radiobuttonD = gui->get("D");
	radiobuttonA->setText(answerD);
}

QuizState::~QuizState() {
	delete gui;
}