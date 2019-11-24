//
// Created by seb on 24/11/2019.
//

#include <iostream>
#include <boost/asio/io_service.hpp>
#include <network/server/TCPServer.hpp>
#include <network/server/UDPServer.hpp>

int main() {
	try
	{
		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		UDPServer s(io_service, 4242);

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}