//
// Created by seb on 19/11/2019.
//

#include "ObjectCreator.hpp"
#include <Entity.hpp>
#include <SceneNode.hpp>

ID ObjectCreator::createObject(std::string meshPath, std::string texturePath, vector3df position, vector3df rotation,
			       ITriangleSelector *mapSelector) {
	auto &ecs = Ecs::get();
	auto id = ecs::Entity::getId();

	ecs.addComponent<SceneNode>(id, meshPath, texturePath, position, rotation);
	auto node = ecs.getComponentMap<SceneNode>()[id].node;

	if (mapSelector)
	{
		ISceneNodeAnimator* anim = ecs.smgr->createCollisionResponseAnimator(
			mapSelector, node, core::vector3df(30,50,30),
			core::vector3df(0,-10,0), core::vector3df(0,30,0));
		mapSelector->drop(); // As soon as we're done with the mapSelector, drop it.
		node->addAnimator(anim);
		anim->drop();  // And likewise, drop the animator when we're done referring to it.
	}

	return id;
}

ID ObjectCreator::createObject(std::string meshPath, std::string texturePath, std::vector<float> position, std::vector<float> rotation, ITriangleSelector *mapSelector) {
	return createObject(meshPath, texturePath, vector3df(position[0], position[1], position[2]),
			    vector3df(rotation[0], rotation[1], rotation[2]), nullptr);
}
