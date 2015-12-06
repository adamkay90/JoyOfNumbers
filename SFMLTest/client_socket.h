#pragma once

#include <SFML\Network.hpp>

class ClientSocket
{
public:
	static void ClientSocket::login(std::string user_name, std::string password);
	static void ClientSocket::register_user(std::string user_name, std::string first_name, std::string last_name, std::string password, bool instructor);
	static void ClientSocket::html();
	static void ClientSocket::quiz_score(sf::Uint64 quiz_id, sf::Uint64 quiz_score); 
	static void ClientSocket::lesson_progress(sf::Uint64 lesson_id, sf::Uint64 lesson_section);
	static void ClientSocket::quiz_info();
	static void ClientSocket::lesson_info();
	
};

