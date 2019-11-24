/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Connection Manager implementation
*/

#include "ConnectionMgr.hpp"

namespace Babel {

	ConnectionMgr::ConnectionMgr()
	{}

	ConnectionMgr::~ConnectionMgr()
	{}

	void ConnectionMgr::start(IConnection::ptr c)
	{
		_connections.insert(c);
		c->start();
	}

	void ConnectionMgr::stop(const IConnection::ptr &c)
	{
		_connections.erase(c);
		c->stop();
	}

	void ConnectionMgr::stop_all()
	{
		for(auto c: _connections)
			c->stop();
		_connections.clear();
	}

} /* Babel */
