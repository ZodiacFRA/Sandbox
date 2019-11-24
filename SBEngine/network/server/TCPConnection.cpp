//
// Created by seb on 24/11/2019.
//

#include <iostream>
#include "TCPConnection.hpp"

TCPConnection::TCPConnection(boost::asio::io_context &io_context): tcpSocket(io_context) {
}

boost::shared_ptr<TCPConnection> TCPConnection::create(boost::asio::io_context& io_context) {
	return boost::shared_ptr<TCPConnection>(new TCPConnection(io_context));
}

void TCPConnection::start() {
	tcpSocket.async_read_some(boost::asio::buffer(data, max_length),
				boost::bind(&TCPConnection::handleRead, shared_from_this(),
					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
	if (!error) {
		boost::asio::async_write(tcpSocket,
					 boost::asio::buffer(data, bytes_transferred),
					 boost::bind(&TCPConnection::handleWrite, shared_from_this(),
						     boost::asio::placeholders::error));
		start();
	} else {
		std::cout << error.message() << std::endl;
		delete this;
	}
}

void TCPConnection::handleWrite(const boost::system::error_code& error) {
	if (!error) {
		tcpSocket.async_read_some(boost::asio::buffer(data, max_length),
					boost::bind(&TCPConnection::handleRead, this,
						    boost::asio::placeholders::error,
						    boost::asio::placeholders::bytes_transferred));
	} else {
		delete this;
	}
}
