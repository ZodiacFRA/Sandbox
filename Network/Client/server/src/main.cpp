/*
** EPITECH PROJET, 2018
** @Project: c++ advanced
** filename
** main file for babel client
*/

#include "Server.hpp"

int usage(char **argv)
{
	std::cout << "Usage: " << argv[0] << " port" << std::endl <<
	"\tport - the port the server will bind to" << std::endl;
	return FAILURE;
}

int main(int argc, char **argv)
{
	if(argc != 2 || std::string(argv[1]) == "-h"){
		return usage(argv);
	}
	try {
		Babel::Server srv(stous(argv[1]));
		srv.run();
	}
	catch(const std::invalid_argument &e){
		std::cerr << "Error: port must be a number: " << e.what() << std::endl;
		return FAILURE;
	}
	catch(const std::out_of_range &e){
		std::cerr << "Error: port must be a valid port number (1 - 65535): " << e.what() << std::endl;
		return FAILURE;
	}
	catch(const std::runtime_error &e) {
		std::cerr << "Error: port is already taken or you don't have enough rights, try another one" << std::endl;
		return FAILURE;
	}
	catch(const std::exception &e) {
		std::cerr << "something horribly wrong happend" << std::endl;
		return FAILURE;
	}
	return SUCCESS;
}
