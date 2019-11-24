/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include "ServerCommsManager.hpp"
#include "QNetworkClientUdp.hpp"

namespace babel {
	class ClientManager;

	class NetworkManager : public QObject {
		Q_OBJECT
	public:
		NetworkManager(ClientManager &parent, char **params);

		ClientManager &getRoot();
		ServerCommsManager &getServerComms();
		QNetworkClientUdp &getClientComms();

	private:
		ClientManager &_parent;
		ServerCommsManager _serverCommsManager;
		QNetworkClientUdp _clientCommsManager;

		char *_ip;
		int _port;

		char *_contactIp;
		int _contactPort;
	};
}

#endif /* end of include guard: NETWORK_MANAGER_HPP */
