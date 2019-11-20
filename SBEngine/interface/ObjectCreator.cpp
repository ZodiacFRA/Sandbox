//
// Created by seb on 19/11/2019.
//

#include "ObjectCreator.hpp"
#include <Entity.hpp>
#include <SceneNode.hpp>

ID ObjectCreator::createObject(std::string meshPath, std::string texturePath) {
	auto &ecs = Ecs::get();
	auto id = ecs::Entity::getId();

	ecs.addComponent<SceneNode>(id, meshPath, texturePath);

	return id;
}