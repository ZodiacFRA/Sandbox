//
// Created by seb on 10/10/18.
//

#include <thread>
#include <iostream>
#include "TimedEvent.hpp"
#include "Ecs.hpp"
#include "Time.hpp"

TimedEvent::TimedEvent()
{
	Ecs::get().addUpdate(5, [this](){
		long time;
		std::vector<TimedFuntion, std::allocator<TimedFuntion>>::iterator func;
		time = ecs::Time::get(TimeUnit::NanoSeconds);
		func = this->_timedFunctions.begin();
		if (this->_timedFunctions.empty() != 1) {
			while (func != this->_timedFunctions.end()) {
				if (func->time > this->_initialTime && func->time < time) {
					func->func();
					func = _timedFunctions.erase(func);
				} else {
					func++;
				}
			}
		}
	});
	_initialTime = ecs::Time::get(TimeUnit::NanoSeconds);
}

TimedEvent::~TimedEvent() {
	this->clear();
}

void	TimedEvent::clear() {
	_timedFunctions.clear();
}

TimedEvent& TimedEvent::get() {
	thread_local static TimedEvent event;

	return event;
}

void TimedEvent::addEvent(long time, TimeUnit unit, std::function<void()> function) {
	long _time;

	if (unit == TimeUnit::Hours)
		_time = time * 3600000000000;
	else if (unit == TimeUnit::Minutes)
		_time = time * 60000000000;
	else if (unit == TimeUnit::Seconds)
		_time = time * 1000000000;
	else if (unit == TimeUnit::MilliSeconds)
		_time = time * 1000000;
	else if (unit == TimeUnit::MicroSeconds)
		_time = time * 1000;
	else
		_time = time;

	_timedFunctions.emplace_back(TimedFuntion(ecs::Time::get(TimeUnit::NanoSeconds) + _time, function));

}