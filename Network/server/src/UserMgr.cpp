/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** User Manager implementation
*/

#include "UserMgr.hpp"
#include "helpers.hpp"
#include <algorithm>
#include <utility>

namespace Babel {

	UserMgr::Call::ptr UserMgr::Call::create(const User::ptr &caller, const User::ptr &callee,
		unsigned short callerPort)
	{
		return ptr(new Call(caller, callee, callerPort));
	}

	UserMgr::Call::Call(const User::ptr &caller, const User::ptr &callee,
		unsigned short callerPort)
	: _caller(caller),
	_callee(callee),
	_callerPort(callerPort),
	_calleePort(0),
	_ready(false)
	{}

	UserMgr::Call::~Call()
	{}

	bool UserMgr::Call::ready() const
	{
		return _ready;
	}

	const User::ptr &UserMgr::Call::caller() const
	{
		return _caller;
	}

	const User::ptr &UserMgr::Call::callee() const
	{
		return _callee;
	}

	unsigned short UserMgr::Call::callerPort() const
	{
		return _callerPort;
	}

	unsigned short UserMgr::Call::calleePort() const
	{
		return _calleePort;
	}

	bool UserMgr::Call::start(unsigned short calleePort)
	{
		if(!_ready){
			_calleePort = calleePort;
			_ready = true;
			return true;
		}
		return false;
	}

	UserMgr::UserMgr()
	: _nullUser(nullptr),
	_nullCall(nullptr),
	_users(),
	_calls()
	{}

	UserMgr::~UserMgr()
	{}

	bool UserMgr::createUser(const std::string &name, const std::string &password)
	{
		if(!exists(name)){
			_users.insert(User::create(name, password));
			std::cout << "User " << name << " created" << std::endl;
			return true;
		}
		return false;
	}

	bool UserMgr::exists(const std::string &name) const
	{
		return std::count_if(_users.begin(), _users.end(),
		[&name](const User::ptr &p){
			return p->name() == name;
		}) > 0;
	}

	const User::ptr &UserMgr::getUserByName(const std::string &name) const
	{
		auto res = std::find_if(_users.begin(), _users.end(),
		[&name](const User::ptr &p){
			return p->name() == name;
		});
		return ((res != _users.end())? *res : _nullUser);
	}

	const User::ptr &UserMgr::getUserByConnection(const IConnection::wk_ptr &c) const
	{
		auto res = std::find_if(_users.begin(), _users.end(),
		[&c](const User::ptr &p){
			return equals(p->connection(), c);
		});
		return ((res != _users.end())? *res : _nullUser);
	}

	bool UserMgr::isInCall(const User::ptr &user) const
	{
		return std::find_if(_calls.begin(), _calls.end(),
		[&user](auto &call){
			return call->caller() == user || call->callee() == user;
		}) != _calls.end();
	}

	const UserMgr::Call::ptr &UserMgr::getCall(const User::ptr &user) const
	{
		auto res = std::find_if(_calls.begin(), _calls.end(),
		[&user](auto &call){
			return call->caller() == user || call->callee() == user;
		});
		return ((res != _calls.end())? *res : _nullCall);
	}

	void UserMgr::startCall(const UserMgr::Call::ptr &call, unsigned short calleePort)
	{
		auto res = std::find(_calls.begin(), _calls.end(), call);
		if(res == _calls.end())
			throw std::runtime_error("Calls are not supposed to be created outside of manager");
		(*res)->start(calleePort);
	}

	void UserMgr::createCall(const User::ptr &caller, const User::ptr &callee,
		unsigned short callerport)
	{
		_calls.push_back(std::move(Call::create(caller, callee, callerport)));
	}

	void UserMgr::deleteCall(const UserMgr::Call::ptr &call)
	{
		auto res = std::find(_calls.begin(), _calls.end(), call);
		if(res == _calls.end()){
			std::cerr << "Error: Calls are not supposed to be created outside of manager" << std::endl;
			return;
		}
		_calls.erase(res);
	}


} /* Babel */
