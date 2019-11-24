/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** User implementation
*/

#include "User.hpp"
#include <algorithm>

namespace Babel {

	User::User(const std::string &name, const std::string &password)
	: _name(name),
	_password(password),
	_connected(false),
	_connection(),
	_contacts()
	{}

	User::~User()
	{}

	User::ptr User::create(const std::string &name, const std::string &password)
	{
		return ptr(new User(name, password));
	}

	const std::string &User::name() const
	{
		return _name;
	}

	bool User::verifyPassword(const std::string &supplied) const
	{
		return supplied == _password;
	}

	bool User::connected() const
	{
		return _connected;
	}

	void User::connect(const IConnection::wk_ptr &connection)
	{
		if (!connection.expired()){
			_connected = true;
			_connection = connection;
		} else {
			std::cout << "User " << _name << ": connection already expired" << std::endl;
		}
	}

	void User::disconnect()
	{
		_connected = false;
		_connection.reset();
	}

	const IConnection::wk_ptr &User::connection() const
	{
		return _connection;
	}

	bool User::isContact(const std::string &name) const
	{
		return std::find_if(_contacts.begin(), _contacts.end(),
		[&name](const auto &c){
			if(auto tmp = c.lock())
				return tmp->name() == name;
			return false;
		}) != _contacts.end();
	}

	bool User::isContact(const wk_ptr &contact) const
	{
		return _contacts.find(contact) != _contacts.end();
	}

	bool User::addContact(const wk_ptr &newContact)
	{
		if(!isContact(newContact) && !newContact.expired()){
			_contacts.insert(newContact);
			return true;
		}
		return false;
	}

	bool User::delContact(const wk_ptr &toDel)
	{
		if(isContact(toDel)){
			_contacts.erase(toDel);
			return true;
		}
		return false;
	}

	const std::set<User::wk_ptr, std::owner_less<User::wk_ptr>> &User::contacts() const
	{
		return _contacts;
	}

	std::vector<std::string> User::generateContactsNames() const
	{
		std::vector<std::string> res;
		generateContactsNames(res);
		return res;
	}

	void User::generateContactsNames(std::vector<std::string> &to_fill) const
	{
		for(auto c : _contacts){
			if(auto tmp = c.lock())
				to_fill.push_back(tmp->name());
		}
	}

} /* Babel */
