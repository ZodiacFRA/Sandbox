//
// Created by seb on 19/11/2019.
//

#pragma once

#include <string>
#include <vector>
#include "irrlicht.h"
#include <Entity.hpp>

using namespace irr;
using namespace core;
using namespace scene;

class ObjectCreator {
public:
	static ID createObject(std::string meshPath, std::string texturePath, vector3df position, vector3df rotation, ITriangleSelector *mapSelector);
	static ID createObject(std::string meshPath, std::string texturePath, std::vector<float> position, std::vector<float> rotation,  ITriangleSelector *mapSelector);

	static ID createLight(ISceneNode* parent = nullptr, const core::vector3df& position = core::vector3df(0,0,0), video::SColorf color = video::SColorf(1.0f, 1.0f, 1.0f), f32 radius=100.0f);
	static ID createLight(ISceneNode* parent, const std::vector<float>& position,  std::vector<float> color, float radius);
	static ID createLight(const core::vector3df& position = core::vector3df(0,0,0), video::SColorf color = video::SColorf(1.0f, 1.0f, 1.0f), f32 radius=100.0f);
	static ID createLight(const std::vector<float>& position,  std::vector<float> color, float radius);
};
