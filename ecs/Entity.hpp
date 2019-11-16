//
// Created by seble on 01/11/2018.
//

#ifndef ECS_ENTITY_HPP
#define ECS_ENTITY_HPP

using ID = unsigned long;

namespace ecs { namespace entity {
        class Entity {
        public:
        	/// Get an unique id
        	/// \return unique id
        	static ID getId();
        };
}}


#endif //ECS_ENTITY_HPP
