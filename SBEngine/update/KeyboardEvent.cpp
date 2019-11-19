//
// Created by seb on 17/11/2019.
//

#include <Ecs.hpp>
#include "KeyboardEvent.hpp"
#include "../component/controllers/Keyboard.hpp"

bool KeyboardEvent::OnEvent(const struct irr::SEvent & event) {
	if (!initialised)
		return false;
	auto &ecs = Ecs::get();
	auto &keyboard = ecs.getComponentMap<Keyboard>();
	auto ids = ecs.filter<Keyboard>();

	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		for (auto const &id : ids) {
			auto &keymap = keyboard[id].keyMap;

			if (keymap.find(event.KeyInput.Key) != keymap.end()) {
				keymap[event.KeyInput.Key].first = event.KeyInput.PressedDown;
				if (keymap[event.KeyInput.Key].second)
					keymap[event.KeyInput.Key].second(event.KeyInput.PressedDown);
			}
		}
	}

	return false;
}
