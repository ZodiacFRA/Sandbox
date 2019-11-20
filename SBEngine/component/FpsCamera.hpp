//
// Created by seb on 19/11/2019.
//

#pragma once

#include "Ecs.hpp"
#include "SceneNode.hpp"

struct FpsCamera {
	FpsCamera(): camera(nullptr) {}
	FpsCamera(ID id, vector3df pos) {
		auto &ecs = Ecs::get();
		auto &node = ecs.getComponentMap<SceneNode>();
		auto parent = node[id].node;

		camera = ecs.smgr->addCameraSceneNode(parent, pos);
	}

	ICameraSceneNode *camera;
};