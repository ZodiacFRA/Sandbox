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
//		std::cout << "ID: " << id << std::endl;
//		std::cout << "Position: " << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
//		std::cout << "Rotation: " << rot.X << " " << rot.Y << " " << rot.Z << std::endl;
	}
}

void Update::speed() {
	auto &ecs = Ecs::get();
	auto &anim = ecs.getComponentMap<SceneNode>();
	auto &speed = ecs.getComponentMap<Speed>();

	auto ids = ecs.filter<Speed, SceneNode>();

	for (const auto &id : ids) {
		auto pos = anim[id].node->getPosition();
		auto rot = anim[id].node->getRotation();
		anim[id].node->setPosition(pos + vector3df(cos(rot.Y / 180 * PI) * speed[id].speed, 0, -sin(rot.Y / 180 * PI) * speed[id].speed));
	}
}

void Update::fpsCamera() {
	auto &ecs = Ecs::get();
	auto &cam = ecs.getComponentMap<FpsCamera>();
	auto &node = ecs.getComponentMap<SceneNode>();
	auto ids = ecs.filter<FpsCamera>();

	for(const auto &id : ids) {
		const auto rot = cam[id].camera->getRotation();
		const auto pos = node[cam[id].parent].node->getPosition();
		auto target = vector3df(cos(rot.Y) * 100, 0, sin(rot.Y) * 100) -
			      vector3df(0, tan(rot.X) * 100, 0);
		cam[id].camera->setTarget(pos + target);
		cam[id].camera->setPosition(vector3df(cos(rot.Y) * 3, 31, sin(rot.Y) * 3));;
		node[cam[id].parent].node->setRotation(vector3df(0, -atan2(target.Z, target.X) * 180 / PI, 0));
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
