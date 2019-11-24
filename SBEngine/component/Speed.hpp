//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>

struct Speed {
	Speed() = default;
	Speed(float x, float y, float z) {
		this->speed.X = x;
		this->speed.Y = y;
		this->speed.Z = z;
	}
	Speed(vector3df speed) {
		this->speed = speed;
	}
	vector3df speed;
};
