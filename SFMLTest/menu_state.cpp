#include "menu_state.h"
#include "client_socket.h"
#include "lesson_state.h"
#include "lesson_state_1.h"
#include "lesson_state_2.h"

void MenuState::draw(const float dt)
{
	this->game->window.setView(this->view);

	// Make the window black
	this->game->window.clear(sf::Color::Black);

	// Render the gui on top of everything
	gui->draw();
	return;
}

void MenuState::update(const float dt)
{

}

void MenuState::handleInput()
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
		// A list item was selected
		if (callback.id == 0) {
			
			for each (bool flag in unlockedMenus) {
				std::cout << flag << " ";
			}
			std::cout << std::endl;

			tgui::ListBox::Ptr listbox = gui->get("List");
			int id = listbox->getSelectedItemId();
			
			tgui::Button::Ptr button = gui->get("Button");
			unlock();
			// Make the button enabled if the menu item can be selected
			if (unlockedMenus.at(id) == true) {
				button->enable();
				button->setTransparency(255);
				button->setTextColor(sf::Color(255, 255, 255, 255));
			}
			else {
				button->disable();
				button->setTransparency(50);
				button->setTextColor(sf::Color(40, 40, 40, 40));
			}
		}
		// The Submit button was clicked
		else if (callback.id == 1)
		{
			tgui::ListBox::Ptr listbox = gui->get("List");
			int id = listbox->getSelectedItemId();

			

			// This is where it'll load either a lesson state or a quiz state
			switch (id) {
			case 0:
				//Natural Numbers
				this->game->pushState(new LessonState(this->game));
				break;

			case 1:
				//Integers
				this->game->pushState(new LessonState1(this->game));
				break;

			case 2:
				//Binary
				this->game->pushState(new LessonState2(this->game));
				break;

			case 3:
				//Quiz
				this->game->pushState(new QuizState(this->game));
				break;
			}
		}
		// The logout button was clicked
		else if (callback.id == 2) {
			this->game->poppedState = true;
			ClientSocket::reset_data();
			this->game->popState();
			return;
		}
	}

	return;
}

MenuState::MenuState(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	MenuState::gui = new tgui::Gui(this->game->window);
	gui->setGlobalFont("media/arial.ttf");
	
	unlockedMenus.resize(10);
	unlockedMenus.at(0) = true;
	for (int i = 1; i < 10; i++){
		unlockedMenus.at(i) = false;
	}
	
	setupGui();
}


void MenuState::setupGui() {

	tgui::Picture::Ptr background(*gui, "background");
	background->load("TGUI-0.6/widgets/2.jpg");
	background->setPosition(0, 0);


	tgui::ListBox::Ptr listBox(*gui, "List");
	listBox->load("TGUI-0.6/widgets/Black.conf");
	listBox->setSize(800, 600);
	listBox->setItemHeight(50);
	listBox->setPosition(240, 50);
	listBox->addItem("Lesson 1: Natural Numbers", 0);
	listBox->addItem("Lesson 2: Integers", 1);
	listBox->addItem("Lesson 3: Binary", 2);
	listBox->addItem("Quiz", 3);


	listBox->bindCallback(tgui::ListBox::ItemSelected);
	listBox->setCallbackId(0);

	// Create the first name label
	tgui::Label::Ptr labelFirstName(*gui);
	labelFirstName->setTextColor(sf::Color::Green);
	labelFirstName->setText(this->game->firstName);
	labelFirstName->setPosition(10, 10);

	// Create the last name label
	tgui::Label::Ptr labelLastName(*gui);
	labelLastName->setTextColor(sf::Color::Green);
	labelLastName->setText(this->game->lastName);
	labelLastName->setPosition(labelFirstName->getPosition().x + labelFirstName->getSize().x + 13, 10);


	// Create the start button
	tgui::Button::Ptr button1(*gui, "Button");
	button1->load("TGUI-0.6/widgets/Black.conf");
	button1->setSize(260, 60);
	button1->setPosition(this->game->window.getSize().x * (3 / 4.f) - 130, this->game->window.getSize().y - 70);
	button1->setText("Start");
	button1->bindCallback(tgui::Button::LeftMouseClicked);
	button1->setCallbackId(1);

	// Create the log out button
	tgui::Button::Ptr button2(*gui);
	button2->load("TGUI-0.6/widgets/Black.conf");
	button2->setSize(160, 40);
	button2->setPosition(this->game->window.getSize().x - button2->getSize().x - 10, 10);
	button2->setText("Logout");
	button2->bindCallback(tgui::Button::LeftMouseClicked);
	button2->setCallbackId(2);
	
	unlock();
	
}

void MenuState::unlockMenu(int menuToUnlock) {
	unlockedMenus.at(menuToUnlock) = true; 
}

void MenuState::unlock(){
	client_information::sections_.clear();
	client_information::quizzes_.clear();

	ClientSocket::lesson_info();
	ClientSocket::quiz_info();



	int counter = -1; 

	for (const sf::Uint64 &section : client_information::sections_){
		if (section != sf::Uint64(0)){
			unlockMenu(++counter);
		}
		else{
			++counter;
		}
	}
	
	for (const sf::Uint64 &quiz : client_information::quizzes_){
		if (quiz != sf::Uint64(0)){
			std::cout << counter << std::endl; 
			unlockMenu(counter++);
		}
		else{
			return;
		}
	}
}

MenuState::~MenuState() {
	delete gui;
}
