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
#include "Update.hpp"
#include <DataBank.hpp>
#include <interface/PlayerCreator.hpp>
#include <interface/MapCreator.hpp>
#include "interface/loadLevelFromFile.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main() {
	auto update = Update();
	auto &ecs = Ecs::get();
	ecs.keyboardEvent.initialised = true;
	ecs.device->getCursorControl()->setVisible(false);

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

	loadLevelFromFile("SB_test");
	//MapCreator::createMap();
	//PlayerCreator::createPlayer("./assets/sydney.md2", "./assets/sydney.bmp", vector3df(0, 0, 0), vector3df(0, 0, 0));

	while(ecs.device->run()) {
		long time = ecs::Time::get(TimeUnit::MicroSeconds);
		ecs.update();

		auto x = static_cast<unsigned int>(16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}

	ecs.device->drop();
	return 0;
}
