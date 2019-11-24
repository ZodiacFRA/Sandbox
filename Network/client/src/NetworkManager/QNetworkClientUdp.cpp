/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "QNetworkClientUdp.hpp"
#include "ServerCommsManager.hpp"

namespace babel {
	QNetworkClientUdp::QNetworkClientUdp(NetworkManager &networkManager, char *ip, int port, QObject *parent)
		: QObject(parent)
		, _clientCommsManager(networkManager)
		, _socket(std::make_shared<QUdpSocket>())
		, _ip(ip)
		, _port(port)
		, _contactIp(nullptr)
		, _contactPort(-1)
	{
		QObject::connect(_socket.get(), SIGNAL(readyRead()), this, SLOT(slotRead()));
	}

	void QNetworkClientUdp::bindUdp(uint32_t port)
	{
		_socket->close();
		_socket->bind(QHostAddress::Any);
		_port = _socket->localPort();
		std::cout << port << std::endl;
	}

	void QNetworkClientUdp::slotRead()
	{
		if (_contactIp == nullptr || _contactPort == -1) {
			std::cerr << "GIVE CONTACT BEFORE RECEIVING" << std::endl;
			return;
		}
		while (_socket->hasPendingDatagrams()) {
			QByteArray buffer;
			//QHostAddress sender;
			//quint16 senderPort;
			buffer.resize(_socket->pendingDatagramSize());
			_socket->readDatagram(buffer.data(), buffer.size()/*, &sender, &senderPort*/);
			std::string test(buffer.data());
			std::cout << _port << " RECEIVED: " << test << std::endl;
			emit audioPacketReceived(buffer);
		}
	}

	void QNetworkClientUdp::slotSend(QByteArray data)
	{
		if (_contactIp == nullptr || _contactPort == -1) {
			std::cerr << "GIVE CONTACT BEFORE BROADCASTING" << std::endl;
			return;
		}
		QHostAddress myHost(QString::fromStdString(_contactIp));
		_socket->writeDatagram(data.data(), data.size(), myHost, _contactPort);
	}

	void QNetworkClientUdp::slotCloseCall()
	{
		_contactIp = nullptr;
		_contactPort = -1;
	}

	void QNetworkClientUdp::slotInitCall(char *ip, int port)
	{
		_contactIp = ip;
		_contactPort = port;
		std::cout << "DEBUT CALL UDP" << std::endl;
		slotSend(QByteArray("hello"));
	}

	uint32_t QNetworkClientUdp::slotGetUdpPort()
	{
		return _port;
	}
}
