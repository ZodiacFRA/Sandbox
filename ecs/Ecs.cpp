//
// Created by seb on 16/11/2019.
//

#include "Ecs.hpp"

Ecs::Ecs() {
	this->device = std::shared_ptr<IrrlichtDevice>(createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			      false, false, false, 0));

	device->setWindowCaption(L"Le jeux de ses morts");
	this->driver = std::shared_ptr<IVideoDriver>(device->getVideoDriver());
	this->smgr = std::shared_ptr<ISceneManager>(device->getSceneManager());
	this->guienv = std::shared_ptr<IGUIEnvironment>(device->getGUIEnvironment());
}