/*
** EPITECH OJET, 2018
** @Project: Pool
** filename
** description
*/

#include "Server.hpp"

namespace Babel {

	Server::Server(unsigned short port)
	: _userMgr(),
	_comHandler(_userMgr),
	_netMgr(port, _comHandler)
	{}

	Server::~Server()
	{}

	void Server::run()
	{
		_netMgr.run();
	}

} /* Babel */
