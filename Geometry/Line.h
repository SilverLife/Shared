// ☕ Привет
#pragma once

#include <cmath>

#include "AnalyticalGeometry.h"
#include "Point.h"

namespace Shared
{
	namespace Geometry
	{
		template <class T>
		class Line
		{
			using Point = Point<T>;
			T _a;
			T _b;
			T _c;

			double _sqrt_a_b;

		public:
			Line(Point p1, Point p2)
				: _a(p2._y - p1._y)
				, _b(p1._x - p2._x)
				, _c(p2._x * p1._y - p1._x * p2._y)
				, _sqrt_a_b(std::sqrt(_a*_a + _b*_b))
			{}

			double Distance(const Point& point) const
			{
				return static_cast<double>(std::abs(_a*point._x + _b * point._y + _c)) / _sqrt_a_b;
			}

			double X(T y) const
			{
				return static_cast<double>(-_b * y - _c) / _a;
			}

			double Y(T x) const
			{
				return static_cast<double>(-_a * x - _c) / _b;
			}
		};
	}
}