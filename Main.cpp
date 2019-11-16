//
// Created by seb on 15/11/2019.
//

#include <iostream>
#include <string>
#include <Ecs.hpp>

#include <irrlicht.h>
#include <chrono>
#include <Time.hpp>
#include <thread>
#include "component/AnimatedMeshScene.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main() {
	auto ecs = Ecs::get();
	long time;

	auto id = ecs::Entity::getId();
	ecs.addComponent<AnimatedMeshScene>(id, "./asset/sydney.md2", "./asset/sydney.bmp");

	ecs.smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	ecs.addUpdate(100, [&ecs](){
		ecs.driver->beginScene(true, true, SColor(255,100,101,140));
		ecs.smgr->drawAll();
		ecs.guienv->drawAll();
		ecs.driver->endScene();
	});

	while(ecs.device->run()) {
		time = ecs::Time::get(TimeUnit::MicroSeconds);
		ecs.update();

		auto x = static_cast<unsigned int>(16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}

	ecs.device->drop();
	return 0;
}