//
// Created by seble on 01/11/2018.
//

#pragma once

#include <any>
#include <vector>
#include <unordered_map>
#include <functional>
#include "Entity.hpp"

namespace ecs {
	template <typename T>
	class ComponentList {
	public:

		/// Get a ComponentList of type T
		/// \return reference to the ComponentList
		static ComponentList<T> &get() {
			thread_local static ComponentList<T> listComponent;

			return listComponent;
		}


		/// Add a component to an ID
		/// \tparam Args
		/// \param id The ID bind to the component
		/// \param args The arguments given to the constructor of the component
		/// \return Return a function to delete the component
		template <typename ...Args>
		std::function<void()> addComponent(ID id, Args... args) {
			_map.try_emplace(id, args...);
			_ids.push_back(id);
			std::sort(_ids.begin(), _ids.end());
			return ([id](){
				ecs::ComponentList<T>::get().getComponentMap().erase(id);
				std::remove_if(ecs::ComponentList<T>::get().getIds().begin(), ecs::ComponentList<T>::get().getIds().end(), [id](ID const &d) {
					return 	d == id;
				});
			});
		}


		/// Return a vector of ID matching the function given
		/// \param function
		/// \return
		std::vector<ID> getIdForComponent(std::function<bool(T&)> function) {
			std::vector<ID> ids;

			for (auto map : _map) {
				if (function(*map.second))
					ids.push_back(*map.first);
			}
			return ids;
		}


		/// Get the component map
		/// \return Return a reference to the component map
		std::unordered_map<ID, T> &getComponentMap() {
			return _map;
		}


		/// Get a vector of ID who have the component T
		/// \return
		std::vector<ID> &getIds() {
			return _ids;
		}


		/// Access directly to the component of ID id
		/// \param id The ID of the component needed
		/// \return Return a reference of the component needed
		T &operator[] (ID id) {
			return _map[id];
		}

	private:
		std::unordered_map<ID, T>	_map;
		std::vector<ID>			_ids;
	};
}
