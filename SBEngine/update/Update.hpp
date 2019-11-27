//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>
#include <network/server/TCPServer.hpp>

#include "Speed.hpp"
#include "SceneNode.hpp"
#include "Online.hpp"

class Update {
public:
	Update(TCPServer *server);

	static void online(TCPServer *server);
	static void speed();
	static void fpsCamera();
	static void keyboard();
};
