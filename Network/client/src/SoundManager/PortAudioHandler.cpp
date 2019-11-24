/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "PortAudioHandler.hpp"
#include "SoundManager.hpp"

namespace babel {
	PortAudioHandler::PortAudioHandler(SoundManager &parent)
		: _parent(parent)
	{}
}
