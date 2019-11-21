//
// Created by seb on 19/11/2019.
//

#pragma once

#include <string>
#include <vector>
#include "irrlicht.h"
#include <Entity.hpp>

using namespace irr;
using namespace core;


class PlayerCreator {
public:
	static ID createPlayer(std::string meshPath, std::string texturePath, vector3df position, vector3df rotation);
	static ID createPlayer(std::string meshPath, std::string texturePath, std::vector<float> position, std::vector<float> rotation);

	static ID createFpsCamera(ID parent);
};
