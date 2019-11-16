//
// Created by seb on 26/12/18.
//

#ifndef ECS_VECTOR2_HPP
#define ECS_VECTOR2_HPP

namespace ecs { namespace core {
	template<typename T>
	struct Vector2 {
		Vector2() {}

		Vector2(T x, T y) {
			this->x = x;
			this->y = y;
		}
		T x;
		T y;

		Vector2<T> &operator=(Vector2<T> const &equal) {
			this->x = equal.x;
			this->y = equal.y;
			return *this;
		}

		Vector2<T> &operator++() {
			this->x++;
			this->y++;
			return *this;
		}

		Vector2<T> &operator--() {
			this->x--;
			this->y--;
			return *this;
		}

		bool operator==(Vector2<T> const& other) {
			return (this->x == other.x && this->y == other.y);
		}
	};


	}}

#endif //ECS_VECTOR2_HPP
