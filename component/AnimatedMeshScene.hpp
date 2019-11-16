//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>

struct AnimatedMeshScene {
	AnimatedMeshScene() = default;
	AnimatedMeshScene(std::string meshPath, std::string texturePath) {
		this->mesh = Ecs::get().smgr->getMesh(meshPath.c_str());
		if (!this->mesh) {
			Ecs::get().device->drop();
		}

		this->node = Ecs::get().smgr->addAnimatedMeshSceneNode(this->mesh);
		if (this->node) {
			this->node->setMaterialFlag(EMF_LIGHTING, false);
			this->node->setMD2Animation(scene::EMAT_STAND);
			this->node->setMaterialTexture( 0, Ecs::get().driver->getTexture(texturePath.c_str()) );
		}
	}


	IAnimatedMeshSceneNode* node;
	IAnimatedMesh* mesh;
};