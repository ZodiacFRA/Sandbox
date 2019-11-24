/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef Q_NETWORK_CLIENT_TCP_HPP
#define Q_NETWORK_CLIENT_TCP_HPP

#include "networkCommon.hpp"
#include "common.hpp"

namespace babel {
	class ServerCommsManager;

	class QNetworkClientTcp : public QObject {
		Q_OBJECT
	public:
		explicit QNetworkClientTcp(ServerCommsManager &serverCommsManager, QObject *parent = nullptr);
		bool connectToTcpHost(const std::string& ip, int port);
		bool write(t_packet&);
		bool disconnect();
		void packetToCharPtr(t_packet &packet, std::string &string);
		void charPtrToPacket(char *data, t_packet &packet);

	public slots:
		bool slotConnected(void);
		bool slotRead();
		bool slotIsConnected();

	private:
		ServerCommsManager &_serverCommsManager;

		std::shared_ptr<QTcpSocket> _socket;
		QDataStream _in;
	};

}


#endif /* end of include guard: Q_NETWORK_CLIENT_TCP_HPP */
