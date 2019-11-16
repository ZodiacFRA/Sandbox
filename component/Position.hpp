//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>

struct Position {
	Position() = default;
	Position(float x, float y, float z) {
		this->pos = vector3df(x, y, z);
	}
	vector3df pos;
};

