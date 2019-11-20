//
// Created by seb on 19/11/2019.
//

#include "Player.hpp"
#include <Entity.hpp>
#include <Speed.hpp>
#include <controllers/Keyboard.hpp>
#include <SceneNode.hpp>
#include <Online.hpp>
#include <FpsCamera.hpp>

ID Player::createPlayer() {
	auto &ecs = Ecs::get();
	auto &keyboard = ecs.getComponentMap<Keyboard>();
	auto &speed = ecs.getComponentMap<Speed>();
	auto id = ecs::Entity::getId();

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
	ecs.addComponent<FpsCamera>(id, id);

	return id;
}

void Player::addFpsCamera(ID id) {
	auto &ecs = Ecs::get();

	SKeyMap keyMap[8];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_Z;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_Q;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	ecs.smgr->addCameraSceneNodeFPS(0, 300.F, 0.3f, -1, keyMap, 8);
	ecs.device->getCursorControl()->setVisible(false);
}
