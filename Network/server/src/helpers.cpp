/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** helper functions implementation
*/

#include "helpers.hpp"

unsigned short stous(const std::string &str)
{
	std::size_t pos = 0;
	int res = std::stoi(str, &pos);
	if(pos != str.length())
		throw std::invalid_argument("pos should be the end of str");
	if(res < 1 || res > std::numeric_limits<unsigned short>::max())
		throw std::out_of_range("number out of range for unsigned short");
	return static_cast<unsigned short>(res);
}
