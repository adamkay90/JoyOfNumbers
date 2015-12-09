#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <TGUI\TGUI.hpp>
#include <iostream>

#include "game_state.h"
#include "register_state.h"
#include "quiz_state.h"


class GameStateLogin : public GameState
{
private:

	sf::Sprite logo;
	sf::Sprite face;
	sf::Music background;

	float flipTime = 0.3;
	float angle1 = 30;
	float angle2 = 325;
	float faceTimer;

	float spinSpeed = 270;

	sf::View view;

	b2Vec2* gravity;
	b2World* world;

	float spawnTime;
	float spawnTimer;

	void loadMenu();
	void onLoginButtonClick();
	void onRegisterButtonClick();
	void getDataFromTextBoxes();

	void CreateGround(b2World& World, float X, float Y);
	void CreateBox(b2World& World, int MouseX, int MouseY); 
	void SetupGui();

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateLogin(Game* game);
	~GameStateLogin();

	tgui::Gui* gui;
};