//
// Created by seb on 24/11/2019.
//

#pragma  once

#include <list>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TCPConnection {// : public boost::enable_shared_from_this<TCPConnection> {
private:
public:

	TCPConnection(boost::asio::io_context& io_context);
	static std::shared_ptr<TCPConnection> create(boost::asio::io_context& io_context);
	void start();
	void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
	void handleWrite(const boost::system::error_code& error);

	void sendData(const char *dat, size_t size);

public:
	bool toRemove;
	tcp::socket tcpSocket;

	enum { max_length = 1024 };
	char data[max_length];

	std::mutex updatesMutex;
	std::list<std::string> updates;

	typedef std::shared_ptr<TCPConnection> pointer;
};
