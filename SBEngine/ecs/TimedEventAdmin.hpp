/*
** EPITECH PROJECT, 2021
** Lib_Event
** File description:
** Created by seb,
*/

#pragma once

#include "TimedEvent.hpp"

class TimedEventAdmin {
public:
	TimedEventAdmin();

	void addEvent(long time, TimeUnit unit, std::function<void()> &function);

private:
	TimedEvent	&_manager;

};



