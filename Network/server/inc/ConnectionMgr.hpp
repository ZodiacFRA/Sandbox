/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Connection Manager definition
*/

#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <set>
#include "IConnection.hpp"

namespace Babel {

	class ConnectionMgr {
	public:
		ConnectionMgr(const ConnectionMgr&) = delete;
		ConnectionMgr& operator=(const ConnectionMgr&) = delete;

		ConnectionMgr();
		~ConnectionMgr();


		void start(IConnection::ptr c);

		void stop(const IConnection::ptr &c);

		void stop_all();

	private:
		std::set<IConnection::ptr> _connections;

	};

} /* Babel */

#endif
