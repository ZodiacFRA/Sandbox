//
// Created by seb on 19/11/2019.
//

#pragma once

#include "Ecs.hpp"
#include "SceneNode.hpp"

struct FpsCamera {
	FpsCamera(): camera(nullptr) {}
	FpsCamera(ID parent, vector3df pos): parent(parent) {
		auto &ecs = Ecs::get();
		auto &node = ecs.getComponentMap<SceneNode>();
		auto player = node[parent].node;

		camera = ecs.smgr->addCameraSceneNode(player, pos);
	}

	ID parent;
	ICameraSceneNode *camera;
};