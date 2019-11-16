//
// Created by seb on 15/11/2019.
//

#include <iostream>
#include <string>
#include <Ecs.hpp>

int main(int ac, char** av) {
	std::cout << "Hello World !" << std::endl;

	auto ecs = Ecs::get();

	auto id = ecs::entity::Entity::getId();
	ecs.addComponent<std::string>(id, "MAIS MANGE TES MORTS");

	auto strings = ecs.getComponentMap<std::string>();
	std::cout << strings[id] << std::endl;
}