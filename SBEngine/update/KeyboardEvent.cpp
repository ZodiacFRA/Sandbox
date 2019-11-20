//
// Created by seb on 17/11/2019.
//

#include <Ecs.hpp>
#include <component/controllers/Mouse.hpp>
#include "KeyboardEvent.hpp"
#include "../component/controllers/Keyboard.hpp"

bool KeyboardEvent::OnEvent(const struct irr::SEvent & event) {
	if (!initialised)
		return false;
	auto &ecs = Ecs::get();
	auto &keyboard = ecs.getComponentMap<Keyboard>();
	auto &mouse = ecs.getComponentMap<Mouse>();

	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		auto ids = ecs.filter<Keyboard>();
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		for (auto const &id : ids) {
			auto &keymap = keyboard[id].keyMap;

			if (keymap.find(event.KeyInput.Key) != keymap.end()) {
				keymap[event.KeyInput.Key].first = event.KeyInput.PressedDown;
				if (keymap[event.KeyInput.Key].second)
					keymap[event.KeyInput.Key].second(event.KeyInput.PressedDown);
			}
		}
	} else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		auto ids = ecs.filter<Mouse>();
		for (const auto &id: ids) {
			auto &tmpMouse = mouse[id];
			switch(event.MouseInput.Event)
			{
				case EMIE_LMOUSE_PRESSED_DOWN:
					tmpMouse.leftClick.first = true;
					if (tmpMouse.leftClick.second)
						tmpMouse.leftClick.second(true);
					break;

				case EMIE_LMOUSE_LEFT_UP:
					tmpMouse.leftClick.first = false;
					if (tmpMouse.leftClick.second)
						tmpMouse.leftClick.second(false);
					break;

				case EMIE_RMOUSE_PRESSED_DOWN:
					tmpMouse.rightClick.first = true;
					if (tmpMouse.rightClick.second)
						tmpMouse.rightClick.second(true);
					break;

				case EMIE_RMOUSE_LEFT_UP:
					tmpMouse.rightClick.first = false;
					if (tmpMouse.rightClick.second)
						tmpMouse.rightClick.second(false);
					break;

				case EMIE_MOUSE_MOVED:
					tmpMouse.x = event.MouseInput.X;
					tmpMouse.y = event.MouseInput.Y;
					if (tmpMouse.onMove)
						tmpMouse.onMove(tmpMouse.x, tmpMouse.y);
					break;

				default:
					// We won't use the wheel
					break;
			}
		}
	}

	return false;
}
