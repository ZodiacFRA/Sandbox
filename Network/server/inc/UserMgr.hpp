/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** User Manager definition
*/

#ifndef BABEL_USER_MANAGER_HPP
#define BABEL_USER_MANAGER_HPP

#include "User.hpp"

namespace Babel {

	class UserMgr {
	public:
		class Call {
		public:
			typedef std::unique_ptr<Call> ptr;
			static ptr create(const User::ptr &caller, const User::ptr &callee,
				unsigned short callerPort);
			~Call();

			bool ready() const;

			const User::ptr &caller() const;
			const User::ptr &callee() const;
			unsigned short callerPort() const;
			unsigned short calleePort() const;

			bool start(unsigned short calleePort);

		private:
			Call(const User::ptr &caller, const User::ptr &callee,
				unsigned short callerPort);
			const User::ptr &_caller;
			const User::ptr &_callee;
			unsigned short _callerPort;
			unsigned short _calleePort;
			bool _ready;
		};

	public:
		UserMgr();
		~UserMgr();

		bool createUser(const std::string &name, const std::string &password);
		bool exists(const std::string &name) const;
		const User::ptr &getUserByName(const std::string &name) const;
		const User::ptr &getUserByConnection(const IConnection::wk_ptr &c) const;

		bool isInCall(const User::ptr &user) const;
		const Call::ptr &getCall(const User::ptr &user) const;
		void startCall(const Call::ptr &call, unsigned short calleePort);
		void createCall(const User::ptr &caller, const User::ptr &callee,
			unsigned short callerport);
		void deleteCall(const Call::ptr &call);

	private:
		User::ptr _nullUser;
		Call::ptr _nullCall;
		std::set<User::ptr> _users;
		std::vector<Call::ptr> _calls;
	};

} /* Babel */



#endif
