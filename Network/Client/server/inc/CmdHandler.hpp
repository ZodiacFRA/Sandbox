/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Command Handler definition
*/

#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <map>
#include "IConnection.hpp"
#include "Command.hpp"
#include "protocol.hpp"

namespace Babel {
	class UserMgr;

	class CmdHandler {
	public:
		typedef void (CmdHandler::*func)(const IConnection::ptr &c, Command &cmd) const;

		CmdHandler(UserMgr &userMgr);
		~CmdHandler();

		void process(const std::string &cmd, const IConnection::ptr &c) const;
		void notify_disconnect(const IConnection::ptr &c) const;

	private:
		UserMgr &_userMgr;

		static std::map<uint32_t, func> _handlers;

		void send_code(const IConnection::ptr &c, Command &cmd, reply::codes code) const;

		//handlers
		void handle_register(const IConnection::ptr &c, Command &cmd) const;
		void handle_login(const IConnection::ptr &c, Command &cmd) const;
		void handle_add(const IConnection::ptr &c, Command &cmd) const;
		void handle_del(const IConnection::ptr &c, Command &cmd) const;
		void handle_get(const IConnection::ptr &c, Command &cmd) const;
		void handle_invite(const IConnection::ptr &c, Command &cmd) const;
		void handle_accept(const IConnection::ptr &c, Command &cmd) const;
		void handle_hangup(const IConnection::ptr &c, Command &cmd) const;
		void handle_reject(const IConnection::ptr &c, Command &cmd) const;
		void handle_disconnect(const IConnection::ptr &c, Command &cmd) const;

	};

} /* Babel */

#endif
