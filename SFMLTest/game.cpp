#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.h"
#include "game_state.h"


// Pushes a new state onto the state stack
void Game::pushState(GameState* state) {
	this->states.push(state);
	return;
}

// Pops a state off the state stack
void Game::popState() {
	delete this->states.top();
	this->states.pop();

	return;
}

// Changes the current state. 
void Game::changeState(GameState* state) {
	if (!this->states.empty()) {
		popState();
	}
	pushState(state);

	return;
}


GameState* Game::peekState() {
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

void Game::loadTextures()
{
	texManager.loadTexture("background", "media/Grey.png");
	texManager.loadTexture("Logo", "media/Logo.png");
	texManager.loadTexture("next", "media/next.png");
	texManager.loadTexture("Ross_Face", "media/Ross_Face.png");
	texManager.loadTexture("one", "media/one.png");
	texManager.loadTexture("zero", "media/zero.png");
	texManager.loadTexture("next", "media/next.png");
	texManager.loadTexture("text_bubble", "media/text_bubble.png");
	texManager.loadTexture("Ross_Strip", "media/Ross_Strip.png");
}

void Game::gameLoop() {
	sf::Clock clock;

	// Main update loop
	while (this->window.isOpen()) {

		// Get the time since the last update
		sf::Time elapsed = clock.restart();
		float deltaTime = elapsed.asSeconds();

		// If there's no state currently, skip
		if (peekState() == nullptr) continue;

		// If there is a state, check for input, update the state,
		// Clear the window, and draw

		if (poppedState) {
			poppedState = false;
			continue;
		}
		peekState()->handleInput();
		if (poppedState) {
			poppedState = false;
			continue;
		}
		peekState()->update(deltaTime);
		if (poppedState) {
			poppedState = false;
			continue;
		}
		this->window.clear(sf::Color::Black);
		peekState()->draw(deltaTime);
		this->window.display();

		
	}
}

// Initialize the window in a 1280 x 800 window with 60fps
Game::Game()
{
	this->loadTextures();

	// gravity.x = 0.f;
	// gravity.y = 9.8f;

	// world.SetGravity(gravity);

	this->window.create(sf::VideoMode(1280, 800), "The Joy of Numbers with Bob Ross", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(60);

	this->background.setTexture(this->texManager.getRef("background"));
	//this->window.draw(background);

	this->defaultFont.loadFromFile("media/arial.ttf");
}

Game::~Game()
{
	while (!this->states.empty()) popState();
}