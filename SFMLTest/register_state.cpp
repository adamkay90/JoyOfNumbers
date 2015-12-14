#include "register_state.h"
#include "client_socket.h"
#include "teacher_state.h"
#include "menu_state.h"
#include "error_state.h"
void RegisterState::draw(const float dt)
{
	this->game->window.setView(this->view);

	// Make the window black
	this->game->window.clear(sf::Color::Black);

	// Render the gui on top of everything
	gui->draw();
	return;
}

void RegisterState::update(const float dt)
{

}

void RegisterState::handleInput()
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
			// For the register button
			std::cout << "Register button clicked!" << std::endl;
			getDataFromTextBoxes();
			if (game->username.empty() || game->firstName.empty() || game->lastName.empty() || game->password.empty()){
				tgui::Label::Ptr output = static_cast<tgui::Label::Ptr>(gui->get("output"));
				//output->setTextColor(sf::Color::Black);
				output->setText("no blank fields allowed");
			}
			else if (ClientSocket::register_user(game->username, game->firstName, game->lastName, game->password, game->isTeacher) == sf::Uint64(2)){
				if (game->isTeacher){
					this->game->pushState(new TeacherState(this->game));
				}
				else{
					this->game->pushState(new MenuState(this->game));
				}
			}
			else{
				this->game->pushState(new ErrorState(this->game, "Registration failed"));
			}
		}
		else if (callback.id == 2) {
			// For the back button
			this->game->poppedState = true;
			this->game->popState();
			return;

		}
	}

	return;
}

RegisterState::RegisterState(Game* game)
{
	this->game = game;
	
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	RegisterState::gui = new tgui::Gui(this->game->window);
	gui->setGlobalFont("media/arial.ttf");

	SetupGui();

}




// Takes you to the second state, the Editor
void RegisterState::loadMenu()
{
	// This should make a new class for loading the menu

	// this->game->pushState(new QuizState(this->game));

	return;
}

void RegisterState::getDataFromTextBoxes() {
	tgui::EditBox::Ptr editBoxUsername = gui->get("Username");
	tgui::EditBox::Ptr editBoxPassword = gui->get("Password");
	tgui::EditBox::Ptr editBoxFirstName = gui->get("First Name");
	tgui::EditBox::Ptr editBoxLastName = gui->get("Last Name");

	tgui::Checkbox::Ptr checkboxTeacher = gui->get("Teacher");

	this->game->username = editBoxUsername->getText();
	this->game->password = editBoxPassword->getText();
	this->game->firstName = editBoxFirstName->getText();
	this->game->lastName = editBoxLastName->getText();

	this->game->isTeacher = checkboxTeacher->isChecked();
}

void RegisterState::SetupGui() {
	tgui::Picture::Ptr background(*gui, "background");
	background->load("TGUI-0.6/widgets/4.jpg");
	background->setPosition(0, 0);

	// Create the username label
	tgui::Label::Ptr labelRegisterNew(*gui);
	//labelRegisterNew->setTextColor(sf::Color::Black);
	labelRegisterNew->setText("Register New User");
	labelRegisterNew->setTextSize(32);
	labelRegisterNew->setPosition(this->game->window.getSize().x / 2.f - labelRegisterNew->getSize().x / 2.f, 100);


	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername(*gui, "Username");
	editBoxUsername->load("TGUI-0.6/widgets/White.conf");
	editBoxUsername->setSize(400, 40);
	editBoxUsername->setPosition(this->game->window.getSize().x / 2.f - editBoxUsername->getSize().x / 2, 200);
	editBoxUsername->setText(this->game->username);

	// Create the password edit box (we will copy the previously created edit box)
	tgui::EditBox::Ptr editBoxPassword = gui->copy(editBoxUsername, "Password");
	editBoxPassword->setPosition(this->game->window.getSize().x / 2.f - editBoxPassword->getSize().x / 2, 300);
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setText(this->game->password);

	// Create the edit box for the first name
	tgui::EditBox::Ptr editBoxFirstName = gui->copy(editBoxUsername, "First Name");
	editBoxFirstName->setText("");
	editBoxFirstName->setPosition(this->game->window.getSize().x / 2.f - editBoxFirstName->getSize().x / 2, 400);

	// Create the edit box for the last name
	tgui::EditBox::Ptr editBoxLastName = gui->copy(editBoxUsername, "Last Name");
	editBoxLastName->setText("");
	editBoxLastName->setPosition(this->game->window.getSize().x / 2.f - editBoxLastName->getSize().x / 2, 500);

	// Create the username label
	tgui::Label::Ptr labelUsername(*gui);
	//labelUsername->setTextColor(sf::Color::Magenta);
	labelUsername->setText("Username:");
	labelUsername->setPosition(editBoxUsername->getSize().x - labelUsername->getSize().x - 10, editBoxUsername->getPosition().y);

	// Create the password label
	tgui::Label::Ptr labelPassword(*gui);
	//labelPassword->setTextColor(sf::Color::Magenta);
	labelPassword->setText("Password:");
	labelPassword->setPosition(editBoxPassword->getSize().x - labelPassword->getSize().x - 10, editBoxPassword->getPosition().y);

	// Create the first name label
	tgui::Label::Ptr labelFirstName(*gui);
	//labelFirstName->setTextColor(sf::Color::Magenta);
	labelFirstName->setText("First Name:");
	labelFirstName->setPosition(editBoxFirstName->getSize().x - labelFirstName->getSize().x - 10, editBoxFirstName->getPosition().y);

	// Create the last name label
	tgui::Label::Ptr labelLastName(*gui);
	//labelLastName->setTextColor(sf::Color::Magenta);
	labelLastName->setText("Last Name:");
	labelLastName->setPosition(editBoxLastName->getSize().x - labelLastName->getSize().x - 10, editBoxLastName->getPosition().y);

	tgui::Checkbox::Ptr checkboxTeacher(*gui, "Teacher");
	checkboxTeacher->load("TGUI-0.6/widgets/White.conf");
	checkboxTeacher->setText("Teacher?");
	checkboxTeacher->setSize(32, 32);
	checkboxTeacher->setPosition(this->game->window.getSize().x / 2.f, this->game->window.getSize().y - 140);

	// Create the register button
	tgui::Button::Ptr button(*gui);
	button->load("TGUI-0.6/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(this->game->window.getSize().x * (1 / 3.f) - 130, this->game->window.getSize().y - 70);
	button->setText("Register");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(1);

	// Create the back button
	tgui::Button::Ptr button2(*gui);
	button2->load("TGUI-0.6/widgets/Black.conf");
	button2->setSize(260, 60);
	button2->setPosition(this->game->window.getSize().x * (2 / 3.f) - 130, this->game->window.getSize().y - 70);
	button2->setText("Back");
	button2->bindCallback(tgui::Button::LeftMouseClicked);
	button2->setCallbackId(2);

	tgui::Label::Ptr output(*gui, "output");
	output->setText("");
	output->setPosition(250, 600);

}

RegisterState::~RegisterState() {
	delete gui;
}