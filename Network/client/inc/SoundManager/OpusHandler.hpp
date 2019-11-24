/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef OPUS_HANDLER_HPP
#define OPUS_HANDLER_HPP

#include "common.hpp"
#include <QObject>

namespace babel {
	class SoundManager;

	class OpusHandler : public QObject {
		Q_OBJECT
	public:
		OpusHandler(SoundManager &parent);

	private:
		SoundManager &_parent;
	};
}

#endif /* end of include guard: OPUS_HANDLER_HPP */
