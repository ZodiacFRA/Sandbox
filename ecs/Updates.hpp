//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>

#include "../component/Position.hpp"
#include "../component/Speed.hpp"
#include "../component/AnimatedMeshScene.hpp"

class Updates {
public:
	Updates() {
		auto &ecs = Ecs::get();

		/// Update Position
		ecs.addUpdate(9, [&ecs](){
			auto &pos = ecs.getComponentMap<Position>();
			auto &anim = ecs.getComponentMap<AnimatedMeshScene>();

			auto ids = ecs.filter<Position, AnimatedMeshScene>();

			for (const auto &id : ids) {
				anim[id].node->setPosition(pos[id].pos);
			}
		});

		/// Update Speed
		ecs.addUpdate(10, [&ecs](){
			auto &pos = ecs.getComponentMap<Position>();
			auto &speed = ecs.getComponentMap<Speed>();

			auto ids = ecs.filter<Position, Speed>();

			for (const auto &id : ids) {
				pos[id].pos += speed[id].speed;
			}
		});
	}
};