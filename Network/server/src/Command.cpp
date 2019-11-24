/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Command implementation
*/

#include "Command.hpp"

namespace Babel {

	Command::Command()
	: _code(500),
	_size(0),
	_data(4, '\0')
	{}

	Command::Command(const std::string &comstr)
	: _code(500),
	_size(0),
	_data("")
	{
		from_str(comstr);
	}

	Command::~Command()
	{}

	uint32_t Command::code() const
	{
		return _code;
	}

	void Command::code(uint32_t newCode)
	{
		_code = newCode;
	}

	uint32_t Command::size() const
	{
		return _size;
	}

	const std::string &Command::data() const
	{
		return _data;
	}

	std::string &Command::data()
	{
		return _data;
	}

	void Command::data(const std::string &newData)
	{
		if(newData.length() >= BUFFER_SIZE - 8)
			throw std::length_error("Command: data size must be less than " + std::to_string(BUFFER_SIZE - 8));
		_data = newData;
		_size = _data.length();
	}

	void Command::to_str(std::string &to_fill) const
	{
		to_fill.clear();
		to_fill.shrink_to_fit();
		to_fill.resize(8 + _size, '\0');
		char *under = &to_fill[0];
		uint32_t *ptr = reinterpret_cast<uint32_t *>(under);
		*ptr = _code;
		ptr = reinterpret_cast<uint32_t *>(under + 4);
		*ptr = _size;
		if(_size > 0)
			std::strncpy(under + 8, _data.data(), _size);
	}

	std::string Command::to_str() const
	{
		std::string res;
		to_str(res);
		return res;
	}

	void Command::from_str(const std::string &comstr)
	{
		if(comstr.length() > BUFFER_SIZE)
			throw std::length_error("Command: comstr size must be less than " + std::to_string(BUFFER_SIZE));
		std::string tmp(comstr);
		char *under = &tmp[0];
		uint32_t *ptr = reinterpret_cast<uint32_t *>(under + 4);
		_size = *ptr;
		if(_size > comstr.length() - 8)
			throw std::invalid_argument("Command: malformed input string");
		ptr = reinterpret_cast<uint32_t *>(under);
		_code = *ptr;
		if (_size != 0)
			_data.assign(under + 8, _size);
	}


} /* Babel */
