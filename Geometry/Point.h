﻿// ☕ Привет
#pragma once

namespace Shared
{
	namespace Geometry
	{
		template <class T>
		struct Point
		{
			T _x;
			T _y;

			Point() = default;
			Point(T x, T y) : _x(x), _y(y) {}

			Point operator+(const Point& rhs) const
			{
				return { _x + rhs._x, _y + rhs._y };
			}
			Point operator-(const Point& rhs) const
			{
				return { _x - rhs._x, _y - rhs._y };
			}
			void operator+=(const Point& rhs)
			{
				_x += rhs._x;
				_y += rhs._y;
			}
			void operator-=(const Point& rhs)
			{
				_x -= rhs._x;
				_y -= rhs._y;
			}

			bool operator==(const Point& rhs) const
			{
				return _x == rhs._x && _y == rhs._y;
			}
			bool operator!=(const Point& rhs) const
			{
				return !(operator==(rhs));
			}

			Point operator-() const 
			{
				return { _x * -1, _y * -1 };
			}

			double Norma() const { return sqrt(_x*_x + _y*_y); }
		};
	}
}