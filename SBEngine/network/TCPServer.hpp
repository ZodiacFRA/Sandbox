//
// Created by seb on 24/11/2019.
//

#pragma once

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "TCPConnection.hpp"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

class TCPServer {
public:
	TCPServer(boost::asio::io_context& io_context)
		: ioContext(io_context),
		  acceptor(io_context, tcp::endpoint(tcp::v4(), 13))
	{
		startAccept();
	}

private:
	void startAccept()
	{
		TCPConnection::pointer new_connection =
			TCPConnection::create(ioContext);

		acceptor.async_accept(new_connection->socket(),
				      boost::bind(&TCPServer::handleAccept, this, new_connection,
						  boost::asio::placeholders::error));
	}

	void handleAccept(TCPConnection::pointer new_connection,
			  const boost::system::error_code& error)
	{
		if (!error)
		{
			new_connection->start();
		}

		startAccept();
	}

	boost::asio::io_context& ioContext;
	tcp::acceptor acceptor;
};
