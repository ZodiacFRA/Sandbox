//
// Created by seb on 19/11/2019.
//

#include <Ecs.hpp>
#include "MapCreator.hpp"

ITriangleSelector * MapCreator::createMap() {
	auto &ecs = Ecs::get();

	ecs.device->getFileSystem()->addFileArchive("./assets/maps/test/test.pk3");
	IAnimatedMesh* mesh = ecs.smgr->getMesh("./assets/maps/test/test.bsp");
	ISceneNode* node = nullptr;
	ITriangleSelector *selector = nullptr;
	if (mesh) {
		node = ecs.smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
		selector = ecs.smgr->createOctreeTriangleSelector(
			mesh->getMesh(0), node, 128);
		node->setTriangleSelector(selector);
	}
	if (node)
		node->setPosition(core::vector3df(-1300,-144,-1249));

	return selector;
}
