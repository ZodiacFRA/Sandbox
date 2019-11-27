//
// Created by seble on 01/11/2018.
//

#pragma once

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <set>

#include "ComponentList.hpp"
#include "KeyboardEvent.hpp"

///include Graphical
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//namespace ecs{
class Ecs {
public:

	Ecs();

	/// Get the thread's instance of the Ecs
	/// \return Ecs &ecs
	static Ecs &get() {
		thread_local static Ecs ecs;

		return ecs;
	}

	/// Get a component map of type T
	/// \tparam T component type
	/// \return component map of type T
	template <typename T>
	std::unordered_map<ID, T> &getComponentMap() {
		return ecs::ComponentList<T>::get().getComponentMap();
	}

	/// Add a component of type T to an id
	/// \tparam T the Type of the component
	/// \tparam Args
	/// \param id where the component will be added
	/// \param args arguments to create the component
	template<typename T, typename ...Args>
	void addComponent(ID id, Args... args){
		get()._deleteIds[id][std::string(typeid(T).name())] = ecs::ComponentList<T>::get().addComponent(id, args...);
		get()._ids.emplace(id);
	}


	/// Delete every component of an id
	/// \param id the ID to delete
	void deleteId(ID id) {
		for (auto &del : get()._deleteIds[id]) {
			del.second();
		}
		get()._deleteIds.erase(id);
		get()._ids.erase(id);
	}

	/// Return if the ID is fully deleted or not
	/// \param id the ID to check
	/// \return Does the ID exist
	bool isDeleted(ID id) {
		return (get()._ids.find(id) != get()._ids.end());
	}

	/// Delete a component of type T of an id
	/// \tparam T the type of the component to delete
	/// \param id the id which will have the component T removed
	template <typename T>
	void deleteComponentforId(ID id) {
		get()._deleteIds[id][std::string(typeid(T).name())]();
		get()._deleteIds[id].erase(std::string(typeid(T).name()));
		if (get()._deleteIds[id].empty())
			get()._ids.erase(id);
	}

	/// Get every id which has the components given
	/// \tparam Args Types of components
	/// \return vector of ids
	template <typename ...Args>
	std::vector<ID> filter() {
		std::vector<ID> valableId;
		for (auto &it : get()._deleteIds) {
			if (idHasComponents<Args...>(it.first))
				valableId.emplace_back(it.first);
		}
		return (valableId);
	}

	/// Check if an id has the components given
	/// \tparam Args Types of component
	/// \param id id to check the component
	/// \return if the id has every components return true@Alex
	template <typename ...Args>
	bool idHasComponents(ID id) {
		isIn<Args...> isin;
		return (isin(id));
	}

	/// Add an update wich will be called by priority from 0 to 100++
	/// \param priority the priority od the update
	/// \param function the update wich will be called
	void addUpdate(int priority, std::function<void()> function) {
		updates.emplace(priority, function);
	}

	/// Clear every updates
	void clearUpdates() {
		updates.clear();
	}

	/// Call every updates
	void update () {
		for (auto &func : updates) {
			func.second();
		}
	}

	std::unordered_map<ID, std::unordered_map<std::string, std::function<void()>>>  _deleteIds;
	std::set<ID>									_ids;
private:
	std::multimap<int, std::function<void()>>				updates;

	template <typename ...Ts>
	struct isIn {
		bool operator() (ID id);
	};

	template <typename T>
	struct isIn<T> {
		bool operator() (ID id) {
			auto &vec = ecs::ComponentList<T>::get().getComponentMap();
			return (vec.find(id) != vec.end());
		}
	};

	template <typename T, typename ...Args>
	struct isIn<T, Args...> {
		bool operator() (ID id) {
			isIn<Args...> isin;
			auto &vec = ecs::ComponentList<T>::get().getComponentMap();
			return ((vec.find(id) != vec.end()) && isin(id));
		}
	};

/// Irrlicht attributes
public:
	IrrlichtDevice*		device;
	IVideoDriver*		driver;
	ISceneManager*		smgr;
	IGUIEnvironment*	guienv;

public:
	KeyboardEvent	*keyboardEvent;
};
