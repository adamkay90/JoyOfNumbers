
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "client_socket.h"
//TODO use actual number of lessons for quiz info and lesson info

namespace client_information{
	const char* const IP_ADDRESS = "155.99.175.104";
	const int PORT = 55555;
	sf::Uint64 user_id_ = 0;
	std::string user_name_;
	std::string first_name_;
	std::string last_name_;
	bool instructor_;
	std::vector<sf::Uint64> quizzes_;
	std::vector<sf::Uint64> sections_;
}


sf::Uint64 ClientSocket::login(std::string user_name, std::string password){
	
	//Connect to socket
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
		socket.disconnect();
		return sf::Uint64(0); 
	}
	std::cout << "Connection made" << std::endl;
	
	client_information::user_name_ = user_name;
	sf::Packet send_packet;
	send_packet << sf::Uint64(1) << user_name << password;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	std::cout << "Sending succeeded" << std::endl;
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Uint64 receive_enum; 
	response_packet >> receive_enum >> client_information::user_id_;
	if (receive_enum != sf::Uint64(1)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	else{
		response_packet >> client_information::first_name_ >> client_information::last_name_ >> client_information::instructor_;
		std::cout << client_information::user_id_ << " " << client_information::first_name_ << " " << client_information::last_name_ << " " << client_information::instructor_ << std::endl;
		socket.disconnect();
		return receive_enum; 
	}
}
sf::Uint64 ClientSocket::register_user(std::string user_name, std::string first_name, std::string last_name, std::string password, bool instructor){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl; 
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	client_information::user_name_ = user_name;
	client_information::first_name_ = first_name;
	client_information::last_name_ = last_name;
	client_information::instructor_ = false;
	
	sf::Packet send_packet;
	send_packet << sf::Uint64(2) << user_name << first_name << last_name<<password << instructor;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cerr << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	sf::Uint64 receive_enum;
	response_packet >> receive_enum >> client_information::user_id_;

	if (receive_enum != sf::Uint64(2)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	else{
		std::cout << client_information::user_id_ << std::endl;
		socket.disconnect();
		return receive_enum; 
	}
}
sf::Uint64 ClientSocket::html(){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);

	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Packet send_packet;
	send_packet << sf::Uint64(3);;
	
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Packet response_packet;
	
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	sf::Uint64 receive_enum;
	std::string html_info; 
	response_packet >> receive_enum;
	
	if (receive_enum != sf::Uint64(3)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	else{
		//register succeeded

		response_packet >> html_info;
		std::cout << html_info << std::endl;
		std::ofstream output_stream("PROGRESS_REPORT.html", std::ios::out | std::ios::binary);
		output_stream.exceptions(std::ofstream::failbit | std::ofstream::badbit);

		output_stream << html_info;
		socket.disconnect();
		return receive_enum; 
	}
}
sf::Uint64 ClientSocket::quiz_score(sf::Uint64 quiz_id, sf::Uint64 quiz_score){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Packet send_packet;

	send_packet << sf::Uint64(4) << client_information::user_id_ << quiz_id << quiz_score;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	sf::Uint64 receive_enum;
	response_packet >> receive_enum; 
	if (receive_enum != sf::Uint64(4)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	socket.disconnect();
	return receive_enum;
}
sf::Uint64 ClientSocket::lesson_progress(sf::Uint64 lesson_id, sf::Uint64 lesson_section){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	std::cout << "Connection made" << std::endl;
	
	sf::Packet send_packet;
	send_packet << sf::Uint64(5) << client_information::user_id_ << lesson_id << lesson_section;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	std::cout << "Sending succeeded" << std::endl;
	
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	sf::Uint64 receive_enum;
	response_packet >> receive_enum;
	if (receive_enum != sf::Uint64(5)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	socket.disconnect();
	return receive_enum; 
}
/*
 *Using the user_id, returns the number of quiz points
 *for each quiz.
 */
sf::Uint64 ClientSocket::quiz_info(){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
		
	sf::Packet send_packet;
	send_packet << sf::Uint64(6) << client_information::user_id_;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	sf::Uint64 receive_enum;
	response_packet >> receive_enum; 
	if (receive_enum != sf::Uint64(6)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	else{
		sf::Uint64 quiz;
		for (std::vector<std::vector<std::string>>::size_type i{ 0 }; i < 5; ++i){
			response_packet >> quiz;//TODO use actual number of lessons for quiz info and lesson info
			client_information::quizzes_.emplace_back(quiz);
			std::cout << quiz << std::endl;
		}
	}
	socket.disconnect();
	return receive_enum; 
}
/*
 *Using the user_id, returns the number of sections that have been completed
 *for each lesson (assumed 10 right now)
 */
sf::Uint64 ClientSocket::lesson_info(){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	sf::Packet send_packet;
	send_packet << sf::Uint64(7) << client_information::user_id_;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	std::cout << "Sending succeeded" << std::endl;
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	
	sf::Uint64 receive_enum;
	response_packet >> receive_enum;
	if (receive_enum != sf::Uint64(7)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	else{
		sf::Uint64 lesson_section;
		for (std::vector<std::vector<std::string>>::size_type i{ 0 }; i < 4; ++i){
			response_packet >> lesson_section;//TODO use actual number of lessons for quiz info and lesson info
			client_information::sections_.emplace_back(lesson_section);
			std::cout << client_information::sections_[i] << std::endl;
		}
	}
	socket.disconnect();
	return receive_enum; 
}
sf::Uint64 ClientSocket::rename_user(std::string user_name, std::string new_first_name, std::string new_last_name){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Packet send_packet;
	send_packet << sf::Uint64(8) << user_name<<new_first_name<<new_last_name;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	std::cout << "Sending succeeded" << std::endl;
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Uint64 receive_enum;
	response_packet >> receive_enum;
	if (receive_enum != sf::Uint64(8)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	socket.disconnect();
	return receive_enum; 
}
sf::Uint64 ClientSocket::remove_user(std::string user_name){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	


	sf::Packet send_packet;
	send_packet << sf::Uint64(9) << user_name;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	std::cout << "Sending succeeded" << std::endl;
	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Uint64 receive_enum;
	response_packet >> receive_enum;
	if (receive_enum != sf::Uint64(9)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}
	socket.disconnect();
	return receive_enum; 
}
sf::Uint64 ClientSocket::add_user(std::string user_name, std::string first_name, std::string last_name, std::string password, bool instructor){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(client_information::IP_ADDRESS, client_information::PORT);
	if (status != sf::Socket::Done){
		std::cerr << "ERROR: Connection to server failed." << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Packet send_packet;
	send_packet << sf::Uint64(2) << user_name << first_name << last_name << password << instructor;
	if (socket.send(send_packet) != sf::Socket::Done){
		std::cout << "Sending failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Packet response_packet;
	if (socket.receive(response_packet) != sf::Socket::Done){
		std::cout << "Receive Failed" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	sf::Uint64 receive_enum;
	response_packet >> receive_enum;

	if (receive_enum != sf::Uint64(2)){
		//register failed.
		std::cerr << "Incorrect ENUM" << std::endl;
		socket.disconnect();
		return sf::Uint64(0);
	}

	socket.disconnect();
	return receive_enum; 
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
		user_id_local.emplace_back(client_information::user_id_);
	}
	for (int i = 0; i < 5; i++){
		login(user_names[i], password[i]);
		if (user_id_local[i] != client_information::user_id_){
			std::cout << "ERROR: user ids do not match. stored: " << user_id_local[i] << " current: " << client_information::user_id_ << std::endl;
		}
	}
	for (int i = 0; i < 5; i++){
		client_information::user_id_ = user_id_local[i];
		client_information::user_name_ = user_names[i];
		client_information::first_name_ = first[i];
		client_information::last_name_ = last[i];
		client_information::instructor_ = instructor_status[i];
		
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
		client_information::user_id_ = user_id_local[i];
		client_information::user_name_ = user_names[i];
		client_information::first_name_ = first[i];
		client_information::last_name_ = last[i];
		client_information::instructor_ = instructor_status[i];
		
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