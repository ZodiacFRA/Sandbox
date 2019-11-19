//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>

struct Speed {
	Speed() = default;
	Speed(float x, float y, float z) {
		this->speed = vector3df(x, y, z);
	}
	vector3df speed;
};
