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
using namespace scene;


class PlayerCreator {
public:
	static ID createPlayer(std::string meshPath, std::string texturePath, vector3df position, vector3df rotation, ITriangleSelector *mapSelector);
	static ID createPlayer(std::string meshPath, std::string texturePath, std::vector<float> position, std::vector<float> rotation, ITriangleSelector *mapSelector);

	static ID createFpsCamera(ID parent);
};
