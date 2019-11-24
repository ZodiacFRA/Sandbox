/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Boost Network Manager definition
*/

#ifndef BOOST_NETWORK_MANAGER_HPP
#define BOOST_NETWORK_MANAGER_HPP

#include <csignal>
#include "TCPConnection.hpp"
#include "ConnectionMgr.hpp"

namespace Babel {
	class CmdHandler;

	class NetworkMgr {
	public:
		NetworkMgr(unsigned short port, CmdHandler &handler);
		virtual ~NetworkMgr();

		void run();

	private:
		void accept();
		void handle_accept(TCPConnection::ptr new_conn,
			const boost::system::error_code &err);
		void await_signals();

		boost::asio::io_context _ioc;
		boost::asio::signal_set _signals;
		boost::asio::ip::tcp::acceptor _acceptor;
		ConnectionMgr _conMgr;
		CmdHandler &_comHandler;

	};

} /* Babel */

#endif
