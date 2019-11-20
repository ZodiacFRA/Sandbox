//
// Created by seb on 19/11/2019.
//

#pragma once

#include "irrlicht.h"
using namespace irr;
using namespace core;
#include <Entity.hpp>
#include <string>

class PlayerCreator {
public:
	static ID createPlayer(std::string meshPath, std::string texturePath, vector3df position, vector3df rotation);
};
