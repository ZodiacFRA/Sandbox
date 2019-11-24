/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "ServerCommsManager.hpp"
#include "NetworkManager.hpp"

namespace babel {

	void ServerCommsManager::leave()
	{
		std::array<char, BUFFER_SIZE> arr;
		writeTCP(42, 0, arr);
		std::cout << "---> Leave" << std::endl;
	}

	void ServerCommsManager::getContactsRequest()
	{
		std::array<char, BUFFER_SIZE> arr;
		writeTCP(23, 0, arr);
		std::cout << COLOR_YELLOW << "------> Contact list request sent!" << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::slotRegisterRequest(QString name, QString password)
	{
		std::string tmp = name.toStdString();
		tmp += '#';
		tmp += password.toStdString();
		std::array<char, BUFFER_SIZE> arr;
		std::copy(tmp.begin(), tmp.end(), arr.data());
		writeTCP(10, tmp.size(), arr);
	}

	void ServerCommsManager::slotLoginRequest(QString name, QString password)
	{
		std::string tmp = name.toStdString();
		tmp += '#';
		tmp += password.toStdString();
		std::array<char, BUFFER_SIZE> arr;
		std::copy(tmp.begin(), tmp.end(), arr.data());
		writeTCP(11, tmp.size(), arr);
	}

	void ServerCommsManager::slotAddContactRequest(QString name)
	{
		std::cout << COLOR_YELLOW << "------> request add contact: " << name.toStdString()  << COLOR_RESET << std::endl;
		std::string tmp = name.toStdString();
		std::array<char, BUFFER_SIZE> arr;
		std::copy(tmp.begin(), tmp.end(), arr.data());
		writeTCP(21, tmp.size(), arr);
	}

	void ServerCommsManager::slotRemoveContactRequest(QString name)
	{
		std::cout << COLOR_YELLOW << "------> request remove contact: " << name.toStdString()  << COLOR_RESET << std::endl;
		std::string tmp = name.toStdString();
		std::array<char, BUFFER_SIZE> arr;
		std::copy(tmp.begin(), tmp.end(), arr.data());
		writeTCP(22, tmp.size(), arr);
	}

	void ServerCommsManager::slotCallRequest(QString name)
	{
		auto port = emit getUdpPort();
		std::string tmp = name.toStdString();
		tmp += '#';
		tmp += port;
		std::array<char, BUFFER_SIZE> arr;
		std::copy(tmp.begin(), tmp.end(), arr.data());
		writeTCP(30, tmp.size(), arr);
		std::cout << COLOR_YELLOW << "------> Call Request: "  << tmp << COLOR_RESET << std::endl;
	}

	void ServerCommsManager::slotEndCallRequest()
	{
		std::cout << "------> End Call Request"  << COLOR_RESET << std::endl;
		std::array<char, BUFFER_SIZE> arr;
		writeTCP(32, 0, arr);
	}

	void ServerCommsManager::slotCallConfirmation()
	{
		std::cout << "------> Confirm Call Request"  << COLOR_RESET << std::endl;
		std::array<char, BUFFER_SIZE> arr;
		writeTCP(31, 0, arr);
	}

	void ServerCommsManager::slotCallRefused()
	{
		std::cout << "------> Deny Call Request"  << COLOR_RESET << std::endl;
		std::array<char, BUFFER_SIZE> arr;
		writeTCP(33, 0, arr);
	}
}
