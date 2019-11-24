/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Command definition
*/

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <cstring>
#include <cstdint>
#include "common.hpp"
#include <stdexcept>

namespace Babel {

	class Command {
	public:
		Command(const std::string &comstr);
		Command();
		~Command();

		uint32_t code() const;
		void code(uint32_t newCode);

		uint32_t size() const;

		const std::string &data() const;
		std::string &data();
		void data(const std::string &newData);

		void to_str(std::string &to_fill) const;
		std::string to_str() const;
		void from_str(const std::string &comstr);

	private:
		uint32_t _code;
		uint32_t _size;
		std::string _data;

	};

} /* Babel */

#endif
