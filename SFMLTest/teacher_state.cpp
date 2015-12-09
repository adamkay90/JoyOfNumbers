#include "teacher_state.h"
#include <iostream>



void TeacherState::draw(const float dt)
{
	this->game->window.setView(this->view);

	// Make the window black
	this->game->window.clear(sf::Color::Black);

	//this->game->window.draw(this->game->background);

	float SCALE = 30.f;

	// First we have to render the physics objects
	for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{
		// Iterate through all the dynamic bodies
		if (BodyIterator->GetType() == b2_dynamicBody)
		{
			// If the dynamic body is outside the scope of the screen, delete it
			if (SCALE * BodyIterator->GetPosition().x > game->window.getSize().x + 100 || SCALE * BodyIterator->GetPosition().y > game->window.getSize().y + 100)
			{
				world->DestroyBody(BodyIterator);
			}
			// Otherwise, create a sprite and render it to the screen
			else {
				sf::Sprite Sprite;
				Sprite.setTexture(this->game->texManager.getRef("zero"));
				Sprite.setOrigin(Sprite.getTextureRect().width / 2.f, Sprite.getTextureRect().height / 2.f);
				Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
				this->game->window.draw(Sprite);
			}
		}
	}

	// Render everything

	// Setup the gui and render it on top
	gui->draw();
	return;
}

void TeacherState::update(const float dt)
{
	spawnTimer -= dt;
	if (spawnTimer <= 0) {
		spawnTimer = spawnTime;
	}

	world->Step(1 / 60.f, 8, 3);

	// This makes Bob Ross's face flip between two angles
	/*
	faceTimer -= dt;
	if (faceTimer <= 0) {
	if (face.getRotation() == angle1) {
	face.setRotation(angle2);
	}
	else if (face.getRotation() == angle2) {
	face.setRotation(angle1);
	}
	faceTimer = flipTime;
	}
	*/

	// This makes Bob Ross's face spin
}
void TeacherState::onRossClick(){
	std::cout << "HELLO" << std::endl;//needs to be an html call
}
void TeacherState::onLabelClick(){
	
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
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();

			// If the key was the Space Bar, load the game State
			else if (event.key.code == sf::Keyboard::Space) this->loadMenu();
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
			gui->get("Potato")->setSize(100, 100);
			//picture_ptr->setSize(100, 100);
			onRossClick();
		}
		else if (callback.id==2){
			label_ptr->setText("I'M NOT ROSS. try again");
		}
	}

	return;
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




	tgui::Picture::Ptr picture(*gui, "Potato");
	picture->load("TGUI-0.6/widgets/Ross_Face.png");
	picture->setSize(400, 400);
	picture->setPosition((this->game->window.getSize().x)* (1 / 2.f), (this->game->window.getSize().y - 400)*(1 / 2.f));
	picture->bindCallback(tgui::Picture::LeftMouseClicked);
	picture->setCallbackId(1);
	picture_ptr = picture;


	tgui::Label::Ptr label(*gui);
	label->setSize(400, 100);
	label->setPosition((this->game->window.getSize().x)* (1 / 2.f), (this->game->window.getSize().y + 400)*(1 / 2.f));
	label->setTextColor(sf::Color(100, 0, 160, 250));
	label->setText("Click On Ross to get HTML");
	label->bindCallback(tgui::Label::LeftMouseClicked);
	label->setCallbackId(2);
	label_ptr = label;

	
	tgui::Button::Ptr submit_button(*gui);
	submit_button->load("TGUI-0.6/widgets/Black.conf");
	submit_button->setSize(30, 60);
	submit_button->setPosition(490, this->game->window.getSize().y - 170);
	submit_button->setText("Submit");
	submit_button->bindCallback(tgui::Button::LeftMouseClicked);
	submit_button->setCallbackId(3);



	tgui::EditBox::Ptr user_name_text(*gui, "username");
	user_name_text->load("TGUI-0.6/widgets/White.conf");
	user_name_text->setSize(400, 40);
	user_name_text->setPosition(200, this->game->window.getSize().y - 670);

	tgui::EditBox::Ptr first_name_text(*gui, "firstname");
	first_name_text->load("TGUI-0.6/widgets/White.conf");
	first_name_text->setSize(400, 40);
	first_name_text->setPosition(200, this->game->window.getSize().y - 570);

	tgui::EditBox::Ptr last_name_text(*gui, "lastname");
	last_name_text->load("TGUI-0.6/widgets/White.conf");
	last_name_text->setSize(400, 40);
	last_name_text->setPosition(200, this->game->window.getSize().y - 470);

	tgui::EditBox::Ptr password_text(*gui, "password");
	password_text->load("TGUI-0.6/widgets/White.conf");
	password_text->setSize(400, 40);
	password_text->setPosition(200, this->game->window.getSize().y - 370);

	tgui::Checkbox::Ptr instructor_checkbox(*gui, "instructor");
	instructor_checkbox->load("TGUI-0.6/widgets/White.conf");
	instructor_checkbox->setPosition(200, this->game->window.getSize().y - 270);

	tgui::RadioButton::Ptr radio_register(*gui, "radio_register");
	radio_register->load("TGUI-0.6/widgets/White.conf");
	radio_register->setPosition(350, this->game->window.getSize().y-170);

	tgui::RadioButton::Ptr radio_delete(*gui, "radio_delete");
	radio_delete->load("TGUI-0.6/widgets/White.conf");
	radio_delete->setPosition(350, this->game->window.getSize().y - 150);

	tgui::RadioButton::Ptr radio_rename(*gui, "radio_rename");
	radio_rename->load("TGUI-0.6/widgets/White.conf");
	radio_rename->setPosition(350, this->game->window.getSize().y - 130);


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
	*/
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
