//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>

struct Speed {
	Speed() = default;
	Speed(float speed) {
		this->speed = speed;
	}
	float speed;
};
