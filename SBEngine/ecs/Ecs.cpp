//
// Created by seb on 16/11/2019.
//

#include "Ecs.hpp"

Ecs::Ecs() {
	this->keyboardEvent	= new KeyboardEvent();

	this->device = createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			      false, false, false, keyboardEvent);

	device->setWindowCaption(L"Sandbox");
	this->driver = device->getVideoDriver();
	this->smgr = device->getSceneManager();
	this->guienv = device->getGUIEnvironment();
}