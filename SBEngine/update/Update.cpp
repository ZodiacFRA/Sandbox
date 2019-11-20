//
// Created by seb on 19/11/2019.
//

#include <FpsCamera.hpp>
#include <controllers/Keyboard.hpp>
#include "Update.hpp"

Update::Update()  {
	auto &ecs = Ecs::get();

	/// Update Speed
	/*ecs.addUpdate(20, [](){
		Update::keyboard();
	});*/
	ecs.addUpdate(20, [](){
		Update::speed();
	});
	ecs.addUpdate(20, [](){
		Update::fpsCamera();
	});
	ecs.addUpdate(100, [&ecs](){
		ecs.driver->beginScene(true, true, SColor(255,100,101,140));
		ecs.smgr->drawAll();
		ecs.guienv->drawAll();
		ecs.driver->endScene();
	});
	ecs.addUpdate(101, [](){
		Update::online();
	});
}

void Update::online() {
	auto &ecs = Ecs::get();
	auto &node = ecs.getComponentMap<SceneNode>();
	auto ids = ecs.filter<Online, SceneNode>();

	for (const auto &id: ids) {
		auto pos = node[id].node->getPosition();
		auto rot = node[id].node->getRotation();
		std::cout << "ID: " << id << std::endl;
		std::cout << "Position: " << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
		std::cout << "Rotation: " << rot.X << " " << rot.Y << " " << rot.Z << std::endl;
	}
}

void Update::speed() {
	auto &ecs = Ecs::get();
	auto &anim = ecs.getComponentMap<SceneNode>();
	auto &speed = ecs.getComponentMap<Speed>();

	auto ids = ecs.filter<Speed>();

	for (const auto &id : ids) {
		vector3d<f32> pos = anim[id].node->getPosition();
		anim[id].node->setPosition(pos + speed[id].speed);
	}
}

void Update::fpsCamera() {
	auto &ecs = Ecs::get();
	auto &cam = ecs.getComponentMap<FpsCamera>();
	auto &node = ecs.getComponentMap<SceneNode>();
	auto ids = ecs.filter<FpsCamera, SceneNode>();

	for(const auto &id : ids) {
		auto rot = node[id].node->getRotation();
		cam[id].camera->setTarget(node[id].node->getPosition() + vector3df(cos(rot.Y) * 100, 0, sin(rot.Y) * 100));
		cam[id].camera->setPosition(node[id].node->getPosition() + vector3df(cos(rot.Y) * 2, 0, sin(rot.Y) * 2));
	}
}

void Update::keyboard() {
	auto &keyboards = Ecs::get().getComponentMap<Keyboard>();

	for (auto &keyboard : keyboards) {
		for (auto &key : keyboard.second.keyMap) {
			if (key.second.second)
				key.second.second(key.second.first);
		}
	}
}
