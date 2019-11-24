//
// Created by seb on 24/11/2019.
//

#pragma once

#include "Ecs.hpp"

struct Light {
	Light() = default;
	Light(ISceneNode* parent = nullptr,
	      const core::vector3df& position = core::vector3df(0,0,0),
	      video::SColorf color = video::SColorf(1.0f, 1.0f, 1.0f),
	      f32 radius=100.0f) {
		auto &ecs = Ecs::get();
		light = ecs.smgr->addLightSceneNode(parent, position, color, radius);
	}
	ILightSceneNode* light;
};