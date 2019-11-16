//
// Created by seb on 16/11/2019.
//

#ifndef SANDBOX_ANIMATEDMESHSCENE_HPP
#define SANDBOX_ANIMATEDMESHSCENE_HPP

#include <Ecs.hpp>

struct AnimatedMeshScene {
	AnimatedMeshScene(std::string meshPath, std::string texturePath) {
		this->mesh = Ecs::get().smgr->getMesh(meshPath.c_str());
		if (!this->mesh)
		{
			Ecs::get().device->drop();
		}
		this->node = Ecs::get().smgr->addAnimatedMeshSceneNode(this->mesh);

		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			node->setMaterialTexture( 0, Ecs::get().driver->getTexture(texturePath.c_str()) );
		}
	}

	IAnimatedMesh* mesh;
	IAnimatedMeshSceneNode* node;
};


#endif //SANDBOX_ANIMATEDMESHSCENE_HPP
