/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef Q_NETWORK_CLIENT_UDP_HPP
#define Q_NETWORK_CLIENT_UDP_HPP

#include "networkCommon.hpp"
#include "common.hpp"

namespace babel {
	class NetworkManager;

	class QNetworkClientUdp : public QObject {
		Q_OBJECT
	public:
		explicit QNetworkClientUdp(NetworkManager &networkManager, char *ip, int port, QObject *parent = nullptr);
		void bindUdp(uint32_t port);

	signals:
		void audioPacketReceived(QByteArray data); //TO networkManager

	public slots:
		void slotRead();
		void slotSend(QByteArray data);
		void slotCloseCall();
		void slotInitCall(char *ip, int port);
		uint32_t slotGetUdpPort();

	private:
		NetworkManager &_clientCommsManager;

		std::shared_ptr<QUdpSocket> _socket;

		char *_ip;
		int _port;

		char *_contactIp;
		int _contactPort;
	};

}


#endif /* end of include guard: Q_NETWORK_CLIENT_UDP_HPP */
