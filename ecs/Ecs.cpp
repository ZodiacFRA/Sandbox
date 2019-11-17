//
// Created by seb on 16/11/2019.
//

#include "Ecs.hpp"

Ecs::Ecs() {
	this->device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			      false, false, false, &keyboardEvent);

	device->setWindowCaption(L"Le jeux de ses morts");
	this->driver = device->getVideoDriver();
	this->smgr = device->getSceneManager();
	this->guienv = device->getGUIEnvironment();
}