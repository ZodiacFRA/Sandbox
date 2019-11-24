//
// Created by seb on 24/11/2019.
//

#pragma  once

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(nullptr);
	return ctime(&now);
}

class TCPConnection : public boost::enable_shared_from_this<TCPConnection> {
private:
	TCPConnection(boost::asio::io_context& io_context): socket_(io_context){
	}

public:
	static boost::shared_ptr<TCPConnection> create(boost::asio::io_context& io_context)
	{
		return boost::shared_ptr<TCPConnection>(new TCPConnection(io_context));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		message_ = make_daytime_string();

		boost::asio::async_write(socket_, boost::asio::buffer(message_),
					 boost::bind(&TCPConnection::handle_write, shared_from_this()));
	}

private:
	void handle_write()
	{
	}

	tcp::socket socket_;
	std::string message_;
};