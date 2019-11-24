/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "SoundManager.hpp"
#include "ClientManager.hpp"

//RECOIT BUFFER A REMPLIR ET BUFFER A LIRE

namespace babel {
	SoundManager::SoundManager(ClientManager &parent)
		: _parent(parent)
		, _portAudio(*this)
		, _opus(*this)
	{}

	ClientManager &SoundManager::getRoot()
	{
		return _parent;
	}

	void SoundManager::slotHandleReceivedAudio(QByteArray data)
	{
		std::cout << "SoundManager handle received audio" << std::endl;
		//DECODED = CODEC.DECODE_AUDIO(DATA)
		//_portAudio.PLAY(DECODED)
	}

	void SoundManager::slotHandleRecordedAudio(QByteArray data)
	{
		std::cout << "Soundmanager handlerecorded audio" << std::endl;
		//ENCODED = CODEC.ENCODE_AUDIO(DATA?)
		//emit sendVoice(ENCODED)
	}

	void SoundManager::slotInitCall()
	{
		//INITIALIZE PORTAUDIO ETC...
	}
}
