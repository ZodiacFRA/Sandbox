/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "ServerCommsManager.hpp"
#include "NetworkManager.hpp"

namespace babel {
	void ServerCommsManager::CMD_SUCCESS(t_packet &data)
	{
		std::cout << COLOR_GREEN << "---> Success? (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::CMD_AUTH_SUCCESS(t_packet &data)
	{
		std::cout << COLOR_GREEN << "---> Authentification Success (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
		emit AuthentificationOK(data.cmdCode);
	}

	void ServerCommsManager::CMD_CONTACT_ADD_SUCCESS(t_packet &dataPacket)
	{
		int i = 0;
		std::string contact;
		while (dataPacket.data.data()[i] != '\0' && i < dataPacket.size) {
			contact += dataPacket.data.data()[i];
			i++;
		}
		emit addContactAccepted(contact);
		std::cout << COLOR_GREEN << "---> server Contact added! (" << dataPacket.cmdCode << ")" << COLOR_RESET << std::endl;

	}

	void ServerCommsManager::CMD_CONTACT_DELETE_SUCCESS(t_packet &data)
	{
		std::cout << COLOR_GREEN << "---> server Contact deleted (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::CMD_GOT_CONTACTS_SUCCESS(t_packet &dataPacket)
	{
		std::cout << COLOR_GREEN << "---> Received contacts list (" << dataPacket.cmdCode << ")" << COLOR_RESET << std::endl;
		if (dataPacket.size == 0)
			return;
		int i = 0;
		size_t pos = 0;
		std::string contact;
		std::vector<QString> contacts;
		while (dataPacket.data.data()[i] != '\0' && i < dataPacket.size) {
			contact += dataPacket.data.data()[i];
			i++;
		}
		std::string token;
		while ((pos = contact.find("#")) != std::string::npos) {
			token = contact.substr(0, pos);
			contacts.push_back(QString::fromStdString(token));
			contact.erase(0, pos + 1);
		}
		contacts.push_back(QString::fromStdString(contact));
		emit addContactList(contacts);
	}

	void ServerCommsManager::CMD_CALL_ENDED_SUCCESS(t_packet &data)
	{
		std::cout << COLOR_RED << "---> Your contact stopped the call: (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::CMD_CALL_SUCCESS(t_packet &dataPacket)
	{
		if (dataPacket.size == 0) {
			std::cout << COLOR_RED << "---> Server didn't provide caller's ip and port!" << COLOR_RESET << std::endl;
			return;
		}
		//std::cout << COLOR_RED << "---> le serveur a bien pris en compte votre accptation d'invitation au call: (" << dataPacket.cmdCode << ")" << COLOR_RESET << std::endl;
		int i = 0;
		size_t pos = 0;
		std::string rawData;
		std::vector<std::string> contacts;
		while (dataPacket.data.data()[i] != '\0' && i < dataPacket.size) {
			rawData += dataPacket.data.data()[i];
			i++;
		}
		std::string token;
		while ((pos = rawData.find("#")) != std::string::npos) {
			token = rawData.substr(0, pos);
			rawData.erase(0, pos + 1);
		}
		std::cout << "---> BEGIN CALL" << std::endl;
		emit initCall(&token[0], atoi(&rawData[0]));
	}

	void ServerCommsManager::CMD_SERVER_ERROR(t_packet &data)
	{
		std::cout << COLOR_RED << "---> Internal Server Error: (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::CMD_FAILURE(t_packet &data)
	{
		std::cout << COLOR_RED << "---> Command Failure: (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::CMD_AUTH_FAILED(t_packet &data)
	{
		std::cout << COLOR_RED << "---> Authentification Failed (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
		emit AuthentificationFailed(data.cmdCode);
	}

	void ServerCommsManager::CMD_CONTACT_FAILED(t_packet &data)
	{
		std::cout << COLOR_RED << "---> Contact management failed (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::CMD_CALL_FAILED(t_packet &data)
	{
		std::cout << COLOR_RED << "---> Call failed (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
		emit callFailed(data.cmdCode);
	}

	void ServerCommsManager::CMD_INVALID_CALL_CMD(t_packet &data)
	{
		std::cout << COLOR_RED << "---> Invalid call command (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::CMD_CONNECTION_FAILED(t_packet &data)
	{
		std::cout << COLOR_RED << "---> Connection failed (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::CMD_INCOMING_CALL(t_packet &dataPacket)
	{
		std::cout << "incoming" << std::endl;
		int i = 0;
		size_t pos = 0;
		std::string contact;
		while (dataPacket.data.data()[i] != '\0' && i < dataPacket.size) {
			contact += dataPacket.data.data()[i];
			i++;
		}
		std::cout << COLOR_GREEN << "---> Call coming (" << dataPacket.cmdCode << ")" << COLOR_RESET << std::endl;
		emit IncomingCall(contact);
	}

	void ServerCommsManager::CMD_CLOSING_CALL(t_packet &data)
	{
		std::cout << COLOR_YELLOW << "---> your contact is closing the call (" << data.cmdCode << ")" << COLOR_RESET << std::endl;
	}
}
