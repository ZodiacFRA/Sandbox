//
// Created by seb on 16/11/2019.
//

#ifndef SANDBOX_ANIMATEDMESHSCENE_HPP
#define SANDBOX_ANIMATEDMESHSCENE_HPP

#include <Ecs.hpp>

struct AnimatedMeshScene {
	AnimatedMeshScene(std::string meshPath, std::string texturePath) {
		this->mesh = std::shared_ptr<IAnimatedMesh>(Ecs::get().smgr->getMesh(meshPath.c_str()));
		if (!this->mesh) {
			Ecs::get().device->drop();
		}

		this->node = std::shared_ptr<IAnimatedMeshSceneNode>(Ecs::get().smgr->addAnimatedMeshSceneNode(this->mesh.get()));
		if (this->node) {
			this->node->setMaterialFlag(EMF_LIGHTING, false);
			this->node->setMD2Animation(scene::EMAT_STAND);
			this->node->setMaterialTexture( 0, Ecs::get().driver->getTexture(texturePath.c_str()) );
		}
	}

	std::shared_ptr<IAnimatedMesh> mesh;
	std::shared_ptr<IAnimatedMeshSceneNode> node;
};


#endif //SANDBOX_ANIMATEDMESHSCENE_HPP
