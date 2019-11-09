// ☕ Привет
#pragma once

#include "Line.h"

namespace Shared
{
	namespace Geometry
	{
		template <class T>
		T Sign(const T& t)
		{
			if (t == 0)
			{
				return 0;
			}
			return (t > 0 ? 1 : -1);
		}

		template <class T>
		static double Scalar(const Point<T>& p1, const Point<T>& p2)
		{
			return p1._x * p2._x + p1._y * p2._y;
		}

		template <class T>
		static double PointsAngle(const Point<T> p1, const Point<T> p2)
		{
			return acos(Scalar(p1,p2) / (p1.Norma() * p2.Norma()));
		}

		template <class T>
		static Point<T> SignCoordinates(const Point<T>& p)
		{
			return { Sign(p._x) , Sign(p._y) };
		}
	}
}