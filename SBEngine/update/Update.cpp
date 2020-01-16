//
// Created by seb on 19/11/2019.
//

#include <FpsCamera.hpp>
#include <controllers/Keyboard.hpp>
#include <network/client/TCPClient.hpp>
#include <component/controllers/Mouse.hpp>
#include "Update.hpp"

Update::Update(void *network)  {
	auto &ecs = Ecs::get();

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
#ifdef	SERVER
	auto server = (TCPServer*)network;
	ecs.addUpdate(101, [&ecs, server](){
		auto &nodes = ecs.getComponentMap<SceneNode>();
		auto &keyboards = ecs.getComponentMap<Keyboard>();
		for (auto &tcpSock: server->connected) {
			tcpSock->updatesMutex.lock();
			for (auto &elem : tcpSock->updates) {
				std::istringstream ss(elem);
				ID id;
				ss >> id;

				vector3df rot;
				ss >> rot.X >> rot.Y >> rot.Z;
				nodes[id].node->setRotation(rot);

				bool empty;
				ss >> empty;

				for (auto &key: keyboards[id].keyMap)
						key.second.first = false;
				if (!empty) {
					std::string keys;
					ss >> keys;

					for (auto key : keys)
						keyboards[id].keyMap[(EKEY_CODE)key].first = true;
				}
			}
			tcpSock->updates.clear();
			tcpSock->updatesMutex.unlock();
		}
	});
	ecs.addUpdate(102, [server](){
		Update::online(server);
	});
#endif
#ifdef	CLIENT_MULTI
	auto client = (TCPClient*)network;
	ecs.addUpdate(111, [client, &ecs](){
		ID player = ecs.filter<Keyboard>()[0];
		auto &keyboard = ecs.getComponentMap<Keyboard>()[player];
		auto &rotation = ecs.getComponentMap<SceneNode>()[player].node->getRotation();

		std::string pressedKeys;
		for (auto &elem : keyboard.keyMap)
			if (elem.second.first)
				pressedKeys += elem.first;

		std::ostringstream out;
		out << player << '\n';
		out << rotation.X << '\n' << rotation.Y << '\n' << rotation.Z << '\n';
		out << pressedKeys.empty() << '\n';
		out << pressedKeys << '\n';

		auto oui = out.str();
		if (client->socket()->is_open())
			client->socket()->send(boost::asio::buffer(oui));
	});
	ecs.addUpdate(112, [&ecs, client](){
		client->mutex.lock();
		auto &node = ecs.getComponentMap<SceneNode>();
		ID player = ecs.filter<Keyboard>()[0];
		while (client->pendingUpdates.size() != 0) {
			std::istringstream ss(client->pendingUpdates.front());
			client->pendingUpdates.pop();
			ID id;
			float x, y, z;
			ss >> id;

			ss >> x >> y >> z;
			node[id].node->setPosition(vector3df(x, y, z));

			if(id != player) {
				ss >> x >> y >> z;
				node[id].node->setRotation(vector3df(x, y, z));
			}
		}
		client->mutex.unlock();
	});
#endif
}

void Update::online(TCPServer *server) {
	auto &ecs = Ecs::get();
	auto &node = ecs.getComponentMap<SceneNode>();
	auto ids = ecs.filter<Online, SceneNode>();
	bool doClean = false;

	for (const auto &id: ids) {
		auto pos = node[id].node->getPosition();
		auto rot = node[id].node->getRotation();
		std::stringstream ss;
		/*ss << "ID: " << id << std::endl;
		ss << "Position: " << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
		ss << "Rotation: " << rot.X << " " << rot.Y << " " << rot.Z << '\0';*/
		ss << id << std::endl;
		ss << pos.X << "\n" << pos.Y << "\n" << pos.Z << std::endl;
		ss << rot.X << "\n" << rot.Y << "\n" << rot.Z << '\0';
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
