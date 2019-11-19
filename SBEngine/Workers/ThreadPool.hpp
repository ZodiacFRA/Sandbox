//
// Created by seb on 23/12/18.
//

#ifndef ECS_THREADPOOL_HPP
#define ECS_THREADPOOL_HPP

#include <vector>
#include <list>
#include <thread>
#include <functional>
#include <mutex>
#include <iostream>

template <typename T>
class ThreadPool {
public:
	ThreadPool(std::function<void(T)> func, int nbWorkers = 4){
		alive = true;
		status.resize(nbWorkers);
		for (int i = 0; i < nbWorkers; i++) {
			workers.emplace_back([this, func, i](){
				T ob;
				while (alive) {
					if (!work.empty()) {
						accedWork.lock();
						if (work.empty()) {
							accedWork.unlock();
							continue;
						}
						status[i] = false;
						ob = work.back();
						work.pop_back();
						accedWork.unlock();
						func(ob);
						status[i] = true;
					}
				}
			});
		}
	}

	~ThreadPool() {
		alive = false;
		for (auto &a: workers)
			if (a.joinable())
				a.join();
	}

	void addTask(T newWork) {
		work.emplace_back(newWork);
	}

	void lockWork(){
		accedWork.lock();
	}

	void unlockWork() {
		accedWork.unlock();
	}

	bool isDone() {
		return (work.empty());
	}

private:
	std::vector<bool>		status;
	std::vector<std::thread>	workers;
	bool 				alive;
	std::function<void(T)>		function;
	std::mutex			accedWork;
	std::list<T>			work;

};


#endif //ECS_THREADPOOL_HPP
