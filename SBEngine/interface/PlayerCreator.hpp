//
// Created by seb on 19/11/2019.
//

#pragma once

#include <Entity.hpp>
#include <string>

class PlayerCreator {
public:
	static ID createPlayer(std::string meshPath, std::string texturePath);
};
