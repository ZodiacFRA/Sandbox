/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Boost TCP connection implementation
*/

#include "TCPConnection.hpp"
#include "ConnectionMgr.hpp"
#include "CmdHandler.hpp"

namespace Babel {

	TCPConnection::TCPConnection(boost::asio::io_context &ioc,
		ConnectionMgr &conMgr, CmdHandler &handler)
	: _socket(ioc),
	_conMgr(conMgr),
	_handler(handler),
	_buffer(BUFFER_SIZE, '\0'),
	_ip(),
	_pending()
	{}

	TCPConnection::~TCPConnection()
	{}

	TCPConnection::ptr TCPConnection::create(boost::asio::io_context &ioc,
		ConnectionMgr &conMgr, CmdHandler &handler)
	{
		return ptr(new TCPConnection(ioc, conMgr, handler));
	}

	boost::asio::ip::tcp::socket &TCPConnection::socket()
	{
		return _socket;
	}

	void TCPConnection::start()
	{
		_ip = _socket.remote_endpoint().address().to_string();
		do_read();
	}

	void TCPConnection::stop()
	{
		_socket.cancel();
		_socket.close();
	}

	ConnectionMgr &TCPConnection::manager()
	{
		return _conMgr;
	}

	void TCPConnection::send(const std::string &cmd)
	{
		bool writing = !_pending.empty();
		_pending.push_back(cmd);
		if (!writing)
			do_write();
	}

	const std::string &TCPConnection::ip() const
	{
		return _ip;
	}

	void TCPConnection::do_read()
	{
		if(!_socket.is_open())
			return;
		_socket.async_read_some(boost::asio::buffer(_buffer, BUFFER_SIZE),
		boost::bind(&TCPConnection::handle_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)
		);
	}

	void TCPConnection::do_write()
	{
		if(!_socket.is_open())
			return;
		boost::asio::async_write(_socket, boost::asio::buffer(_pending.front().data(), _pending.front().length()),
		boost::bind(&TCPConnection::handle_write, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)
		);
	}

	void TCPConnection::handle_write(const boost::system::error_code& err,size_t nbytes)
	{
		if(!err){
			_pending.pop_front();
			if(!_pending.empty())
				do_write();
		} else if (err != boost::asio::error::operation_aborted) {
			_handler.notify_disconnect(shared_from_this());
			_conMgr.stop(shared_from_this());
		}
	}

	void TCPConnection::handle_read(const boost::system::error_code& err, size_t nbytes)
	{
		if(!err){
			_handler.process(_buffer, shared_from_this());
			do_read();
		} else if (err != boost::asio::error::operation_aborted) {
			_handler.notify_disconnect(shared_from_this());
			_conMgr.stop(shared_from_this());
		}
	}
} /* Babel */
