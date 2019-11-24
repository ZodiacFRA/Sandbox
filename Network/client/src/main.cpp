/*
** EPITECH PROJET, 2018
** @Project: c++ advanced
** filename
** main file for babel server
*/

#include "ClientManager.hpp"

int usage(char **argv)
{
	std::cout << "Usage: " << argv[0] << "ip port" << std::endl <<
	"\tip - the ip the client will try to connect to\n" <<
	"\tport - the port the client will try to connect to" << std::endl;
	return FAILURE;
}

int main(int argc, char **argv)
{
	int flag = SUCCESS;
	if (argc != 3 || (argc == 2 && std::string(argv[1]) == "-h"))
		return usage(argv);
	try {
		QApplication app(argc, argv);
		babel::ClientManager client(argv, nullptr);
		flag = client.run();
	}
	catch(const std::invalid_argument &e){
		std::cerr << "Error: port must be a number: " << e.what() << std::endl;
		return FAILURE;
	}
	catch(const std::out_of_range &e){
		std::cerr << "Error: port must be a valid port number (1 - 65535): " << e.what() << std::endl;
		return FAILURE;
	}
	catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return FAILURE;
	}
	return flag;
}
