//
// Created by seb on 24/11/2019.
//

#include <iostream>
#include "TCPConnection.hpp"

TCPConnection::TCPConnection(boost::asio::io_context &io_context): tcpSocket(io_context) {
	toRemove = false;
}

std::shared_ptr<TCPConnection> TCPConnection::create(boost::asio::io_context& io_context) {
	return std::shared_ptr<TCPConnection>(new TCPConnection(io_context));
}

void TCPConnection::start() {
	if (toRemove)
		return;
	tcpSocket.async_read_some(boost::asio::buffer(data, max_length),
				boost::bind(&TCPConnection::handleRead, this,
					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
	if (toRemove)
		return;
	if (!error) {
		std::istringstream in(data);
		std::cout << in.str() << std::endl << std::endl;
		updatesMutex.lock();
		updates.push_back(in.str());
		updatesMutex.unlock();
		start();
		return;
		boost::asio::async_write(tcpSocket,
					 boost::asio::buffer(data, bytes_transferred),
					 boost::bind(&TCPConnection::handleWrite, this,
						     boost::asio::placeholders::error));
		start();
	} else {
		toRemove = true;
	}
}

void TCPConnection::handleWrite(const boost::system::error_code& error) {
	if (toRemove)
		return;
	if (!error) {
		tcpSocket.async_read_some(boost::asio::buffer(data, max_length),
					boost::bind(&TCPConnection::handleRead, this,
						    boost::asio::placeholders::error,
						    boost::asio::placeholders::bytes_transferred));
	} else {
		toRemove = true;
	}
}

void TCPConnection::sendData(const char *dat, size_t size) {
	if (toRemove)
		return;
	boost::asio::async_write(tcpSocket,
				 boost::asio::buffer(dat, size),
				 boost::bind(&TCPConnection::handleWrite, this,
					     boost::asio::placeholders::error));
}

