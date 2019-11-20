//
// Created by seb on 19/11/2019.
//

#include "PlayerCreator.hpp"
#include "ObjectCreator.hpp"
#include <Entity.hpp>
#include <Speed.hpp>
#include <controllers/Keyboard.hpp>
#include <SceneNode.hpp>
#include <Online.hpp>
#include <FpsCamera.hpp>
#include <component/controllers/Mouse.hpp>

ID PlayerCreator::createPlayer(std::string meshPath, std::string texturePath) {
	auto &ecs = Ecs::get();
	auto &keyboard = ecs.getComponentMap<Keyboard>();
	auto &mouse = ecs.getComponentMap<Mouse>();
	auto &speed = ecs.getComponentMap<Speed>();
	auto id = ObjectCreator::createObject(meshPath, texturePath);

	ecs.addComponent<SceneNode>(id, "./assets/sydney.md2", "./assets/sydney.bmp");

	//ecs.addComponent<Online>(id);
	ecs.addComponent<Speed>(id, 0.1, 0.0, 0.0);
	ecs.addComponent<Keyboard>(id);
	keyboard[id].keyMap[EKEY_CODE::KEY_ESCAPE] = std::pair<bool, std::function<void(bool)>>(false, [id, &ecs](bool pressed){
		if (pressed)
			ecs.device->closeDevice();
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_KEY_Z] = std::pair<bool, std::function<void(bool)>>(false, [id, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.X = 10.0;
		else
			speed[id].speed.X = 0.0;
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_KEY_Q] = std::pair<bool, std::function<void(bool)>>(false, [id, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.Z = 10.0;
		else
			speed[id].speed.Z = 0.0;
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_KEY_S] = std::pair<bool, std::function<void(bool)>>(false, [id, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.X = -10.0;
		else
			speed[id].speed.X = 0.0;
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_KEY_D] = std::pair<bool, std::function<void(bool)>>(false, [id, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.Z = -10.0;
		else
			speed[id].speed.Z = 0.0;
	});

	ecs.addComponent<Mouse>(id);
	mouse[id].onMove = [id, &ecs](int x, int y){
		if (x != 640/2 || y != 480/2) {
			std::cout << "Mouse: " << (110.0 / 640.0) * ((float)x - 640.0 / 2.0) / 100 << std::endl;
			auto &node = ecs.getComponentMap<SceneNode>()[id];
			auto rot = node.node->getRotation();
			node.node->setRotation(rot - vector3df(0,110.0 / 640.0 * ((float)(x) - 640.0 / 2.0) / 85.0, 0));
			ecs.device->getCursorControl()->setPosition(640/2, 480/2);
		}
	};

	auto node = ecs.getComponentMap<SceneNode>()[id];
	ecs.addComponent<FpsCamera>(id, id, node.node->getPosition() + vector3df(0, 31, 0));

	return id;
}