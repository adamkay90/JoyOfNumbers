
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "client_socket.h"
//TODO use actual number of lessons for quiz info and lesson info
namespace{
	static const char* const IP_ADDRESS = "155.99.175.104";
	static const int PORT = 55555; 
	static sf::Uint64 user_id_ = 0;
	static std::string user_name_; 
	static std::string first_name_;
	static std::string last_name_;
	static bool instructor_;
	static std::vector<sf::Uint64> quizzes_;
	static std::vector<sf::Uint64> sections_;
}

void ClientSocket::login(std::string user_name, std::string password){
	
	//Connect to socket
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
	}
	std::cout << "Connection made" << std::endl;
	
	user_name_ = user_name;
	sf::Packet send_packet;
	send_packet << sf::Uint64(1) << user_name << password;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	std::cout << "Sending succeeded" << std::endl;
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}

	sf::Uint64 receive_enum; 
	response_packet >> receive_enum >>user_id_;
	if (receive_enum != sf::Uint64(1)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}
	else{
		if (user_id_ == 0){
			//login failed.
			std::cerr << "Login Failed" << std::endl;
		}
		else{
			response_packet >> first_name_ >> last_name_ >> instructor_;
			std::cout << user_id_ << " " << first_name_ << " " << last_name_ << " " << instructor_ << std::endl;
		}
	}
	socket.disconnect(); 
}
void ClientSocket::register_user(std::string user_name, std::string first_name, std::string last_name, std::string password, bool instructor){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl; 
	}
	std::cout << "Connection made" << std::endl;
	
	user_name_ = user_name;
	first_name_ = first_name;
	last_name_ = last_name;
	instructor_ = false;
	
	sf::Packet send_packet;
	send_packet << sf::Uint64(2) << user_name << first_name << last_name<<password << instructor;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	std::cout << "Sending succeeded" << std::endl;
	
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}
	
	sf::Uint64 receive_enum;
	response_packet >> receive_enum >>user_id_;

	if (receive_enum != sf::Uint64(2)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}
	else{

		if (user_id_ == 0){
			//register failed.
			std::cerr << "Login Failed" << std::endl;
		}
		else{
			//register succeeded
			std::cout << user_id_ << std::endl;
		}
	}
	socket.disconnect(); 
}
void ClientSocket::html(){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);

	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
	}
	std::cout << "Connection made" << std::endl;

	sf::Packet send_packet;
	send_packet << sf::Uint64(3);;
	
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	
	std::cout << "Sending succeeded" << std::endl;
	sf::Packet response_packet;
	
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}
	
	sf::Uint64 receive_enum;
	std::string html_info; 
	response_packet >> receive_enum;
	
	if (receive_enum != sf::Uint64(3)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}
	else{
		//register succeeded

		response_packet >> html_info;
		std::cout << html_info << std::endl;
		std::ofstream output_stream("PROGRESS_REPORT.html", std::ios::out | std::ios::binary);
		output_stream.exceptions(std::ofstream::failbit | std::ofstream::badbit);

		output_stream << html_info;
	}

	socket.disconnect(); 
}
void ClientSocket::quiz_score(sf::Uint64 quiz_id, sf::Uint64 quiz_score){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
	}
	std::cout << "Connection made" << std::endl;
	
	sf::Packet send_packet;

	send_packet << sf::Uint64(4) << user_id_ << quiz_id << quiz_score;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	std::cout << "Sending succeeded" << std::endl;
	
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}
	sf::Uint64 receive_enum;
	response_packet >> receive_enum; 
	if (receive_enum != sf::Uint64(4)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}

	socket.disconnect();
}
void ClientSocket::lesson_progress(sf::Uint64 lesson_id, sf::Uint64 lesson_section){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
	}
	std::cout << "Connection made" << std::endl;
	
	sf::Packet send_packet;
	send_packet << sf::Uint64(5) << user_id_ << lesson_id << lesson_section;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	std::cout << "Sending succeeded" << std::endl;
	
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}
	
	sf::Uint64 receive_enum;
	response_packet >> receive_enum;
	if (receive_enum != sf::Uint64(5)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}

	socket.disconnect();
}
/*
 *Using the user_id, returns the number of quiz points
 *for each quiz.
 */
void ClientSocket::quiz_info(){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
	}
	std::cout << "Connection made" << std::endl;
	
		
	sf::Packet send_packet;
	send_packet << sf::Uint64(6) << user_id_;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	std::cout << "Sending succeeded" << std::endl;
	
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}
	sf::Uint64 receive_enum;
	response_packet >> receive_enum; 
	if (receive_enum != sf::Uint64(6)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}
	else{
		sf::Uint64 quiz;
		for (std::vector<std::vector<std::string>>::size_type i{ 0 }; i < 5; ++i){
			response_packet >> quiz;//TODO use actual number of lessons for quiz info and lesson info
			quizzes_.emplace_back(quiz); 
			std::cout << quiz << std::endl;
		}
	}
	socket.disconnect();
	
}
/*
 *Using the user_id, returns the number of sections that have been completed
 *for each lesson (assumed 10 right now)
 */
void ClientSocket::lesson_info(){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
	}
	std::cout << "Connection made" << std::endl;
	
	
	sf::Packet send_packet;
	send_packet << sf::Uint64(7) << user_id_;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	std::cout << "Sending succeeded" << std::endl;
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}
	
	sf::Uint64 receive_enum;
	response_packet >> receive_enum;
	if (receive_enum != sf::Uint64(7)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}
	else{
		sf::Uint64 lesson_section;
		for (std::vector<std::vector<std::string>>::size_type i{ 0 }; i < 4; ++i){
			response_packet >> lesson_section;//TODO use actual number of lessons for quiz info and lesson info
			sections_.emplace_back(lesson_section); 
			std::cout << sections_[i] << std::endl;
		}
	}
	socket.disconnect();
}
void ClientSocket::rename_user(std::string user_name, std::string new_first_name, std::string new_last_name){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
	}
	std::cout << "Connection made" << std::endl;


	sf::Packet send_packet;
	send_packet << sf::Uint64(8) << user_name<<new_first_name<<new_last_name;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	std::cout << "Sending succeeded" << std::endl;
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}

	sf::Uint64 receive_enum;
	response_packet >> receive_enum;
	if (receive_enum != sf::Uint64(8)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}
	else{
		std::cout << "success rename" << std::endl;
	}
	socket.disconnect();
}
void ClientSocket::remove_user(std::string user_name){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
	}
	std::cout << "Connection made" << std::endl;


	sf::Packet send_packet;
	send_packet << sf::Uint64(9) << user_name;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	std::cout << "Sending succeeded" << std::endl;
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}

	sf::Uint64 receive_enum;
	response_packet >> receive_enum;
	if (receive_enum != sf::Uint64(9)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}
	else{
		std::cout << "success delete" << std::endl;
	}
	socket.disconnect();
}
void ClientSocket::add_user(std::string user_name, std::string first_name, std::string last_name, std::string password, bool instructor){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(IP_ADDRESS, PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
	}
	std::cout << "Connection made" << std::endl;

	sf::Packet send_packet;
	send_packet << sf::Uint64(2) << user_name << first_name << last_name << password << instructor;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		return;
	}
	std::cout << "Sending succeeded" << std::endl;

	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
	}

	sf::Uint64 receive_enum;
	response_packet >> receive_enum;

	if (receive_enum != sf::Uint64(2)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
	}

	socket.disconnect();
}
void ClientSocket::test(){
	std::vector<sf::Uint64> user_id_local;
	std::vector<std::string> user_names{"user1", "user2", "user3", "user4", "user5"}; 
	std::vector<std::string> first{"Joe", "Tim", "Tom", "Brynn", "Bob"};
	std::vector<std::string> last{ "Alexis", "Bohensky", "Cobell", "Kasik", "Ross"};
	std::vector<std::string> password{ "a", "b", "c", "d", "e" };
	std::vector<bool> instructor_status{ false, false, false, false, false};
	
	for (int i = 0; i < 5; i++){
		register_user(user_names[i], first[i], last[i], password[i], instructor_status[i]); 
		user_id_local.emplace_back(user_id_); 
	}
	for (int i = 0; i < 5; i++){
		login(user_names[i], password[i]);
		if (user_id_local[i] != user_id_){
			std::cout << "ERROR: user ids do not match. stored: " << user_id_local[i] << " current: " << user_id_ << std::endl; 
		}
	}
	for (int i = 0; i < 5; i++){
		user_id_ = user_id_local[i];
		user_name_ = user_names[i];
		first_name_ = first[i];
		last_name_ = last[i];
		instructor_ = instructor_status[i];
		
		for (int j = 1; j <= 4; j++){
			lesson_progress(sf::Uint64(j), sf::Uint64(j));
		}
		for (int j = 1; j <= 4; j++){
			lesson_progress(sf::Uint64(j), sf::Uint64(3));
		}
		for (int j = 1; j <= 4; j++){
			lesson_progress(sf::Uint64(j), sf::Uint64(1));
		}

	}
	for (int i = 0; i < 5; i++){
		user_id_ = user_id_local[i];
		user_name_ = user_names[i];
		first_name_ = first[i];
		last_name_ = last[i];
		instructor_ = instructor_status[i];
		
		for (int j = 1; j <= 5; j++){
			quiz_score(sf::Uint64(j), sf::Uint64(j));
		}
		for (int j = 1; j <= 5; j++){
			quiz_score(sf::Uint64(j), sf::Uint64(3));
		}
		for (int j = 1; j <= 5; j++){
			quiz_score(sf::Uint64(j), sf::Uint64(1));
		}
	}
	
	/*for (int i = 0; i < 5; i++){
		user_id_ = user_id_local[i];
		user_name_ = user_names[i];
		first_name_ = first[i];
		last_name_ = last[i];
		instructor_ = instructor_status[i];
	}*/
	
	/*quiz_info();
	lesson_info();*/

	html();
	add_user("user6", "Ellyx", "Jolley", "password", false); 
}