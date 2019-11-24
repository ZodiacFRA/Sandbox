/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "ServerCommsManager.hpp"
#include "NetworkManager.hpp"

namespace babel {
	ServerCommsManager::ServerCommsManager(NetworkManager &parent)
		: _parent(parent)
		, _networkTcp(*this)
		, _commands({
		//SUCCESS
			{200,	[&](t_packet data) {CMD_SUCCESS(data);}},

			{210,	[&](t_packet data) {CMD_AUTH_SUCCESS(data);}},
			{211,	[&](t_packet data) {CMD_AUTH_SUCCESS(data);}},

			{220,	[&](t_packet data) {CMD_CONTACT_ADD_SUCCESS(data);}},
			{221,	[&](t_packet data) {CMD_CONTACT_DELETE_SUCCESS(data);}},
			{222,	[&](t_packet data) {CMD_GOT_CONTACTS_SUCCESS(data);}},

			{230,	[&](t_packet data) {CMD_CALL_SUCCESS(data);}},
			{231,	[&](t_packet data) {CMD_CALL_SUCCESS(data);}},
			{232,	[&](t_packet data) {CMD_CALL_ENDED_SUCCESS(data);}},

		//ERRORS
			{500,	[&](t_packet data) {CMD_SERVER_ERROR(data);}},

			{400,	[&](t_packet data) {CMD_FAILURE(data);}},

			{410,	[&](t_packet data) {CMD_AUTH_FAILED(data);}},
			{411,	[&](t_packet data) {CMD_AUTH_FAILED(data);}},

			{420,	[&](t_packet data) {CMD_CONTACT_FAILED(data);}},
			{421,	[&](t_packet data) {CMD_CONTACT_FAILED(data);}},
			{422,	[&](t_packet data) {CMD_CONTACT_FAILED(data);}},

			{430,	[&](t_packet data) {CMD_CALL_FAILED(data);}},
			{431,	[&](t_packet data) {CMD_CALL_FAILED(data);}},
			{432,	[&](t_packet data) {CMD_CALL_FAILED(data);}},

			{450,	[&](t_packet data) {CMD_INVALID_CALL_CMD(data);}},
			{451,	[&](t_packet data) {CMD_INVALID_CALL_CMD(data);}},
			{452,	[&](t_packet data) {CMD_INVALID_CALL_CMD(data);}},

			{460,	[&](t_packet data) {CMD_CONNECTION_FAILED(data);}},
			{461,	[&](t_packet data) {CMD_CONNECTION_FAILED(data);}},
			{462,	[&](t_packet data) {CMD_CONNECTION_FAILED(data);}},

			{700,	[&](t_packet data) {CMD_INCOMING_CALL(data);}},
			{701,	[&](t_packet data) {CMD_CLOSING_CALL(data);}}
		})
	{}

	ServerCommsManager::~ServerCommsManager()
	{
		//leave();
	}

	void ServerCommsManager::writeTCP(std::uint32_t cmdCode, std::uint32_t size, std::array<char, BUFFER_SIZE> &data)
	{
		t_packet packet;
		packet.cmdCode = cmdCode;
		packet.size = size;
		packet.data = data;
		_networkTcp.write(packet);
	}

	void ServerCommsManager::writeTCP(t_packet &data)
	{
		_networkTcp.write(data);
	}

	void ServerCommsManager::handleCmd(t_packet &data)
	{
		if (_commands[data.cmdCode]) {
			_commands[data.cmdCode](data);
		} else
			std::cout << "---> Unknown Command" << std::endl;
	}

	bool ServerCommsManager::connectToTcpHost(const std::string& ip, int port)
	{
		_networkTcp.connectToTcpHost(ip, port);
		return SUCCESS;
	}

	QNetworkClientTcp &ServerCommsManager::getQNetworkClientTcp()
	{
		return _networkTcp;
	}
}
