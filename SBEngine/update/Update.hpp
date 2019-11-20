//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>

#include "Speed.hpp"
#include "SceneNode.hpp"
#include "Online.hpp"

class Update {
public:
	Update();

	static void online();
	static void speed();
	static void fpsCamera();
	static void keyboard();

public:
	KeyboardEvent keyboardEvent;
};
