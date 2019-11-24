/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Server definition
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include "common.hpp"
#include "NetworkMgr.hpp"
#include "CmdHandler.hpp"
#include "UserMgr.hpp"
#include "helpers.hpp"

namespace Babel {
	class Server {
	public:
		Server(unsigned short port);
		~Server();

		void run();
	private:
		UserMgr _userMgr;
		CmdHandler _comHandler;
		NetworkMgr _netMgr;

	};

} /* Babel */

#endif /* end of include guard: SERVER_HPP */
