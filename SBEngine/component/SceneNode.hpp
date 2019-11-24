//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>
#include <DataBank.hpp>

struct SceneNode {
	SceneNode() = default;
	SceneNode(std::string meshPath, std::string texturePath, vector3df position, vector3df rotation) {

		this->node = Ecs::get().smgr->addAnimatedMeshSceneNode(ecs::DataBank<std::string, IAnimatedMesh*>::get()[meshPath]);
		if (this->node) {
			this->node->setMaterialFlag(EMF_LIGHTING, false);
			this->node->setMD2Animation(scene::EMAT_STAND);
			this->node->setMaterialTexture( 0, ecs::DataBank<std::string, ITexture*>::get()[texturePath]);
			this->node->setPosition(position);
			this->node->setRotation(rotation);

			auto selector = Ecs::get().smgr->createTriangleSelector(node);
			node->setTriangleSelector(selector);
			selector->drop();
		}
	}

	IAnimatedMeshSceneNode* node;
};