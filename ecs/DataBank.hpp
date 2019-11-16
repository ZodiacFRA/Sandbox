/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include <unordered_map>
#include <functional>
#include <iostream>
#include "Entity.hpp"

namespace ecs {
	template <typename I, typename T>
	class DataBank {
	public:

		/// Get the DataBank of iterator type I with the component of type T
		/// \return
		static DataBank<I, T> &get() {
			static DataBank<I, T> bank;

			return (bank);
		}


		/// Get the component T at the iterator I and create it if i doesn't exist yet
		/// \param iterator The iterator I
		/// \return Return a reference of the component of given iterator
		static T &get(I iterator) {
			DataBank<I, T> &bank = DataBank<I,T>::get();
			if (!bank.creator) {
				std::cout << "src/game_engine/ecs/DataBank: creator not initialised for type " << std::string(typeid(T).name()) << std::endl;
				exit(84);
			}
			if (bank.map.find(iterator) == bank.map.end())
				bank.map[iterator] = bank.creator(iterator);
			return (bank.map[iterator]);
		}


		/// Delete the component at the given iterator
		/// \param iterator Will delete the component of this iterator
		static void deleteAt(I iterator) {
			DataBank<I, T> &bank = DataBank<I,T>::get();
			bank.map.erase(iterator);
		}


		/// Directly access to component at the given iterator
		/// \param iterator The iteraot of the component needed
		/// \return Return a reference to the needed component
		T &operator[] (I iterator) {
			if (!creator) {
				std::cout << "src/game_engine/ecs/DataBank: creator not initialised" << std::endl;
				exit(84);
			}
			if (map.find(iterator) == map.end())
				map[iterator] = creator(iterator);
			return (map[iterator]);
		}


		std::function<T(I)>		creator;
		std::unordered_map<I, T>	map;
	};
}