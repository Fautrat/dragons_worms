#pragma once

#include <sfml/Graphics.hpp>
#include <math.h>
#include <iostream>

template<typename T>
class VectorMath
{
public:

	T Clamp(T value, T min, T max)
	{
		if (min == max) return min;
		if (min > max) std::cout << "Min is greater than the max" << std::endl;
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	sf::Vector2<T> Transform(sf::Vector2<T> v, float sin, float cos, sf::Vector2<T> position)
	{
		return sf::Vector2<T>(cos * v.x - sin * v.y + position.x,
							  sin * v.x + cos * v.y + position.y);
	}

	static T Lenght(sf::Vector2<T> v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	static T Distance(sf::Vector2<T> a, sf::Vector2<T> b)
	{
		T dx = a.x - b.x;
		T dy = a.y - b.y;
		return sqrt(dx * dx + dy * dy);
	}

	static sf::Vector2<T> Normalize(sf::Vector2<T> v)
	{
		T len = Lenght(v);
		return sf::Vector2<T>(v.x / len, v.y / len);
	}

	static T Dot(sf::Vector2<T> a, sf::Vector2<T> b)
	{
		return a.x * b.x + a.y * b.y;
	}

	static T Cross(sf::Vector2<T> a, sf::Vector2<T> b)
	{
		return a.x * b.y - a.y * b.x;
	}
};