//
// Created by seble on 01/11/2018.
//

#pragma once

using ID = unsigned long;

namespace ecs {
        class Entity {
        public:
        	/// Get an unique id
        	/// \return unique id
        	static ID getId();
        };
}