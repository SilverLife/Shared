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

		template <class T1, class T2>
		static double Scalar(const Point<T1>& p1, const Point<T2>& p2)
		{
			return p1._x * p2._x + p1._y * p2._y;
		}

		template <class T1, class T2>
		static double AngleBetweenPoints(const Point<T1> p1, const Point<T2> p2)
		{
			return acos(Scalar(p1,p2) / (p1.Norma() * p2.Norma()));
		}

		template <class T1, class T2>
		static double AngleBetweenLineAndPoint(const Line<T1>& line, const Point<T2> point)
		{
			auto angle = AngleBetweenPoints(line.DirectionVector(), point);
			if (angle > PI*0.5)
			{
				angle = PI - angle;
			}
			return angle;
		}

		template <class T>
		static Point<T> SignCoordinates(const Point<T>& p)
		{
			return { Sign(p._x) , Sign(p._y) };
		}

		template <class T>
		static Point<T> RotatePoint(const Point<T>& p, double angle, bool is_right = false)
		{
			if (!is_right)
			{
				return
				{
					static_cast<T>( p._x * cos(angle)) + static_cast<T>(p._y * sin(angle)),
					static_cast<T>(-p._x * sin(angle)) + static_cast<T>(p._y * cos(angle))
				};
			}
			else
			{
				return
				{
					static_cast<T>(p._x * cos(angle)) - static_cast<T>(p._y * sin(angle)),
					static_cast<T>(p._x * sin(angle)) + static_cast<T>(p._y * cos(angle))
				};
			}
		}

		static const double PI = acos(-1);

		static double DegressToRadians(double degress)
		{
			return (degress * PI) / 180;
		}

		static double RadiansToDegress(double radians)
		{
			return (radians * 180) / PI;
		}
	}
}