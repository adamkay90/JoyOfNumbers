#pragma once

#include <SFML\Network.hpp>

class ClientSocket
{
public:
	static sf::Uint64 login(std::string user_name, std::string password);
	static sf::Uint64 register_user(std::string user_name, std::string first_name, std::string last_name, std::string password, bool instructor);
	static sf::Uint64 html();
	static sf::Uint64 quiz_score(sf::Uint64 quiz_id, sf::Uint64 quiz_score); 
	static sf::Uint64 lesson_progress(sf::Uint64 lesson_id, sf::Uint64 lesson_section);
	static sf::Uint64 quiz_info();
	static sf::Uint64 lesson_info();
	static sf::Uint64 rename_user(std::string user_name, std::string new_first_name, std::string new_last_name);
	static sf::Uint64 remove_user(std::string user_name);
	static sf::Uint64 add_user(std::string user_name, std::string first_name, std::string last_name, std::string password, bool instructor);

	static void test(); 
};

