/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Boost TCP connection Definition
*/

#ifndef BOOST_TCP_CONNECTION
#define BOOST_TCP_CONNECTION

#include "common.hpp"

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "IConnection.hpp"
#include <deque>

namespace Babel {

	class CmdHandler;

	class TCPConnection : public IConnection, public std::enable_shared_from_this<TCPConnection> {
	public:
		typedef std::shared_ptr<TCPConnection> ptr;

		TCPConnection(const TCPConnection&) = delete;
		TCPConnection& operator=(const TCPConnection&) = delete;

		static ptr create(boost::asio::io_context &ioc,
			ConnectionMgr &conMgr, CmdHandler &handler);

		boost::asio::ip::tcp::socket &socket();

		virtual void start();

		virtual void stop();

		virtual ConnectionMgr &manager();

		virtual const std::string &ip() const;

		virtual void send(const std::string& cmd);

		virtual ~TCPConnection();

	private:
		TCPConnection(boost::asio::io_context &ioc,
			ConnectionMgr &conMgr, CmdHandler &handler);
		void do_read();
		void do_write();
		void handle_write(const boost::system::error_code &err, size_t nbytes);
		void handle_read(const boost::system::error_code &err, size_t nbytes);

		boost::asio::ip::tcp::socket _socket;
		ConnectionMgr &_conMgr;
		CmdHandler &_handler;
		std::string _buffer;
		std::string _ip;
		std::deque<std::string> _pending;
	};
} /* Babel */

#endif
