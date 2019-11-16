//
// Created by seble on 01/11/2018.
//

#include "Entity.hpp"

ID ecs::entity::Entity::getId() {
    thread_local static ID id = 0;
    return (id++);
}