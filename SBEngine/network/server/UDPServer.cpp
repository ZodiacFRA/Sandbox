//
// Created by seb on 24/11/2019.
//

#include <iostream>
#include "UDPServer.hpp"

UDPServer::UDPServer(boost::asio::io_context &io_context, short port): udpSocket(io_context, udp::endpoint(udp::v4(), port)) {
	startReceive();
}

void UDPServer::startReceive() {
	udpSocket.async_receive_from(
		boost::asio::buffer(data), remoteEndpoint,
		boost::bind(&UDPServer::handleReceive, this,
			    boost::asio::placeholders::error,
			    boost::asio::placeholders::bytes_transferred));
}

void UDPServer::handleReceive(const boost::system::error_code &error, size_t bytes_recvd) {
	if (!error && bytes_recvd > 0) {
		udpSocket.async_send_to(
			boost::asio::buffer(data, bytes_recvd), remoteEndpoint,
			boost::bind(&UDPServer::handleSend, this,
				    boost::asio::placeholders::error,
				    boost::asio::placeholders::bytes_transferred));
	} else {
		udpSocket.async_receive_from(
			boost::asio::buffer(data, max_length), remoteEndpoint,
			boost::bind(&UDPServer::handleReceive, this,
				    boost::asio::placeholders::error,
				    boost::asio::placeholders::bytes_transferred));
	}
}

void UDPServer::handleSend(const boost::system::error_code &error, size_t bytes_sent) {
	udpSocket.async_receive_from(
		boost::asio::buffer(data, max_length), remoteEndpoint,
		boost::bind(&UDPServer::handleReceive, this,
			    boost::asio::placeholders::error,
			    boost::asio::placeholders::bytes_transferred));
}
