#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include "game.h";
#include "game_state_start.h"
#include "game_state_login.h"
#include "quiz_state.h"
#include "client_socket.h"
#include "teacher_state.h"
#include "menu_state.h"
#include "lesson_state.h"

int main()
{
	
	ClientSocket::test();

	Game game;
	
	//game.pushState(new GameStateLogin(&game));
	game.pushState(new MenuState(&game));
	//game.pushState(new LessonState(&game));
	//game.pushState(new QuizState(&game));
	//game.pushState(new TeacherState(&game));
	game.gameLoop();
	
	return 0;
}

