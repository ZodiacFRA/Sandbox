/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef BABEL_CLIENT_HPP
#define BABEL_CLIENT_HPP

#include "common.hpp"
#include "GUIManager.hpp"
#include "NetworkManager.hpp"
#include "SoundManager.hpp"

namespace babel {
	class ClientManager : public QObject {
		Q_OBJECT
	public:
		ClientManager(char **argv, QObject *parent);

		const int run();

		GUIManager &getGUI();
		NetworkManager &getNetwork();
		SoundManager &getSound();
	private:
		GUIManager _GUI;
		NetworkManager _Network;
		SoundManager _Sound;

		char **_params;
	};
}

#endif /* end of include guard: client_HPP */
