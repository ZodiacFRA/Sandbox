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
#include <network/server/TCPServer.hpp>
#include "interface/loadLevelFromFile.hpp"
#include <boost/thread.hpp>
#include <component/FpsCamera.hpp>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main() {
	boost::asio::io_service io_service;
	TCPServer *server = new TCPServer(io_service, 4242);
	std::thread t([&io_service](){io_service.run();});
	t.detach();

	auto &ecs = Ecs::get();
	auto update = Update(server);
	ecs.keyboardEvent->initialised = true;
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

	ID id = ecs::Entity::getId();
	ecs.addComponent<IMetaTriangleSelector*>(id);
	ecs.getComponentMap<IMetaTriangleSelector*>()[id] = ecs.smgr->createMetaTriangleSelector();
	loadLevelFromFile("1");
	ID player = ecs.getComponentMap<FpsCamera>()[ecs.filter<FpsCamera>()[0]].parent;
	auto node = ecs.getComponentMap<SceneNode>()[player].node;

	ISceneNodeAnimator* anim = ecs.smgr->createCollisionResponseAnimator(
		ecs.getComponentMap<IMetaTriangleSelector*>()[id], node, node->getBoundingBox().MaxEdge,
		core::vector3df(0,-10,0),core::vector3df(0,node->getBoundingBox().MaxEdge.Y,0));
	ecs.getComponentMap<IMetaTriangleSelector*>()[id]->drop(); // As soon as we're done with the mapSelector, drop it.
	node->addAnimator(anim);
	anim->drop();  // And likewise, drop the animator when we're done referring to it.

	// auto selector = MapCreator::createMap();
	// PlayerCreator::createFpsCamera(PlayerCreator::createPlayer("./assets/sydney.md2", "./assets/sydney.bmp",
								   // vector3df(200, 200, 200), vector3df(0, 0, 0), selector));
	while(ecs.device->run()) {
		long time = ecs::Time::get(TimeUnit::MicroSeconds);
		ecs.update();

		auto x = static_cast<unsigned int>(16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::cout << "Cpu usage: " << (double)(16666 - x) / 16666.0 * 100.0 << '\r' << std::flush;
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}


	ecs.device->drop();
	return 0;
}
