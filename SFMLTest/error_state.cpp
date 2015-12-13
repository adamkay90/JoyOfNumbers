#include "error_state.h"
#include "game_state_login.h"
#include "client_socket.h"
#include "teacher_state.h"
#include "menu_state.h"

void ErrorState::draw(const float dt)
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
	this->game->window.draw(logo);
	this->game->window.draw(face);

	// Setup the gui and render it on top
	gui->draw();
	return;
}

void ErrorState::update(const float dt)
{

	spawnTimer -= dt;
	if (spawnTimer <= 0) {
		ErrorState::CreateBox(*world, this->game->window.getSize().x / 2, 0);
		spawnTimer = spawnTime;
	}

	world->Step(1 / 60.f, 8, 3);

	// This makes Bob Ross's face spin
	face.setRotation(face.getRotation() + spinSpeed * dt);

}

void ErrorState::handleInput()
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

	while (gui->pollCallback(callback))
	{
		// Make sure tha callback comes from the button
		if (callback.id == 1)
		{
			return_state();
			//this->game->poppedState = true;
			//this->game->popState();
			return;
		}
	}

	return;
}

void ErrorState::return_state(){
	this->game->poppedState = true;
	this->game->popState();
}

ErrorState::ErrorState(Game* game, std::string error_message)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	logo.setTexture(this->game->texManager.getRef("Logo"));
	logo.setOrigin(logo.getTextureRect().width / 2, logo.getTextureRect().height / 2);
	logo.setPosition(this->game->window.getSize().x / 2, 150);
	/*
	logo1.setTexture(this->game->texManager.getRef("HappyLittleAccidents"));
	//logo1.setTexture(this->game->texManager.getRef("Logo"));
	logo1.setOrigin(logo1.getTextureRect().width / 2, logo1.getTextureRect().height / 2);
	logo1.setPosition(this->game->window.getSize().x / 2, 150);
	
	*/
	
	face.setTexture(this->game->texManager.getRef("Ross_Face"));
	face.setScale(sf::Vector2f(0.5, 0.5));
	face.setOrigin(face.getTextureRect().width / 2, face.getTextureRect().height / 2);
	face.setPosition(this->game->window.getSize().x / 2, this->game->window.getSize().y / 2);

	face.setRotation(angle1);

	faceTimer = flipTime;
	spawnTime = 0.2f;
	spawnTimer = spawnTime;

	ErrorState::gui = new tgui::Gui(this->game->window);
	gui->setGlobalFont("media/arial.ttf");

	SetupGui(error_message);

	gravity = new b2Vec2(0.f, 9.8f);
	world = new b2World(*gravity);

	CreateGround(*world, 400.f, 500.f);
}


void ErrorState::CreateBox(b2World& World, int MouseX, int MouseY)
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

void ErrorState::CreateGround(b2World& World, float X, float Y)
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



void ErrorState::SetupGui(std::string error_message) {

	tgui::Picture::Ptr new_logo(*gui, "logo1");
	new_logo->load("TGUI-0.6/widgets/HappyLittleAccidents.png");
	new_logo->setPosition(500, 30);

	tgui::Label::Ptr generic_error(*gui, "generic_error");
	//We don't make mistakes, just happy little accidents.
	generic_error->load("TGUI-0.6/widgets/Black.conf");
	generic_error->setSize(400, 100);
	generic_error->setPosition(400, 500);
	generic_error->setText("We don't make mistakes, just \nhappy little accidents.");

	tgui::Label::Ptr error(*gui, "error");
	//We don't make mistakes, just happy little accidents.
	error->load("TGUI-0.6/widgets/Black.conf");
	error->setSize(400, 100);
	error->setPosition(400, 570);
	error->setText(error_message);

	tgui::Button::Ptr acknowledge(*gui, "acknowledge");
	acknowledge->load("TGUI-0.6/widgets/Black.conf");
	acknowledge->setSize(260, 60);
	acknowledge->setPosition(this->game->window.getSize().x * (2 / 3.f) - 130, this->game->window.getSize().y - 170);
	acknowledge->setText("I HAVE SEEN THE LIGHT");
	acknowledge->bindCallback(tgui::Button::LeftMouseClicked);
	acknowledge->setCallbackId(1);
}

ErrorState::~ErrorState() {
	delete gravity;
	delete world;
	delete gui;
}

