#include "teacher_state.h"
#include "client_socket.h"
#include "menu_state.h"
#include <iostream>
#include "client_socket.h"
#include "error_state.h"

void TeacherState::draw(const float dt)
{
	this->game->window.setView(this->view);

	// Make the window black
	this->game->window.clear(sf::Color::Black);

	// Setup the gui and render it on top
	gui->draw();
	return;
}

void TeacherState::update(const float dt)
{

}

void TeacherState::on_ross_click(){
	//needs to be an html call
	if (ClientSocket::html() != 0){
		tgui::Label::Ptr output = static_cast<tgui::Label::Ptr>(gui->get("output_label"));
		output->setText("HTML created successfully");
	}
	else{
		//fail
		this->game->pushState(new ErrorState(this->game, "HTML failed"));
		return;
	}
	tgui::Picture::Ptr picture = static_cast<tgui::Picture::Ptr>(gui->get("ross"));
	picture->load("TGUI-0.6/widgets/potato.png");
	picture->setSize(497, 541);
	picture->setPosition((this->game->window.getSize().x)* (1 / 2.f), (this->game->window.getSize().y - 800)*(1 / 2.f));
}
void TeacherState::on_submit_click(){
	//std::cout << "potato" << std::endl;
	if ((static_cast<tgui::RadioButton::Ptr>(gui->get("radio_register")))->isChecked()){
		tgui::EditBox::Ptr user_name = static_cast<tgui::EditBox::Ptr>(gui->get("username"));

		tgui::EditBox::Ptr first_name = static_cast<tgui::EditBox::Ptr>(gui->get("firstname"));

		tgui::EditBox::Ptr last_name = static_cast<tgui::EditBox::Ptr>(gui->get("lastname"));

		tgui::EditBox::Ptr password = static_cast<tgui::EditBox::Ptr>(gui->get("password"));

		tgui::Checkbox::Ptr inst = static_cast<tgui::Checkbox::Ptr>(gui->get("instructor"));
		if (user_name->getText().isEmpty()|| first_name->getText().isEmpty() || last_name->getText().isEmpty() ||password->getText().isEmpty()){

			tgui::Label::Ptr output = static_cast<tgui::Label::Ptr>(gui->get("output_label"));
			output->setText("No blank fields allowed");
			return;
		}
		if (ClientSocket::add_user(user_name->getText(), first_name->getText(), last_name->getText(), password->getText(), inst->isChecked()) != 0){
			//success
			tgui::Label::Ptr output = static_cast<tgui::Label::Ptr>(gui->get("output_label"));
			output->setText("User succesfully registered");
			return;
		}
		else{
			//fail
			this->game->pushState(new ErrorState(this->game, "Registration failed"));
			return;
		}
		

	}
	else if ((static_cast<tgui::RadioButton::Ptr>(gui->get("radio_remove")))->isChecked()){
		tgui::EditBox::Ptr user_name = static_cast<tgui::EditBox::Ptr>(gui->get("username"));
		
		if (user_name->getText().isEmpty()){
			tgui::Label::Ptr output = static_cast<tgui::Label::Ptr>(gui->get("output_label"));
			output->setText("No blank fields allowed");
			return;
		}
		if (ClientSocket::remove_user(user_name->getText()) != 0){
			//success
			tgui::Label::Ptr output = static_cast<tgui::Label::Ptr>(gui->get("output_label"));
			output->setText("User succesfully deleted");
			return;
		}
		else{
			//fail
			this->game->pushState(new ErrorState(this->game, "Deletion failed"));
			return;
		}
	}
	else if ((static_cast<tgui::RadioButton::Ptr>(gui->get("radio_rename")))->isChecked()){
		tgui::EditBox::Ptr user_name = static_cast<tgui::EditBox::Ptr>(gui->get("username"));

		tgui::EditBox::Ptr first_name = static_cast<tgui::EditBox::Ptr>(gui->get("firstname"));

		tgui::EditBox::Ptr last_name = static_cast<tgui::EditBox::Ptr>(gui->get("lastname"));
		
		if (user_name->getText().isEmpty() || first_name->getText().isEmpty() || last_name->getText().isEmpty()){
			tgui::Label::Ptr output = static_cast<tgui::Label::Ptr>(gui->get("output_label"));
			output->setText("No blank fields allowed");
			return;
		}
		if (ClientSocket::rename_user(user_name->getText(), first_name->getText(), last_name->getText()) != 0){
			//success
			tgui::Label::Ptr output = static_cast<tgui::Label::Ptr>(gui->get("output_label"));
			output->setText("Updated first and last name successfully");
			return;
		}
		else{
			//fail
			this->game->pushState(new ErrorState(this->game, "Update failed"));
			return;
		}
	}
	else{
		//dafuq?
	}
}
void TeacherState::on_register_select(){
	tgui::EditBox::Ptr first_name = static_cast<tgui::EditBox::Ptr>(gui->get("firstname"));
	first_name->setText("");
	first_name->load("TGUI-0.6/widgets/White.conf");
	first_name->setSize(400, 40);
	first_name->enable();

	tgui::EditBox::Ptr last_name = static_cast<tgui::EditBox::Ptr>(gui->get("lastname"));
	last_name->setText("");
	last_name->load("TGUI-0.6/widgets/White.conf");
	last_name->setSize(400, 40);
	last_name->enable();

	tgui::EditBox::Ptr password = static_cast<tgui::EditBox::Ptr>(gui->get("password"));
	password->setText("");
	password->load("TGUI-0.6/widgets/White.conf");
	password->setSize(400, 40);
	password->enable();

	tgui::Checkbox::Ptr inst = static_cast<tgui::Checkbox::Ptr>(gui->get("instructor"));
	inst->uncheck();
	inst->load("TGUI-0.6/widgets/White.conf");
	inst->enable();

	tgui::RadioButton::Ptr remove = static_cast<tgui::Checkbox::Ptr>(gui->get("radio_remove"));
	remove->uncheck();

	tgui::RadioButton::Ptr rename = static_cast<tgui::Checkbox::Ptr>(gui->get("radio_rename"));
	rename->uncheck();

}
void TeacherState::on_remove_select(){
	tgui::EditBox::Ptr first_name = static_cast<tgui::EditBox::Ptr>(gui->get("firstname"));
	first_name->setText("");
	first_name->load("TGUI-0.6/widgets/Black.conf");
	first_name->setSize(400, 40);
	first_name->disable();

	tgui::EditBox::Ptr last_name = static_cast<tgui::EditBox::Ptr>(gui->get("lastname"));
	last_name->setText("");
	last_name->load("TGUI-0.6/widgets/Black.conf");
	last_name ->setSize(400, 40);
	last_name->disable();

	tgui::EditBox::Ptr password = static_cast<tgui::EditBox::Ptr>(gui->get("password"));
	password->setText("");
	password->load("TGUI-0.6/widgets/Black.conf");
	password->setSize(400, 40);
	password->disable();
	
	tgui::Checkbox::Ptr inst = static_cast<tgui::Checkbox::Ptr>(gui->get("instructor"));
	inst->uncheck();
	inst->load("TGUI-0.6/widgets/Black.conf");
	inst->setSize(20, 20);
	inst->disable();


	tgui::RadioButton::Ptr register_ = static_cast<tgui::Checkbox::Ptr>(gui->get("radio_register"));
	register_->uncheck();

	tgui::RadioButton::Ptr rename = static_cast<tgui::Checkbox::Ptr>(gui->get("radio_rename"));
	rename->uncheck();
}
void TeacherState::on_rename_select(){
	tgui::EditBox::Ptr first_name = static_cast<tgui::EditBox::Ptr>(gui->get("firstname"));
	first_name->setText("");
	first_name->load("TGUI-0.6/widgets/White.conf");
	first_name->setSize(400, 40);
	first_name->enable();

	tgui::EditBox::Ptr last_name = static_cast<tgui::EditBox::Ptr>(gui->get("lastname"));
	last_name->setText("");
	last_name->load("TGUI-0.6/widgets/White.conf");
	last_name->setSize(400, 40);
	last_name->enable();

	tgui::EditBox::Ptr password = static_cast<tgui::EditBox::Ptr>(gui->get("password"));
	password->setText("");
	password->load("TGUI-0.6/widgets/Black.conf");
	password->setSize(400, 40);
	password->disable();

	tgui::Checkbox::Ptr inst = static_cast<tgui::Checkbox::Ptr>(gui->get("instructor"));
	inst->uncheck();
	inst->load("TGUI-0.6/widgets/Black.conf");
	inst->setSize(20, 20);
	inst->disable();


	tgui::RadioButton::Ptr remove = static_cast<tgui::Checkbox::Ptr>(gui->get("radio_remove"));
	remove->uncheck();

	tgui::RadioButton::Ptr register_ = static_cast<tgui::Checkbox::Ptr>(gui->get("radio_register"));
	register_->uncheck();
}
void TeacherState::handleInput()
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
			if (event.key.code == sf::Keyboard::Escape) {
				this->game->window.close();
				this->game->stopLooping = true;
				return;
			}

		}
		}

		gui->handleEvent(event);
	}

	// Handle the gui callbacks
	tgui::Callback callback;

	while (gui->pollCallback(callback))
	{
		// Make sure tha callback comes from the button
		if (callback.id == 1)
		{
			tgui::Label::Ptr label = static_cast<tgui::Label::Ptr>(gui->get("label"));
			label->setText("HTML acquired");
			on_ross_click();
		}
		else if (callback.id==2){
			
			tgui::Label::Ptr label = static_cast<tgui::Label::Ptr>(gui->get("label"));
			label->setText("I'M NOT ROSS. try again");
		}
		else if (callback.id == 3){
			//submit button
			on_submit_click();
		}
		else if (callback.id == 4){
			//register
			on_register_select();
		}
		else if (callback.id == 5){
			//remove
			on_remove_select();
		}
		else if (callback.id == 6){
			//rename
			on_rename_select();
		}
	}

	return;
}

// Takes you to the second state, the Editor
void TeacherState::loadMenu()
{
	// This should make a new class for loading the menu

	//this->game->pushState(new QuizState(this->game));

	return;
}

void TeacherState::SetupGui() {

	tgui::Picture::Ptr background(*gui, "background");
	background->load("TGUI-0.6/widgets/3.jpg");
	background->setPosition(0, 0);


	tgui::Picture::Ptr picture(*gui, "ross");
	picture->load("TGUI-0.6/widgets/Ross_Face.png");
	picture->setSize(400, 400);
	picture->setPosition((this->game->window.getSize().x)* (1 / 2.f), (this->game->window.getSize().y - 400)*(1 / 2.f));
	picture->bindCallback(tgui::Picture::LeftMouseClicked);
	picture->setCallbackId(1);


	tgui::Label::Ptr label(*gui, "label");
	label->setSize(400, 100);
	label->setPosition((this->game->window.getSize().x)* (1 / 2.f), (this->game->window.getSize().y + 400)*(1 / 2.f));
	label->setTextColor(sf::Color(100, 0, 160, 250));
	label->setText("Click On Ross to get HTML");
	label->bindCallback(tgui::Label::LeftMouseClicked);
	label->setCallbackId(2);

	
	tgui::Button::Ptr submit_button(*gui, "submit");
	submit_button->load("TGUI-0.6/widgets/Black.conf");
	submit_button->setSize(30, 60);
	submit_button->setPosition(250, this->game->window.getSize().y - 250);
	submit_button->setText("Submit");
	submit_button->bindCallback(tgui::Button::LeftMouseClicked);
	submit_button->setCallbackId(3);



	tgui::EditBox::Ptr user_name_text(*gui, "username");
	user_name_text->load("TGUI-0.6/widgets/White.conf");
	user_name_text->setSize(400, 40);
	user_name_text->setPosition(200, this->game->window.getSize().y - 770);

	tgui::EditBox::Ptr first_name_text(*gui, "firstname");
	first_name_text->load("TGUI-0.6/widgets/White.conf");
	first_name_text->setSize(400, 40);
	first_name_text->setPosition(200, this->game->window.getSize().y - 670);

	tgui::EditBox::Ptr last_name_text(*gui, "lastname");
	last_name_text->load("TGUI-0.6/widgets/White.conf");
	last_name_text->setSize(400, 40);
	last_name_text->setPosition(200, this->game->window.getSize().y - 570);

	tgui::EditBox::Ptr password_text(*gui, "password");
	password_text->load("TGUI-0.6/widgets/White.conf");
	password_text->setSize(400, 40);
	password_text->setPosition(200, this->game->window.getSize().y - 470);

	tgui::Checkbox::Ptr instructor_checkbox(*gui, "instructor");
	instructor_checkbox->load("TGUI-0.6/widgets/White.conf");
	instructor_checkbox->setPosition(200, this->game->window.getSize().y - 370);

	tgui::RadioButton::Ptr radio_register(*gui, "radio_register");
	radio_register->load("TGUI-0.6/widgets/White.conf");
	radio_register->setPosition(200, this->game->window.getSize().y-270);
	radio_register->check();
	radio_register->bindCallback(tgui::RadioButton::Checked);
	radio_register->setCallbackId(4);

	tgui::RadioButton::Ptr radio_remove(*gui, "radio_remove");
	radio_remove->load("TGUI-0.6/widgets/White.conf");
	radio_remove->setPosition(200, this->game->window.getSize().y - 230);
	radio_remove->bindCallback(tgui::RadioButton::Checked);
	radio_remove->setCallbackId(5);

	tgui::RadioButton::Ptr radio_rename(*gui, "radio_rename");
	radio_rename->load("TGUI-0.6/widgets/White.conf");
	radio_rename->setPosition(200, this->game->window.getSize().y - 190);
	radio_rename->bindCallback(tgui::RadioButton::Checked);
	radio_rename->setCallbackId(6);

	tgui::Label::Ptr user_label(*gui, "user_label");
	user_label->setSize(150, 40);
	user_label->setPosition(30, this->game->window.getSize().y - 770);
	user_label->setText("Username");

	tgui::Label::Ptr first_label(*gui, "first_label");
	first_label->setSize(150, 40);
	first_label->setPosition(30, this->game->window.getSize().y - 670);
	first_label->setText("First name");

	tgui::Label::Ptr last_label(*gui, "last_label");
	last_label->setSize(150, 40);
	last_label->setPosition(30, this->game->window.getSize().y - 570);
	last_label->setText("Last name");

	tgui::Label::Ptr pass_label(*gui, "pass_label");
	pass_label->setSize(150, 40);
	pass_label->setPosition(30, this->game->window.getSize().y - 470);
	pass_label->setText("Password");

	tgui::Label::Ptr instructor_label(*gui, "instructor_label");
	instructor_label->setSize(150, 40);
	instructor_label->setPosition(30, this->game->window.getSize().y - 370);
	instructor_label->setText("Instructor");

	tgui::Label::Ptr register_label(*gui, "register_label");
	register_label->setSize(150, 40);
	register_label->setPosition(30, this->game->window.getSize().y - 270);
	register_label->setText("Register");

	tgui::Label::Ptr remove_label(*gui, "remove_label");
	remove_label->setSize(150, 40);
	remove_label->setPosition(30, this->game->window.getSize().y - 230);
	remove_label->setText("Remove");

	tgui::Label::Ptr rename_label(*gui, "rename_label");
	rename_label->setSize(150, 40);
	rename_label->setPosition(30, this->game->window.getSize().y - 190);
	rename_label->setText("Rename");

	tgui::Label::Ptr output_label(*gui, "output_label");
	output_label->setSize(800, 40);
	output_label->setPosition(30, this->game->window.getSize().y - 140);
}
TeacherState::TeacherState(Game* game)
{

	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	TeacherState::gui = new tgui::Gui(this->game->window);
	gui->setGlobalFont("media/arial.ttf");
	
	SetupGui();

	//gravity = new b2Vec2(0.f, 9.8f);
	//world = new b2World(*gravity);

	//CreateGround(*world, 400.f, 500.f);

}


TeacherState::~TeacherState()
{
	delete gravity;
	delete world;
	delete gui;
}
