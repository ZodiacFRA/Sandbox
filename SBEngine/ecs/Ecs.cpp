//
// Created by seb on 16/11/2019.
//

#include "Ecs.hpp"

Ecs::Ecs() {
	this->keyboardEvent = new KeyboardEvent();
	video::E_DRIVER_TYPE type = video::EDT_OPENGL;

#ifdef	SERVER
	type = video::EDT_NULL;
#elif	CLIENT_MULTI
	type = video::EDT_OPENGL;
#elif	CLIENT_SOLO
	type = video::EDT_OPENGL;
#endif

	this->device = createDevice( type, dimension2d<u32>(1920, 1080), 16,
			      true, true, false, keyboardEvent);

	device->setWindowCaption(L"Sandbox");
	this->driver = device->getVideoDriver();
	this->smgr = device->getSceneManager();
	this->guienv = device->getGUIEnvironment();
}