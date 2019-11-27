//
// Created by seb on 24/11/2019.
//

#include <iostream>
#include <boost/asio/io_service.hpp>
#include <network/server/TCPServer.hpp>
#include <network/server/UDPServer.hpp>
#include <network/client/TCPClient.hpp>

int main() {
	try
	{
		boost::asio::io_context io_context;
		tcp::resolver r(io_context);
		TCPClient c(io_context);

		c.start(r.resolve("localhost", "4242"));

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}