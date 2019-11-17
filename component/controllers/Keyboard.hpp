//
// Created by seb on 17/11/2019.
//

#pragma once

#include <irrlicht.h>
using namespace irr;

#include <unordered_map>
#include <functional>

#include <Entity.hpp>

struct Keyboard {
	Keyboard() {
	}

	std::unordered_map<EKEY_CODE, std::pair<bool, std::function<void(bool)>>> keyMap;
};