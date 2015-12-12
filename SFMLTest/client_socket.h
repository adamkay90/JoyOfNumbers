#pragma once

#include <SFML\Network.hpp>

class ClientSocket
{
public:
	static void login(std::string user_name, std::string password);
	static void register_user(std::string user_name, std::string first_name, std::string last_name, std::string password, bool instructor);
	static void html();
	static void quiz_score(sf::Uint64 quiz_id, sf::Uint64 quiz_score); 
	static void lesson_progress(sf::Uint64 lesson_id, sf::Uint64 lesson_section);
	static void quiz_info();
	static void lesson_info();
	static void rename_user(std::string user_name, std::string new_first_name, std::string new_last_name);
	static void remove_user(std::string user_name);



	static void test(); 
	
};

