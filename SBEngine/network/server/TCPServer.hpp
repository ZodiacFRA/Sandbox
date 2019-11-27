//
// Created by seb on 24/11/2019.
//

#pragma once

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <list>

#include "TCPConnection.hpp"

using boost::asio::ip::tcp;

class TCPServer {
public:
	TCPServer(boost::asio::io_context& io_context, short port);

private:
	void startAccept();

	void handleAccept(TCPConnection::pointer newConnection, const boost::system::error_code& error);

	boost::asio::io_context& ioContext;
	tcp::acceptor acceptor;

public:
	std::list<TCPConnection::pointer> connected;
};
