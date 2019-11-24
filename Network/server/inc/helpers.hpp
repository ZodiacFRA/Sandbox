/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** helper functions definition
*/

#ifndef BABEL_HELPERS_HPP
#define BABEL_HELPERS_HPP

#include <exception>
#include <stdexcept>
#include <cstddef>
#include <memory>
#include <vector>
#include <limits>

unsigned short stous(const std::string &str);

template <typename T>
void splitString(std::vector<std::string> &v, const std::string &s, const T & f)
{
	std::string buff;
	for(auto c: s){
		bool b = f(c);
		if(!b){
			buff+=c;
		} else if(b && buff != "") {
			v.push_back(buff);
			buff = "";
		}
	}
	if(buff != "")
		v.push_back(buff);
}

template <typename T>
inline bool is_uninitialised(std::weak_ptr<T> const &weak)
{
	return !weak.owner_before(std::weak_ptr<T>{}) && !std::weak_ptr<T>{}.owner_before(weak);
}

template <typename T, typename U>
inline bool equals(const std::weak_ptr<T>& t, const std::weak_ptr<U>& u)
{
	return !t.owner_before(u) && !u.owner_before(t);
}


template <typename T, typename U>
inline bool equals(const std::weak_ptr<T>& t, const std::shared_ptr<U>& u)
{
	return !t.owner_before(u) && !u.owner_before(t);
}



#endif
