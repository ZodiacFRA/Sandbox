/*
** EPITECH PROJECT, 2021
** Lib_Event
** File description:
** Created by seb,
*/

#include "TimedEventAdmin.hpp"
#include <thread>

TimedEventAdmin::TimedEventAdmin():_manager(TimedEvent::get()) {

}

void TimedEventAdmin::addEvent(long time, TimeUnit unit, std::function<void()> &function) {
	_manager.addEvent(time, unit, function);
}