/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** User definition
*/

#ifndef BABEL_USER_HPP
#define BABEL_USER_HPP

#include <string>
#include <set>
#include <vector>
#include <iostream>
#include "IConnection.hpp"

namespace Babel {

	class User : public std::enable_shared_from_this<User> {
	public:
		typedef std::shared_ptr<User> ptr;
		typedef std::weak_ptr<User> wk_ptr;
		~User();

		static ptr create(const std::string &name, const std::string &password);

		const std::string &name() const;

		bool verifyPassword(const std::string &supplied) const;
		bool connected() const;
		void connect(const IConnection::wk_ptr &connection);
		void disconnect();
		const IConnection::wk_ptr &connection() const;

		bool isContact(const std::string &name) const;
		bool isContact(const wk_ptr &contact) const;
		bool addContact(const wk_ptr &newContact);
		bool delContact(const wk_ptr &toDel);
		const std::set<wk_ptr, std::owner_less<wk_ptr>> &contacts() const;
		std::vector<std::string> generateContactsNames() const;
		void generateContactsNames(std::vector<std::string> &to_fill) const;

	private:
		User(const std::string &name, const std::string &password);
		std::string _name;
		std::string _password;
		bool _connected;
		IConnection::wk_ptr _connection;
		std::set<wk_ptr, std::owner_less<wk_ptr>> _contacts;

	};

} /* Babel */

#endif
