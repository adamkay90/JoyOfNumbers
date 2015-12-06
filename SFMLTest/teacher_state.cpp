#include "teacher_state.h"
#include <iostream>



void TeacherState::draw(const float dt)
{
}

void TeacherState::update(const float dt)
{

}

void TeacherState::handleInput()
{
}
void TeacherState::CreateBox(b2World& World, int MouseX, int MouseY)
{
	float SCALE = 30.f;

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

void TeacherState::CreateGround(b2World& World, float X, float Y)
{
	float SCALE = 30.f;

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}


// Takes you to the second state, the Editor
void TeacherState::loadMenu()
{
	// This should make a new class for loading the menu

	//this->game->pushState(new QuizState(this->game));

	return;
}

void TeacherState::SetupGui() {

	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername(*gui, "Username");
	editBoxUsername->load("TGUI-0.6/widgets/White.conf");
	editBoxUsername->setSize(400, 40);
	editBoxUsername->setPosition(this->game->window.getSize().x / 2.f - editBoxUsername->getSize().x / 2, this->game->window.getSize().y - 200);

	// Create the password edit box (we will copy the previously created edit box)
	tgui::EditBox::Ptr editBoxPassword = gui->copy(editBoxUsername, "Password");
	editBoxPassword->setPosition(this->game->window.getSize().x / 2.f - editBoxPassword->getSize().x / 2, this->game->window.getSize().y - 150);
	editBoxPassword->setPasswordCharacter('*');

	// Create the username label
	tgui::Label::Ptr labelUsername(*gui);
	labelUsername->setText("Username:");
	labelUsername->setPosition(editBoxUsername->getPosition().x - labelUsername->getSize().x - 10, editBoxUsername->getPosition().y);

	// Create the password label
	tgui::Label::Ptr labelPassword(*gui);
	labelPassword->setText("Password:");
	labelPassword->setPosition(editBoxPassword->getPosition().x - labelPassword->getSize().x - 10, editBoxPassword->getPosition().y);

	// Create the login button
	tgui::Button::Ptr button(*gui);
	button->load("TGUI-0.6/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(this->game->window.getSize().x * (1 / 3.f) - 130, this->game->window.getSize().y - 70);
	button->setText("Login");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(1);

	// Create the register button
	tgui::Button::Ptr button2(*gui);
	button2->load("TGUI-0.6/widgets/Black.conf");
	button2->setSize(260, 60);
	button2->setPosition(this->game->window.getSize().x * (2 / 3.f) - 130, this->game->window.getSize().y - 70);
	button2->setText("Register");
	button2->bindCallback(tgui::Button::LeftMouseClicked);
	button2->setCallbackId(2);
}
TeacherState::TeacherState(Game* game)
{

	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
	/*
	logo.setTexture(this->game->texManager.getRef("Logo"));
	logo.setOrigin(logo.getTextureRect().width / 2, logo.getTextureRect().height / 2);
	logo.setPosition(this->game->window.getSize().x / 2, 150);

	if (!background.openFromFile("media/Interlude.ogg")) {

	}
	background.play();

	face.setTexture(this->game->texManager.getRef("Ross_Face"));
	face.setScale(sf::Vector2f(0.5, 0.5));
	face.setOrigin(face.getTextureRect().width / 2, face.getTextureRect().height / 2);
	face.setPosition(this->game->window.getSize().x / 2, this->game->window.getSize().y / 2);

	face.setRotation(angle1);

	faceTimer = flipTime;
	spawnTime = 0.2f;
	spawnTimer = spawnTime;

	TeacherState::gui = new tgui::Gui(this->game->window);
	gui->setGlobalFont("media/arial.ttf");
	*/
	SetupGui();

	gravity = new b2Vec2(0.f, 9.8f);
	world = new b2World(*gravity);

	CreateGround(*world, 400.f, 500.f);

}


TeacherState::~TeacherState()
{
	delete gravity;
	delete world;
	delete gui;
}
