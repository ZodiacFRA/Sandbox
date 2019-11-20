//
// Created by seb on 19/11/2019.
//

#include <Ecs.hpp>
#include "Map.hpp"

void Map::createMap() {
	auto &ecs = Ecs::get();

	ecs.device->getFileSystem()->addFileArchive("./assets/map-20kdm2.pk3");
	scene::IAnimatedMesh* mesh = ecs.smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* node = nullptr;
	if (mesh)
		node = ecs.smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	if (node)
		node->setPosition(core::vector3df(-1300,-144,-1249));
}
