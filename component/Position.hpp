//
// Created by seb on 16/11/2019.
//

#ifndef SANDBOX_ANIMATEDMESHSCENE_HPP
#define SANDBOX_ANIMATEDMESHSCENE_HPP

#include <Ecs.hpp>

struct Position {
	Position(float x, float y, float z) {
		this->pos = vector3df(x, y, z);
	}
	vector3df pos;
};


#endif //SANDBOX_ANIMATEDMESHSCENE_HPP
