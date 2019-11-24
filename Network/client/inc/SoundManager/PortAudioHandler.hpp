/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef PORT_AUDIO_HANDLER_HPP
#define PORT_AUDIO_HANDLER_HPP

#include "common.hpp"
#include <QObject>

namespace babel {
	class SoundManager;

	class PortAudioHandler : public QObject {
		Q_OBJECT
	public:
		PortAudioHandler(SoundManager &parent);

	private:
		SoundManager &_parent;
	};
}

#endif /* end of include guard: PORT_AUDIO_HANDLER_HPP */
