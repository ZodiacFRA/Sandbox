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
#include <iostream>

using boost::asio::ip::tcp;
using boost::asio::steady_timer;

class TCPClient
{
public:
	TCPClient(boost::asio::io_context& io_context)
		: stopped_(false),
		  socket_(io_context),
		  deadline_(io_context),
		  heartbeat_timer_(io_context) {
	}

	void start(tcp::resolver::results_type endpoints)
	{
		endpoints_ = endpoints;
		start_connect(endpoints_.begin());
		deadline_.async_wait(boost::bind(&TCPClient::check_deadline, this));
	}

	void stop()
	{
		stopped_ = true;
		boost::system::error_code ignored_ec;
		socket_.close(ignored_ec);
		deadline_.cancel();
		heartbeat_timer_.cancel();
	}

private:
	void start_connect(tcp::resolver::results_type::iterator endpoint_iter)
	{
		if (endpoint_iter != endpoints_.end()) {
			std::cout << "Trying " << endpoint_iter->endpoint() << "...\n";
			deadline_.expires_after(boost::asio::chrono::seconds(60));
			socket_.async_connect(endpoint_iter->endpoint(),
					      boost::bind(&TCPClient::handle_connect,
							  this, _1, endpoint_iter));
		} else {
			stop();
		}
	}

	void handle_connect(const boost::system::error_code& ec,
			    tcp::resolver::results_type::iterator endpoint_iter)
	{
		if (stopped_)
			return;
		if (!socket_.is_open()) {
			std::cout << "Connect timed out\n";
			start_connect(++endpoint_iter);
		} else if (ec) {
			std::cout << "Connect error: " << ec.message() << "\n";
			socket_.close();
			start_connect(++endpoint_iter);
		} else {
			std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";
			start_read();
			start_write();
		}
	}

	void start_read()
	{
		deadline_.expires_after(boost::asio::chrono::seconds(30));
		boost::asio::async_read_until(socket_,
					      boost::asio::dynamic_buffer(input_buffer_), '\0',
					      boost::bind(&TCPClient::handle_read, this, _1, _2));
	}
	void handle_read(const boost::system::error_code& ec, std::size_t n)
	{
		if (stopped_)
			return;
		if (!ec) {
			std::string line(input_buffer_.substr(0, n - 1));
			input_buffer_.erase(0, n);
			if (!line.empty())
			{
				std::cout << "Received:\n" << line << "\n\n";
			}
			start_read();
		} else {
			std::cout << "Error on receive: " << ec.message() << "\n";
			stop();
		}
	}

	void start_write()
	{
		if (stopped_)
			return;
		boost::asio::async_write(socket_, boost::asio::buffer("\n", 1),
					 boost::bind(&TCPClient::handle_write, this, _1));
	}

	void handle_write(const boost::system::error_code& ec)
	{
		if (stopped_)
			return;
		if (!ec) {
			heartbeat_timer_.expires_after(boost::asio::chrono::seconds(10));
			heartbeat_timer_.async_wait(boost::bind(&TCPClient::start_write, this));
		} else {
			std::cout << "Error on heartbeat: " << ec.message() << "\n";
			stop();
		}
	}

	void check_deadline()
	{
		if (stopped_)
			return;
		if (deadline_.expiry() <= steady_timer::clock_type::now()) {
			socket_.close();
			deadline_.expires_at(steady_timer::time_point::max());
		}
		deadline_.async_wait(boost::bind(&TCPClient::check_deadline, this));
	}

private:
	bool stopped_;
	tcp::resolver::results_type endpoints_;
	tcp::socket socket_;
	std::string input_buffer_;
	steady_timer deadline_;
	steady_timer heartbeat_timer_;
};
