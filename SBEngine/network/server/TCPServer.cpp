//
// Created by seb on 24/11/2019.
//

#include <iostream>
#include "TCPServer.hpp"

TCPServer::TCPServer(boost::asio::io_context &io_context, short port): ioContext(io_context),
	  acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
	startAccept();
}

void TCPServer::startAccept() {
	TCPConnection::pointer new_connection(new TCPConnection(ioContext));

	acceptor.async_accept(new_connection->tcpSocket,
			      boost::bind(&TCPServer::handleAccept, this, new_connection,
					  boost::asio::placeholders::error));
}

void TCPServer::handleAccept(TCPConnection::pointer newConnection, const boost::system::error_code &error) {
	if (!error) {
		newConnection->start();
		connected.push_back(newConnection);
		std::cout << "WTF LANCE TOI" << std::endl;
		if (onConnection)
			onConnection(newConnection);
	} else {
		std::cout << "c est la merde" << std::endl;
	}
	startAccept();
}
