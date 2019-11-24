/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include "common.hpp"
#include "PortAudioHandler.hpp"
#include "OpusHandler.hpp"

namespace babel {
	class ClientManager;

	class SoundManager : public QObject {
		Q_OBJECT
	public:
		SoundManager(ClientManager &parent);

		ClientManager &getRoot();

	//signals:
		//void sendEncodedVoice(QByteArray data);

	private slots:
		void slotInitCall();
		void slotHandleReceivedAudio(QByteArray data);
		void slotHandleRecordedAudio(QByteArray data);

	private:
		ClientManager &_parent;
		PortAudioHandler _portAudio;
		OpusHandler _opus;
	};
}

#endif /* end of include guard: SOUND_MANAGER_HPP */
