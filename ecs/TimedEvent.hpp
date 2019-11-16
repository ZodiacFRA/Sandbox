//
// Created by seb on 10/10/18.
//

#pragma once

#include <functional>
#include <vector>
#include <mutex>
#include <thread>
#include "Time.hpp"


struct TimedFuntion {
	TimedFuntion() {
		time = 0;
		func = nullptr;
	}

	TimedFuntion(long time, std::function<void()> &function) {
		this->time = time;
		this->func = function;
	}

	long 			time;
	std::function<void()>	func;
};

class TimedEvent {
public:
	TimedEvent();
	~TimedEvent();

	void addEvent(long time, TimeUnit unit, std::function<void()> function);
	static TimedEvent &get();

	void	clear();
private:

	std::vector<TimedFuntion>		_timedFunctions;
 	long 					_initialTime;
};
