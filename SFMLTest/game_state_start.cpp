#include <SFML/Graphics.hpp>

#include "game_state_start.h"
#include "game_state_editor.h"
#include "game_state.h"

void GameStateStart::draw(const float dt)
{
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Blue);

	//this->game->window.draw(shape);
	return;
}

void GameStateStart::update(const float dt)
{
}

void GameStateStart::handleInput()
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

			// If the key was the Space Bar, load the game State
			else if (event.key.code == sf::Keyboard::Space) this->loadGame();
			break;
		}
		default: break;
		}
	}

	return;
}

GameStateStart::GameStateStart(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}

// Takes you to the second state, the Editor
void GameStateStart::loadGame()
{
	this->game->pushState(new GameStateEditor(this->game));

	return;
}