/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "ClientManager.hpp"

namespace babel {
	ClientManager::ClientManager(char **params, QObject *parent)
		: QObject(parent)
		, _GUI(*this, parent)
		, _Network(*this, params)
		, _Sound(*this)
		, _params(params)
	{
		//GUI TO TCP
		connect(_GUI.getWindow("LoginWindow"), SIGNAL (registerRequest(QString, QString)), &_Network.getServerComms(), SLOT(slotRegisterRequest(QString, QString)));
		connect(_GUI.getWindow("LoginWindow"), SIGNAL (loginRequest(QString, QString)), &_Network.getServerComms(), SLOT(slotLoginRequest(QString, QString)));
		connect(_GUI.getWindow("LoginWindow"), SIGNAL (connectionStateRequest()), &_Network.getServerComms().getQNetworkClientTcp(), SLOT(slotIsConnected()));
		connect(_GUI.getWindow("LoginWindow"), SIGNAL (loggedIn()), &_Network.getServerComms(), SLOT(getContactsRequest()));
		connect(_GUI.getWindow("AddContactWindow"), SIGNAL (addContactRequest(QString)), &_Network.getServerComms(), SLOT(slotAddContactRequest(QString)));
		connect(_GUI.getWindow("MainWindow"), SIGNAL (callRequest(QString)), &_Network.getServerComms(), SLOT(slotCallRequest(QString)));
		connect(_GUI.getWindow("MainWindow"), SIGNAL (endCallRequest()), &_Network.getServerComms(), SLOT(slotEndCallRequest()));
		connect(_GUI.getWindow("MainWindow"), SIGNAL (requestConfirmationForContactDeletion(QString)), &_Network.getServerComms(), SLOT(slotRemoveContactRequest(QString)));
		connect(_GUI.getWindow("MainWindow"), SIGNAL (callConfirmation()), &_Network.getServerComms(), SLOT(slotCallConfirmation()));
		connect(_GUI.getWindow("MainWindow"), SIGNAL (callRefused()), &_Network.getServerComms(), SLOT(slotCallRefused()));

		//TCP TO GUI
		connect(&_Network.getServerComms(), SIGNAL (AuthentificationOK(uint32_t)), _GUI.getWindow("LoginWindow"), SLOT(slotAuthentificationDone(uint32_t)));
		connect(&_Network.getServerComms(), SIGNAL (AuthentificationFailed(uint32_t)), _GUI.getWindow("LoginWindow"), SLOT(slotAuthentificationFailed(uint32_t)));
		connect(&_Network.getServerComms(), SIGNAL (addContactList(std::vector<QString>)), _GUI.getWindow("MainWindow"), SLOT(slotAddServerContacts(std::vector<QString>)));
		connect(&_Network.getServerComms(), SIGNAL (callFailed(uint32_t)), _GUI.getWindow("MainWindow"), SLOT(slotCallFailed(uint32_t)));
		connect(&_Network.getServerComms(), SIGNAL (addContactAccepted(std::string)), _GUI.getWindow("MainWindow"), SLOT(slotAddContactAccepted(std::string)));
		connect(&_Network.getServerComms(), SIGNAL (IncomingCall(std::string)), _GUI.getWindow("MainWindow"), SLOT(slotIncomingCall(std::string)));

		//TCP TO UDP
		connect(&_Network.getServerComms(), SIGNAL (initCall(char *, int)), &_Network.getClientComms(), SLOT(slotInitCall(char *, int)));

		//TCP TO AUDIO
		//connect(&_Network.getServerComms(), SIGNAL (initCall(char *, int)), &_Sound, SLOT(slotInitCall()));

		//UDP TO AUDIO
		connect(&_Network.getClientComms(), SIGNAL (audioPacketReceived(QByteArray)), &_Sound, SLOT(slotHandleReceivedAudio(QByteArray)));

		//AUDIO TO UDP
		//connect(&_Sound, SIGNAL (sendEncodedVoice(DATA)), &_Network.getClientComms(), SLOT(sendVoice(DATA)));
	}

	const int ClientManager::run()
	{
		if (_GUI.start() == SUCCESS)
			return qApp->exec();
		return FAILURE;
	}

	GUIManager &ClientManager::getGUI()
	{
		return _GUI;
	}

	NetworkManager &ClientManager::getNetwork()
	{
		return _Network;
	}

	SoundManager &ClientManager::getSound()
	{
		return _Sound;
	}
}
