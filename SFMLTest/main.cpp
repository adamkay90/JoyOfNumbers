#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include "game.h";
#include "game_state_start.h"
#include "game_state_login.h"
#include "quiz_state.h"
#include "client_socket.h"
#include "teacher_state.h"
int main()
{
	/*
	ClientSocket::register_user("user_name", "First", "Last", "HelloWorld", false); 
	ClientSocket::login("user_name", "HelloWorld"); 
	ClientSocket::quiz_score(sf::Uint64(1), sf::Uint64(1));
	ClientSocket::quiz_info(); 
	*/

	Game game;
	
	game.pushState(new GameStateLogin(&game));
	//game.pushState(new TeacherState(&game));
	game.gameLoop();
	
	return 0;
}

