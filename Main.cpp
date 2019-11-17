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
#include "update/Updates.hpp"
#include <DataBank.hpp>
#include "component/SceneNode.hpp"
#include "component/controllers/Keyboard.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main() {
	auto update = Updates();
	auto &ecs = Ecs::get();
	ecs.keyboardEvent.initialised = true;
	auto &keyboard = ecs.getComponentMap<Keyboard>();
	long time;

	ecs::DataBank<std::string, IAnimatedMesh*>::get().creator = [](std::string meshPath){
		auto mesh = Ecs::get().smgr->getMesh(meshPath.c_str());
		if (!mesh) {
			Ecs::get().device->drop();
			std::cout << "Issue with: " << meshPath << std::endl;
			exit(84);
		}
		return mesh;
	};
	ecs::DataBank<std::string, ITexture*>::get().creator = [](std::string texturePath){
		return Ecs::get().driver->getTexture(texturePath.c_str());
	};

	auto id = ecs::Entity::getId();
	ecs.addComponent<SceneNode>(id, "./asset/sydney.md2", "./asset/sydney.bmp");
	ecs.addComponent<Speed>(id, 0.0, 0.0, 0.0);
	ecs.addComponent<Keyboard>(id);
	keyboard[id].keyMap[EKEY_CODE::KEY_KEY_Z] = std::pair<bool, std::function<void(bool)>>(false, [id, &ecs](bool pressed){
		auto &speed = ecs.getComponentMap<Speed>();
		if (pressed)
			speed[id].speed.X = .5;
		else
			speed[id].speed.X = 0;
	});

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