//
// Created by seb on 19/11/2019.
//

#include <FpsCamera.hpp>
#include <controllers/Keyboard.hpp>
#include "Update.hpp"

Update::Update(TCPServer *server)  {
	auto &ecs = Ecs::get();

	/// Update Speed
	ecs.addUpdate(20, [](){
		Update::keyboard();
	});
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
	ecs.addUpdate(101, [server](){
		Update::online(server);
	});
}

void Update::online(TCPServer *server) {
	auto &ecs = Ecs::get();
	auto &node = ecs.getComponentMap<SceneNode>();
	auto ids = ecs.filter<Online, SceneNode>();
	bool doClean = false;

	for (const auto &id: ids) {
		auto pos = node[id].node->getPosition();
		auto rot = node[id].node->getRotation();
		//TODO: send data through network
		std::stringstream ss;
		ss << "ID: " << id << std::endl;
		ss << "Position: " << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
		ss << "Rotation: " << rot.X << " " << rot.Y << " " << rot.Z << '\0';
		std::string out = ss.str();
		for (auto mec: server->connected) {
			if (mec->toRemove)
				doClean = true;
			else
				mec->sendData(out.c_str(), out.size());
		}
		if (doClean) {
			doClean = false;
			auto it = server->connected.begin();
			for (; it != server->connected.end() && server->connected.size() != 0; ++it) {
				if ((*it)->toRemove) {
					server->connected.remove(*it);
					break;
				}
			}
		}
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

		anim[id].node->setPosition(pos +
		vector3df(cos((rot.Y) / 180 * PI) * speed[id].speed.Y, 0, -sin((rot.Y) / 180 * PI) * speed[id].speed.Y) +
		vector3df(cos((rot.Y + 90) / 180 * PI) * speed[id].speed.X, 0, -sin((rot.Y + 90) / 180 * PI) * speed[id].speed.X) +
		vector3df(0, speed[id].speed.Z, 0));
	}
}

void Update::fpsCamera() {
	auto &ecs = Ecs::get();
	auto &cam = ecs.getComponentMap<FpsCamera>();
	auto &node = ecs.getComponentMap<SceneNode>();
	auto ids = ecs.filter<FpsCamera>();

	for(const auto &id : ids) {
		const auto rot = cam[id].camera->getRotation();
		const auto camPos = cam[id].camera->getPosition();
		const auto pos = node[cam[id].parent].node->getPosition();
		auto target = vector3df(cos(rot.Y) * 100, 0, sin(rot.Y) * 100) -
			      vector3df(0, tan(rot.X) * 100, 0);
		cam[id].camera->setTarget(pos + target);
//		cam[id].camera->setPosition(vector3df(cos(rot.Y) * 3, camPos.Y, sin(rot.Y) * 3));;
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
