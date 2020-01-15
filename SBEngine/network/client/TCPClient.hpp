//
// Created by seb on 27/11/2019.
//
// #pragma once

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio.hpp>
#include <string>
#include <queue>
#include <iostream>

using boost::asio::ip::tcp;
using boost::asio::steady_timer;

class TCPClient {
public:
	explicit TCPClient(boost::asio::io_context& io_context);

	void start(tcp::resolver::results_type endpoints);
	void stop();

	tcp::socket *socket();

private:
	void start_connect(tcp::resolver::results_type::iterator endpoint_iter);
	void handle_connect(const boost::system::error_code& ec, tcp::resolver::results_type::iterator endpoint_iter);
	void start_read();
	void handle_read(const boost::system::error_code& ec, std::size_t n);
	void start_write();
	void handle_write(const boost::system::error_code& ec);
	void check_deadline();

public:
	std::mutex mutex;
	std::queue<std::string> pendingUpdates;
private:
	bool stopped_;
	tcp::resolver::results_type endpoints_;
	tcp::socket socket_;
	std::string input_buffer_;
	steady_timer deadline_;
	steady_timer heartbeat_timer_;
};
