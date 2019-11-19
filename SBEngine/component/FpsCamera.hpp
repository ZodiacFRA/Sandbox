//
// Created by seb on 19/11/2019.
//

#pragma once

#include "Ecs.hpp"
#include "SceneNode.hpp"

struct FpsCamera {
	FpsCamera(): camera(nullptr) {}
	FpsCamera(ID id) {
		auto &ecs = Ecs::get();
		auto &node = ecs.getComponentMap<SceneNode>();
		auto parent = node[id].node;

		camera = ecs.smgr->addCameraSceneNode(parent, parent->getPosition(), parent->getPosition());

		//_cam = _smgr->addCameraSceneNode(0, irr::core::vector3df(21, 10, 11.6),
		//				 irr::core::vector3df(8.5,0,11.6));
		//irr::core::matrix4 MyMatrix;
		//MyMatrix.buildProjectionMatrixPerspectiveRH(90.0f,45.0f,0.0f,-1000.0f);
		//camera->setProjectionMatrix(MyMatrix);

	}

	ICameraSceneNode *camera;
};