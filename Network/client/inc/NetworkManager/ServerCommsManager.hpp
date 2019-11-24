/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef SERVER_COMMS_MANAGER_HPP
#define SERVER_COMMS_MANAGER_HPP

#include "QNetworkClientTcp.hpp"
#include <unistd.h>

namespace babel {
	class NetworkManager;

	class ServerCommsManager : public QObject {
		Q_OBJECT
	public:
		ServerCommsManager(NetworkManager &parent);
		~ServerCommsManager();

		void writeTCP(std::uint32_t cmdCode, std::uint32_t size, std::array<char, BUFFER_SIZE> &data);
		void writeTCP(t_packet &);
		void handleCmd(t_packet &);
		void leave();
		bool connectToTcpHost(const std::string& ip, int port);
		QNetworkClientTcp &getQNetworkClientTcp();

	signals:
		void AuthentificationOK(uint32_t code);
		void AuthentificationFailed(uint32_t code);
		void addContactList(std::vector<QString>);
		void callFailed(uint32_t code);
		void initCall(char *ip, int port);
		void IncomingCall(std::string);
		void addContactAccepted(std::string);
		uint32_t getUdpPort();

	private slots:
		void getContactsRequest();
		void slotRegisterRequest(QString name, QString password);
		void slotLoginRequest(QString name, QString password);
		void slotAddContactRequest(QString name);
		void slotRemoveContactRequest(QString name);
		void slotCallRequest(QString name);
		void slotEndCallRequest();
		void slotCallConfirmation();
		void slotCallRefused();

	private:
		NetworkManager &_parent;
		QNetworkClientTcp _networkTcp;
		std::unordered_map<std::uint32_t, std::function<void(t_packet)>> _commands;

		void CMD_SUCCESS(t_packet &data);

		void CMD_AUTH_SUCCESS(t_packet &data);
		void CMD_CONTACT_ADD_SUCCESS(t_packet &data);
		void CMD_CONTACT_DELETE_SUCCESS(t_packet &data);
		void CMD_GOT_CONTACTS_SUCCESS(t_packet &data);

		//void CMD_CALL_REQUEST_SUCCESS(t_packet &data);
		void CMD_CALL_SUCCESS(t_packet &data);
		void CMD_CALL_ENDED_SUCCESS(t_packet &data);

		void CMD_SERVER_ERROR(t_packet &data);
		void CMD_FAILURE(t_packet &data);

		void CMD_AUTH_FAILED(t_packet &data);
		void CMD_CONTACT_FAILED(t_packet &data);
		void CMD_CALL_FAILED(t_packet &data);
		void CMD_INVALID_CALL_CMD(t_packet &data);
		void CMD_CONNECTION_FAILED(t_packet &data);

		void CMD_INCOMING_CALL(t_packet &data);
		void CMD_CLOSING_CALL(t_packet &data);
	};
}

#endif /* end of include guard: SERVER_COMMS_MANAGER_HPP */
