/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef NETWORK_COMMON_HPP
#define NETWORK_COMMON_HPP

#include "common.hpp"

#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>

#include <QTcpSocket>
#include <QDataStream>
#include <QtNetwork>
#include <QWidget>
#include <QMessageBox>
#include <QObject>
#include <QTimer>

namespace babel {
	typedef struct s_packet {
		std::uint32_t cmdCode;
		std::uint32_t size;
		std::array<char, BUFFER_SIZE> data;
	} t_packet;
}

#endif /* end of include guard: NETWORK_COMMON_HPP */
