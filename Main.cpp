//
// Created by seb on 15/11/2019.
//

#include <iostream>
#include <string>
#include <Ecs.hpp>

#include <irrlicht.h>
#include "component/AnimatedMeshScene.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main() {
	auto ecs = Ecs::get();

	auto id = ecs::Entity::getId();
	ecs.addComponent<AnimatedMeshScene>(id, "./asset/sydney.md2", "./asset/sydney.bmp");

	ecs.smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	while(ecs.device->run())
	{
		ecs.driver->beginScene(true, true, SColor(255,100,101,140));

		ecs.smgr->drawAll();
		ecs.guienv->drawAll();

		ecs.driver->endScene();
	}

	ecs.device->drop();
	return 0;
}