//
// Created by seb on 16/11/2019.
//

#pragma once

#include <Ecs.hpp>

#include "../component/Speed.hpp"
#include "../component/SceneNode.hpp"

class Updates {
public:
	Updates() {
		auto &ecs = Ecs::get();

		/// Update Speed
		ecs.addUpdate(10, [&ecs](){
			auto &anim = ecs.getComponentMap<SceneNode>();
			auto &speed = ecs.getComponentMap<Speed>();

			auto ids = ecs.filter<Speed>();

			for (const auto &id : ids) {
				vector3d<f32> pos = anim[id].node->getPosition();
				anim[id].node->setPosition(pos + speed[id].speed);
			}
		});
	}

public:
	KeyboardEvent keyboardEvent;
};
