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

ID PlayerCreator::createPlayer(std::string meshPath, std::string texturePath, vector3df position, vector3df rotation,
			       ITriangleSelector *mapSelector) {
	auto &ecs = Ecs::get();
	auto &keyboard = ecs.getComponentMap<Keyboard>();
	auto &speed = ecs.getComponentMap<Speed>();
	auto id = ObjectCreator::createObject(meshPath, texturePath, position, rotation, mapSelector, false);

	//ecs.addComponent<Online>(id);
	float speedX = 0.3;
	float speedY = 0.3;
	float speedZ = 0.3;
	ecs.addComponent<Speed>(id, 0.0, 0.0, 0.0);
	ecs.addComponent<Online>(id);
	ecs.addComponent<Keyboard>(id);
	keyboard[id].keyMap[EKEY_CODE::KEY_ESCAPE] = std::pair<bool, std::function<void(bool)>>(false, [id, &ecs](bool pressed){
		if (pressed)
			ecs.device->closeDevice();
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_KEY_Z] = std::pair<bool, std::function<void(bool)>>(false, [id, speedX, speedY, speedZ, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.Y = speedX;
		else if (speed[id].speed.Y == speedX)
			speed[id].speed.Y = 0.0;
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_KEY_Q] = std::pair<bool, std::function<void(bool)>>(false, [id, speedX, speedY, speedZ, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.X = -speedY;
		else if (speed[id].speed.X == -speedY)
			speed[id].speed.X = 0.0;
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_KEY_S] = std::pair<bool, std::function<void(bool)>>(false, [id, speedX, speedY, speedZ, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.Y = -speedX;
		else if (speed[id].speed.Y == -speedX)
			speed[id].speed.Y = 0.0;
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_KEY_D] = std::pair<bool, std::function<void(bool)>>(false, [id, speedX, speedY, speedZ, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.X = speedY;
		else if (speed[id].speed.X == speedY)
			speed[id].speed.X = 0.0;
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_SPACE] = std::pair<bool, std::function<void(bool)>>(false, [id, speedX, speedY, speedZ, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.Z = speedZ;
		else if (speed[id].speed.Z == speedZ)
			speed[id].speed.Z = 0.0;
	});
	keyboard[id].keyMap[EKEY_CODE::KEY_LCONTROL] = std::pair<bool, std::function<void(bool)>>(false, [id, speedX, speedY, speedZ, &ecs, &speed](bool pressed){
		if (pressed)
			speed[id].speed.Z = -speedZ;
		else if (speed[id].speed.Z == -speedZ)
			speed[id].speed.Z = 0.0;
	});

	return id;
}

ID PlayerCreator::createPlayer(std::string meshPath, std::string texturePath, std::vector<float> position, std::vector<float> rotation, ITriangleSelector *mapSelector) {
	return createPlayer(meshPath, texturePath, vector3df(position[0], position[1], position[2]),
			    vector3df(rotation[0], rotation[1], rotation[2]), mapSelector);
}

ID PlayerCreator::createFpsCamera(ID player) {
	auto &ecs = Ecs::get();
	auto id = ecs::Entity::getId();
	auto &mouse = ecs.getComponentMap<Mouse>();
	auto parent = ecs.getComponentMap<SceneNode>()[player].node;

	auto box = parent->getBoundingBox().MaxEdge;


	ecs.addComponent<FpsCamera>(id, player, vector3df(box.X / 2.0, box.Y + 1, box.Z / 2.0));
	ecs.addComponent<Mouse>(id);
	mouse[id].onMove = [id, &ecs, parent](int x, int y){
		if (x != 640/2 || y != 480/2) {
			auto cam = ecs.getComponentMap<FpsCamera>()[id];
			auto rot = cam.camera->getRotation();

			float x_sens = 1000.0;
			float x_fov = 110.0;
			float x_size = 640.0;

			float y_sens = 1000.0;
			float y_fov = 110.0;
			float y_size = 480.0;

			float delta_x = ((x_fov / x_size) * ((double)(x) - (x_size / 2.0))) / x_sens;
			float delta_y = ((y_fov / y_size) * ((double)(y) - (y_size / 2.0))) / y_sens;
			cam.camera->setRotation(rot - vector3df(0, delta_x, 0));
			cam.camera->setRotation(cam.camera->getRotation() + vector3df(delta_y, 0, 0));
			ecs.device->getCursorControl()->setPosition(640/2, 480/2);
		}
	};


	return 0;
}
