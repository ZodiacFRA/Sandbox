//
// Created by seb on 24/11/2019.
//

#include "TCPServer.hpp"

TCPServer::TCPServer(boost::asio::io_context &io_context, short port): ioContext(io_context),
	  acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
	startAccept();
}

void TCPServer::startAccept() {
	TCPConnection::pointer new_connection = TCPConnection::create(ioContext);

	acceptor.async_accept(new_connection->tcpSocket,
			      boost::bind(&TCPServer::handleAccept, this, new_connection,
					  boost::asio::placeholders::error));
}

void TCPServer::handleAccept(TCPConnection::pointer newConnection, const boost::system::error_code &error) {
	if (!error) {
		newConnection->start();
	}
	startAccept();
}
