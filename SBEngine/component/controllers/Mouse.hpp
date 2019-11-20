//
// Created by seb on 17/11/2019.
//

#pragma once

#include <irrlicht.h>
using namespace irr;

#include <functional>
#include <Entity.hpp>

struct Mouse {
	Mouse() {
	}

	std::pair<bool, std::function<void(bool)>> leftClick;
	std::pair<bool, std::function<void(bool)>> rightClick;

	int x;
	int y;
	std::function<void(int, int)>	onMove;
};