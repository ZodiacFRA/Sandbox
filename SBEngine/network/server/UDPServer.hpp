//
// Created by seb on 24/11/2019.
//

#ifndef SANDBOX_UDPSERVER_HPP
#define SANDBOX_UDPSERVER_HPP

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "TCPConnection.hpp"

using boost::asio::ip::udp;


class UDPServer {
public:
	UDPServer(boost::asio::io_context& io_context, short port);

private:
	void startReceive();

	void handleReceive(const boost::system::error_code& error, size_t bytes_recvd);

	void handleSend(const boost::system::error_code &error, size_t bytes_sent);

	udp::socket udpSocket;
	udp::endpoint remoteEndpoint;
	enum { max_length = 1024 };
	char data[max_length];
};


#endif //SANDBOX_UDPSERVER_HPP
