/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Iconnection Definition
*/

#ifndef ICONNECTION_HPP
#define ICONNECTION_HPP

#include <memory>

namespace Babel {
	class ConnectionMgr;

	class IConnection {
	public:
		typedef std::shared_ptr<IConnection> ptr;
		typedef std::weak_ptr<IConnection> wk_ptr;

		virtual ~IConnection(){};
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual ConnectionMgr &manager() = 0;
		virtual const std::string &ip() const = 0;
		virtual void send(const std::string& cmd) = 0;
	};

} /* Babel */


#endif
