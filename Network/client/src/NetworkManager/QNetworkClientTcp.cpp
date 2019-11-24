/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "QNetworkClientTcp.hpp"
#include "ServerCommsManager.hpp"

namespace babel {
	QNetworkClientTcp::QNetworkClientTcp(ServerCommsManager &ServerCommsManager, QObject *parent)
		: QObject(parent)
		, _serverCommsManager(ServerCommsManager)
		, _socket(std::make_shared<QTcpSocket>())
	{
		_in.setDevice(_socket.get());
		_in.setVersion(QDataStream::Qt_5_11);

		QObject::connect(_socket.get(), SIGNAL(connected()), this, SLOT(slotConnected()));
		QObject::connect(_socket.get(), SIGNAL(readyRead()), this, SLOT(slotRead()));
	}

	bool QNetworkClientTcp::connectToTcpHost(const std::string& ip, int port)
	{
		_socket->abort();
		_socket->connectToHost(QString::fromStdString(ip), port);
		return true;
	}

	bool QNetworkClientTcp::disconnect()
	{
		_socket->disconnectFromHost();
		return true;
	}

	void QNetworkClientTcp::packetToCharPtr(t_packet &packet, std::string &string)
	{
		char *under = &string[0];
		uint32_t *ptr = reinterpret_cast<uint32_t *>(under);
		*ptr = packet.cmdCode;
		ptr = reinterpret_cast<uint32_t *>(under + 4);
		*ptr = packet.size;
		std::strncpy(under + 8, packet.data.data(), packet.size);
	}

	void QNetworkClientTcp::charPtrToPacket(char *data, t_packet &packet)
	{
		uint32_t *ptr = reinterpret_cast<uint32_t *>(data);
		packet.cmdCode = *ptr;
		ptr = reinterpret_cast<uint32_t *>(data + 4);
		packet.size = *ptr;
		if (packet.size != 0)
			std::strncpy(packet.data.data(), data + 8, packet.size);
	}

	bool QNetworkClientTcp::write(t_packet& packet)
	{
		if (_socket->state() == QAbstractSocket::ConnectedState) {
			auto len = strlen(packet.data.data()) + 1;
			std::string string((len + 8), '\0');
			packetToCharPtr(packet, string);
			QByteArray toSend(string.data(), len + 8);
			_socket->write(toSend);
			return true;
		}
		return false;
	}

	bool QNetworkClientTcp::slotIsConnected()
	{
		if (_socket->state() == QAbstractSocket::ConnectedState)
			return true;
		return false;
	}

	bool QNetworkClientTcp::slotRead()
	{
		std::cout << "RECU 1 PACKET" << std::endl;
		t_packet packet;
		charPtrToPacket(_socket->read(sizeof(t_packet)).data(), packet);
		_serverCommsManager.handleCmd(packet);
		return true;
	}

	bool QNetworkClientTcp::slotConnected()
	{
		std::cout << COLOR_GREEN << "------> Connected to server" << COLOR_RESET << std::endl;
		return true;
	}
}
