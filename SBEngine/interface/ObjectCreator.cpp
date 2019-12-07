//
// Created by seb on 19/11/2019.
//

#include "ObjectCreator.hpp"
#include <Entity.hpp>
#include <SceneNode.hpp>
#include <component/controllers/Light.hpp>

// TODO: FIX COLLIDE
ID ObjectCreator::createObject(std::string meshPath, std::string texturePath, vector3df position, vector3df rotation, ITriangleSelector *mapSelector, bool collide) {
	auto &ecs = Ecs::get();
	auto id = ecs::Entity::getId();

	ecs.addComponent<SceneNode>(id, meshPath, texturePath, position, rotation);
	auto node = ecs.getComponentMap<SceneNode>()[id].node;

	if (!collide)
		return id;
	scene::ITriangleSelector* sel = ecs.smgr->createTriangleSelector(node);
	ecs.getComponentMap<IMetaTriangleSelector*>()[ecs.filter<IMetaTriangleSelector*>()[0]]->addTriangleSelector(sel);
	sel->drop();

	if (mapSelector)
	{
		ISceneNodeAnimator* anim = ecs.smgr->createCollisionResponseAnimator(
			mapSelector, node, core::vector3df(30,50,30),
			core::vector3df(0,-10,0), core::vector3df(0,30,0));
		mapSelector->drop(); // As soon as we're done with the mapSelector, drop it.
		node->addAnimator(anim);
		anim->drop();  // And likewise, drop the animator when we're done referring to it.
	}

	node->addShadowVolumeSceneNode();

	return id;
}

ID ObjectCreator::createObject(std::string meshPath, std::string texturePath, std::vector<float> position, std::vector<float> rotation, ITriangleSelector *mapSelector, bool collide) {
	return createObject(meshPath, texturePath, vector3df(position[0], position[1], position[2]),
			    vector3df(rotation[0], rotation[1], rotation[2]), nullptr, collide);
}

ID ObjectCreator::createLight(ISceneNode *parent, const vector3df &position, video::SColorf color, f32 radius) {
	auto &ecs = Ecs::get();
	auto id = ecs::Entity::getId();

	ecs.addComponent<Light>(id, parent, position, color, radius);

	return id;
}

ID ObjectCreator::createLight(ISceneNode *parent, const std::vector<float> &position, std::vector<float> color, float radius) {
	return createLight(
		parent,
		vector3df(position[0], position[1], position[2]),
		SColorf(color[0], color[1], color[2], color[3]),
		radius);
}

ID ObjectCreator::createLight(const vector3df &position, video::SColorf color, f32 radius) {
	return createLight(nullptr, position, color, radius);
}

ID ObjectCreator::createLight(const std::vector<float> &position, std::vector<float> color, float radius) {
	return createLight(
		vector3df(position[0], position[1], position[2]),
		SColorf(color[0], color[1], color[2], color[3]),
		radius);
}
