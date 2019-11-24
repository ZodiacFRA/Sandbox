/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "NetworkManager.hpp"
#include "ClientManager.hpp"

namespace babel {
	NetworkManager::NetworkManager(ClientManager &parent, char **params)
		: _parent(parent)
		, _clientCommsManager(*this, params[1], std::atoi(params[2]))
		, _serverCommsManager(*this)
		, _ip(params[1])
		, _port(std::atoi(params[2]))
	{
		_serverCommsManager.connectToTcpHost(_ip, _port);
		connect(&_serverCommsManager, SIGNAL (getUdpPort()), &_clientCommsManager, SLOT(slotGetUdpPort()));

	}

	ClientManager &NetworkManager::getRoot()
	{
		return _parent;
	}

	ServerCommsManager &NetworkManager::getServerComms()
	{
		return _serverCommsManager;
	}

	QNetworkClientUdp &NetworkManager::getClientComms()
	{
		return _clientCommsManager;
	}
}
