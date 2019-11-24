/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Command Handler implementation
*/

#include "CmdHandler.hpp"
#include "ConnectionMgr.hpp"
#include "UserMgr.hpp"
#include "helpers.hpp"

namespace Babel {
	std::map<uint32_t, CmdHandler::func> CmdHandler::_handlers = {
		{static_cast<uint32_t>(client::codes::REGISTER), &CmdHandler::handle_register},
		{static_cast<uint32_t>(client::codes::LOGIN), &CmdHandler::handle_login},
		{static_cast<uint32_t>(client::codes::ADD_CONTACT), &CmdHandler::handle_add},
		{static_cast<uint32_t>(client::codes::DEL_CONTACT), &CmdHandler::handle_del},
		{static_cast<uint32_t>(client::codes::GET_CONTACTS), &CmdHandler::handle_get},
		{static_cast<uint32_t>(client::codes::INVITE_CALL), &CmdHandler::handle_invite},
		{static_cast<uint32_t>(client::codes::ACCEPT_CALL), &CmdHandler::handle_accept},
		{static_cast<uint32_t>(client::codes::HANGUP_CALL), &CmdHandler::handle_hangup},
		{static_cast<uint32_t>(client::codes::REJECT_CALL), &CmdHandler::handle_reject},
		{static_cast<uint32_t>(client::codes::DISCONNECT), &CmdHandler::handle_disconnect}
	};

	CmdHandler::CmdHandler(UserMgr &userMgr)
	: _userMgr(userMgr)
	{}

	CmdHandler::~CmdHandler()
	{}

	void CmdHandler::process(const std::string &cmd, const IConnection::ptr &c) const
	{
		Command com;
		bool valid = true;

		try{
			com.from_str(cmd);
		} catch(const std::length_error &e){
			valid = false;
		} catch(const std::invalid_argument &e){
			valid = false;
		}
		if(!valid || !_handlers.count(com.code()))
			return send_code(c, com, reply::codes::BAD_COMMAND);
		(this->*_handlers[com.code()])(c, com);
	}

	void CmdHandler::send_code(const IConnection::ptr &c, Command &cmd, reply::codes code) const
	{
		cmd.code(static_cast<uint32_t>(code));
		cmd.data("");
		c->send(cmd.to_str());
	}

	void CmdHandler::notify_disconnect(const IConnection::ptr &c) const
	{
		auto &user = _userMgr.getUserByConnection(c);
		if(user){
			Command cmd;
			auto &call = _userMgr.getCall(user);
			if(call && call->ready()){
				auto &other = ((call->caller() == user)? call->callee() : call->caller());
				if(auto othercon = other->connection().lock())
					send_code(othercon, cmd, reply::codes::LEAVE_CALL);
				_userMgr.deleteCall(call);
			} else if(call && call->callee() == user){
				if(auto con = call->caller()->connection().lock())
					send_code(con, cmd, reply::codes::REJECTED);
				_userMgr.deleteCall(call);
			}
			user->disconnect();
			std::cout << "User " << user->name() << " (" << c->ip()
			<< ") disconnected abruptly" << std::endl;
		} else {
			std::cout << "Connection from " << c->ip() << " disconnected abruptly" << std::endl;
		}
	}

	void CmdHandler::handle_register(const IConnection::ptr &c, Command &cmd) const
	{
		std::vector<std::string> registerData;
		splitString(registerData, cmd.data(),
		[](char c){
			return c == '#';
		});
		if(registerData.size() != 2)
			return send_code(c, cmd, reply::codes::BAD_COMMAND);
		if(_userMgr.getUserByConnection(c))
			return send_code(c, cmd, reply::codes::ALREADY_LOGGED_IN);
		if(!_userMgr.createUser(registerData[0], registerData[1]))
			return send_code(c, cmd, reply::codes::USERNAME_USED);
		auto &user = _userMgr.getUserByName(registerData[0]);
		user->connect(c);
		send_code(c, cmd, reply::codes::SUCCESS_REGISTER);
		std::cout << "User " << user->name() << " registered" << std::endl;

	}

	void CmdHandler::handle_login(const IConnection::ptr &c, Command &cmd) const
	{
		std::vector<std::string> loginData;
		splitString(loginData, cmd.data(),
		[](char c){
			return c == '#';
		});
		if(loginData.size() != 2)
			return send_code(c, cmd, reply::codes::BAD_COMMAND);
		auto &user = _userMgr.getUserByName(loginData[0]);
		if(!user || !user->verifyPassword(loginData[1]))
			return send_code(c, cmd, reply::codes::INVALID_CREDENTIALS);
		if(user->connected()){
			if(equals(user->connection(), c))
				return send_code(c, cmd, reply::codes::ALREADY_LOGGED_IN);
			return send_code(c, cmd, reply::codes::ALREADY_CONNECTED);
		}
		user->connect(c);
		send_code(c, cmd, reply::codes::SUCCESS_LOGIN);
		std::cout << "User " << user->name() << " logged in" << std::endl;
	}

	void CmdHandler::handle_add(const IConnection::ptr &c, Command &cmd) const
	{
		auto &user = _userMgr.getUserByConnection(c);
		if(!user)
			return send_code(c, cmd, reply::codes::NOT_LOGGED_IN);
		if(user->name() == cmd.data())
			return send_code(c, cmd, reply::codes::CANT_ADD_YOURSELF);
		auto to_add = _userMgr.getUserByName(cmd.data());
		if(!to_add)
			return send_code(c, cmd, reply::codes::UNKNOWN_USER);
		if(!user->addContact(to_add))
			return send_code(c, cmd, reply::codes::ALREADY_IN_CONTATCS);
		std::cout << user->name() << " added " << to_add->name() <<
		" to his contacts" << std::endl;
		cmd.code(static_cast<uint32_t>(reply::codes::SUCCESS_ADD));
		cmd.data(to_add->name());
		c->send(cmd.to_str());
	}

	void CmdHandler::handle_del(const IConnection::ptr &c, Command &cmd) const
	{
		auto &user = _userMgr.getUserByConnection(c);
		if(!user)
			return send_code(c, cmd, reply::codes::NOT_LOGGED_IN);
		auto to_del = _userMgr.getUserByName(cmd.data());
		if(!to_del)
			return send_code(c, cmd, reply::codes::UNKNOWN_USER);
		if(!user->delContact(to_del))
			return send_code(c, cmd, reply::codes::NOT_IN_CONTACT_LIST);
		std::cout << user->name() << " deleted " << to_del->name() <<
		" from his contacts" << std::endl;
		return send_code(c, cmd, reply::codes::SUCCESS_DEL);
	}

	void CmdHandler::handle_get(const IConnection::ptr &c, Command &cmd) const
	{
		auto &user = _userMgr.getUserByConnection(c);
		if(!user)
			return send_code(c, cmd, reply::codes::NOT_LOGGED_IN);
		std::vector<std::string> contacts = user->generateContactsNames();
		std::string tmpdata("");
		cmd.code(static_cast<uint32_t>(reply::codes::PENDING_CONTACTS));
		while (contacts.size() > 0) {
			if (tmpdata.size() + contacts.back().size() + 1 > BUFFER_SIZE - 8) {
				cmd.data(tmpdata);
				c->send(cmd.to_str());
				tmpdata = "";
			}
			if(tmpdata.size() > 0)
				tmpdata = "#" + tmpdata;
			tmpdata = contacts.back() + tmpdata;
			contacts.pop_back();
		}
		cmd.code(static_cast<uint32_t>(reply::codes::SUCCESS_CONTACTS));
		cmd.data(tmpdata);
		c->send(cmd.to_str());
	}

	void CmdHandler::handle_invite(const IConnection::ptr &c, Command &cmd) const
	{
		auto &user = _userMgr.getUserByConnection(c);
		if(!user)
			return send_code(c, cmd, reply::codes::NOT_LOGGED_IN);
		if(_userMgr.isInCall(user))
			return send_code(c, cmd, reply::codes::ALREADY_IN_CALL);
		std::vector<std::string> inviteData;
		splitString(inviteData, cmd.data(),
		[](char c){
			return c == '#';
		});
		if(inviteData.size() != 2)
			return send_code(c, cmd, reply::codes::BAD_COMMAND);
		unsigned short callerport = 0;
		try {
			callerport = stous(inviteData[1]);
		} catch(const std::exception &e) {
			return send_code(c, cmd, reply::codes::BAD_COMMAND);
		}
		auto &invited = _userMgr.getUserByName(inviteData[0]);
		if(!invited || !user->isContact(invited))
			return send_code(c, cmd, reply::codes::NOT_IN_CONTACT_LIST);
		if(!invited->connected())
			return send_code(c, cmd, reply::codes::USER_NOT_CONNECTED);
		if(_userMgr.isInCall(invited))
			return send_code(c, cmd, reply::codes::USER_ALREADY_IN_CALL);
		if(auto invitedcon = invited->connection().lock()){
			_userMgr.createCall(user, invited, callerport);
			cmd.code(static_cast<uint32_t>(reply::codes::INVITE_CALL));
			cmd.data(user->name());
			std::cout << user->name() << " invited " << invited->name() <<
			" in a call" << std::endl;
			return invitedcon->send(cmd.to_str());
		}
		send_code(c, cmd, reply::codes::REJECTED);
	}

	void CmdHandler::handle_accept(const IConnection::ptr &c, Command &cmd) const
	{
		auto &user = _userMgr.getUserByConnection(c);
		if(!user)
			return send_code(c, cmd, reply::codes::NOT_LOGGED_IN);
		unsigned short calleeport = 0;
		try {
			calleeport = stous(cmd.data());
		} catch(const std::exception &e) {
			return send_code(c, cmd, reply::codes::BAD_COMMAND);
		}
		auto &call = _userMgr.getCall(user);
		if(!call || call->callee() != user || call->ready())
			return send_code(c, cmd, reply::codes::NOT_INVITED);
		if(auto callercon = call->caller()->connection().lock()){
			cmd.code(static_cast<uint32_t>(reply::codes::ACCEPTED));
			cmd.data(c->ip() + "#" + cmd.data());
			callercon->send(cmd.to_str());
			cmd.code(static_cast<uint32_t>(reply::codes::SUCCESS_CALL));
			cmd.data(callercon->ip() + "#" + std::to_string(call->callerPort()));
			c->send(cmd.to_str());
			call->start(calleeport);
		} else {
			send_code(c, cmd, reply::codes::LEAVE_CALL);
			_userMgr.deleteCall(call);
		}

	}

	void CmdHandler::handle_hangup(const IConnection::ptr &c, Command &cmd) const
	{
		auto &user = _userMgr.getUserByConnection(c);
		if(!user)
			return send_code(c, cmd, reply::codes::NOT_LOGGED_IN);
		auto &call = _userMgr.getCall(user);
		if(!call)
			return send_code(c, cmd, reply::codes::NOT_IN_CALL);
		auto &other = ((call->caller() == user)? call->callee() : call->caller());
		if(auto othercon = other->connection().lock())
			send_code(othercon, cmd, reply::codes::LEAVE_CALL);
		_userMgr.deleteCall(call);
		std::cout << user->name() << " hung up the call with " <<
		other->name() << std::endl;
		send_code(c, cmd, reply::codes::CALL_ENDED);
	}

	void CmdHandler::handle_reject(const IConnection::ptr &c, Command &cmd) const
	{
		auto &user = _userMgr.getUserByConnection(c);
		if(!user)
			return send_code(c, cmd, reply::codes::NOT_LOGGED_IN);
		auto &call = _userMgr.getCall(user);
		if(!call || call->callee() != user)
			return send_code(c, cmd, reply::codes::NOT_INVITED);
		if(auto callercon = call->caller()->connection().lock())
			send_code(callercon, cmd, reply::codes::REJECTED);
		std::cout << user->name() << " rejected a call from " <<
		call->caller()->name() << std::endl;
		send_code(c, cmd, reply::codes::SUCCESS_REJECT);
		_userMgr.deleteCall(call);
	}

	void CmdHandler::handle_disconnect(const IConnection::ptr &c, Command &cmd) const
	{
		auto &user = _userMgr.getUserByConnection(c);
		if(user){
			auto &call = _userMgr.getCall(user);
			if(call && call->ready()){
				auto &other = ((call->caller() == user)? call->callee() : call->caller());
				if(auto othercon = other->connection().lock())
					send_code(othercon, cmd, reply::codes::LEAVE_CALL);
				_userMgr.deleteCall(call);
			} else if(call && call->callee() == user){
				if(auto con = call->caller()->connection().lock())
					send_code(con, cmd, reply::codes::REJECTED);
				_userMgr.deleteCall(call);
			}
			user->disconnect();
			std::cout << "User " << user->name() << " (" << c->ip()
			<< ") disconnected" << std::endl;
		} else {
			std::cout << "Connection from " << c->ip() << " disconnected" << std::endl;
		}
		c->manager().stop(c);
	}

} /* Babel */
