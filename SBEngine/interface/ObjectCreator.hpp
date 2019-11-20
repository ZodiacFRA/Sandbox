//
// Created by seb on 19/11/2019.
//

#pragma once

#include <Entity.hpp>
#include <string>

class ObjectCreator {
public:
	static ID createObject(std::string meshPath, std::string texturePath);
};
