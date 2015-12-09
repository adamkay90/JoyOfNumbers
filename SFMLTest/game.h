#pragma once

#include <stack>
#include <SFML\Graphics.hpp>
#include "texture_manager.h"
#include <Box2D\Box2D.h>

class GameState;

class Game {
public:

private:

	void loadTextures();

public:

	std::string username;
	std::string password;
	std::string firstName;
	std::string lastName;
	bool isTeacher;

	// The state stack
	std::stack<GameState*> states;

	sf::RenderWindow window;
	TextureManager texManager;
	sf::Sprite background;
	sf::Font defaultFont;

	// b2Vec2 gravity;
	// b2World world;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

	Game();
	~Game();

};