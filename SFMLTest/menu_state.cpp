#include <SFML/Graphics.hpp>

#include "menu_state.h"
#include "game_state_editor.h"
#include "game_state.h"
#include "quiz_state.h"

//sf::Sprite nextLogo;
//TODO: Need more Sprites

// Constructor
MenuState::MenuState(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}

// Draws the window
void MenuState::draw(const float dt)
{

	this->game->window.setView(this->view);
	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Blue);


	// Set up the text that displays which quiz it is
	sf::Font font;
	font.loadFromFile("..\\arial.ttf");

	// creating the text
	sf::String Menu = { "Menu" };
	sf::Text text(Menu, font, 60);
	text.setColor(sf::Color::Green);

	// set postion of the text
	text.setPosition(this->game->window.getSize().x / 20, this->game->window.getSize().y / 100);
	this->game->window.draw(text);

	// set up the quiz question
	sf::String question = "What are all the possible values that can be represented using two's compliment and 5 bits?";
	sf::Text text2(question, font, 20);
	text2.setColor(sf::Color::White);
	text2.setPosition(this->game->window.getSize().x / 20, this->game->window.getSize().y / 3);
	this->game->window.draw(text2);

	// option to click for the user (circles as checkbox options)
	sf::CircleShape s1(10.f);
	s1.setFillColor(sf::Color::White);
	s1.setPosition(this->game->window.getSize().x / 10, this->game->window.getSize().y / 2);
	this->game->window.draw(s1);

	sf::CircleShape s2(10.f);
	s2.setFillColor(sf::Color::White);
	s2.setPosition(this->game->window.getSize().x / 10, this->game->window.getSize().y / 2 + 50);
	this->game->window.draw(s2);

	sf::CircleShape s3(10.f);
	s3.setFillColor(sf::Color::White);
	s3.setPosition(this->game->window.getSize().x / 10, this->game->window.getSize().y / 2 + 100);
	this->game->window.draw(s3);

	sf::CircleShape s4(10.f);
	s4.setFillColor(sf::Color::White);
	s4.setPosition(this->game->window.getSize().x / 10, this->game->window.getSize().y / 2 + 150);
	this->game->window.draw(s4);


	// text answer options
	sf::String A = "32";
	sf::Text answerA(A, font, 20);
	answerA.setColor(sf::Color::White);
	answerA.setPosition(this->game->window.getSize().x / 10 + 50, this->game->window.getSize().y / 2);
	this->game->window.draw(answerA);

	sf::String B = "64";
	sf::Text answerB(B, font, 20);
	answerB.setColor(sf::Color::White);
	answerB.setPosition(this->game->window.getSize().x / 10 + 50, this->game->window.getSize().y / 2 + 50);
	this->game->window.draw(answerB);

	sf::String C = "16";
	sf::Text answerC(C, font, 20);
	answerC.setColor(sf::Color::White);
	answerC.setPosition(this->game->window.getSize().x / 10 + 50, this->game->window.getSize().y / 2 + 100);
	this->game->window.draw(answerC);

	sf::String D = "15";
	sf::Text answerD(D, font, 20);
	answerD.setColor(sf::Color::White);
	answerD.setPosition(this->game->window.getSize().x / 10 + 50, this->game->window.getSize().y / 2 + 150);
	this->game->window.draw(answerD);



	// next question selection
	//nextLogo.setScale(.5, .5);
	//nextLogo.setTexture(this->game->texManager.getRef("next"));
	//nextLogo.setOrigin(nextLogo.getTextureRect().width / 2, nextLogo.getTextureRect().height / 2);
	//nextLogo.setPosition(this->game->window.getSize().x - 100, this->game->window.getSize().y - 200);
	//this->game->window.draw(nextLogo);



	//this->game->window.draw(shape);
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
			// If the user resizes the window
		case sf::Event::Resized:
		{
								   // This code wlil change things so images and elements don't stretch when the window is resized
								   // Their size will remain constant, no matter what the window size is
								   this->view.setSize(event.size.width, event.size.height);


								   // Note mapPixelToCoords use! It will map a position's object on the screen to its position in the world.
								   this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
								   this->game->background.setScale(
									   float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
									   float(event.size.height) / float(this->game->background.getTexture()->getSize().y));


								   break;
		}
			// If the user presses any key
		case sf::Event::KeyPressed:
		{
									  // If the key was the Esc key
									  if (event.key.code == sf::Keyboard::Escape) this->game->window.close();

									  // If the key was the Space Bar, load the quiz State
									  else if (event.key.code == sf::Keyboard::Space) this->loadQuiz();
									  break;

		}
		default: break;
		}
	}

	return;
}


// Takes you to the second state, the Editor
void MenuState::loadQuiz()
{
	this->game->pushState(new QuizState(this->game));

	return;
}