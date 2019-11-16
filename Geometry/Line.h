// ☕ Привет
#pragma once

#include <cmath>

#include "Point.h"

namespace Shared
{
	namespace Geometry
	{
		template <class T>
		class Line
		{
			using LinePoint = Point<T>;
			LinePoint _normal; // {a,b}
			T _c;

			double _sqrt_a_b;

		public:
			template <class PointCoordsType>
			Line(Point<PointCoordsType> p1, Point<PointCoordsType> p2)
			{
				ConfigureByTwoPoints(p1, p2);
			}

			template <class PointCoordsType>
			void ConfigureByTwoPoints(Point<PointCoordsType> p1, Point<PointCoordsType> p2)
			{
				_normal._x = p2._y - p1._y;
				_normal._y = p1._x - p2._x;
				_c = p2._x * p1._y - p1._x * p2._y;
				_sqrt_a_b = _normal.Norma();
			}

			template <class PointCoordsType>
			void ConvfigureByVectorAndPoint(Point<PointCoordsType> v, Point<PointCoordsType> p)
			{
				_normal._x =  v._y;
				_normal._y = -v._x;
				_c = v._x*p._y - v._y*p._x;
			}

			template <class PointCoordsType>
			double Distance(const Point<PointCoordsType>& point) const
			{
				return static_cast<double>(std::abs(_normal._x*point._x + _normal._y * point._y + _c)) / _sqrt_a_b;
			}

			double X(T y) const
			{
				return static_cast<double>(-_normal._y * y - _c) / _normal._x;
			}

			double Y(T x) const
			{
				return static_cast<double>(-_normal._x * x - _c) / _normal._y;
			}

			template <class PointCoordsType>
			void Rotate(double angle, Point<PointCoordsType> center_point)
			{
				_normal = RotatePoint(_normal, angle);
				_c = -_normal._x * center_point._x - _normal._y * center_point._y;
			}

			const LinePoint& Normal() const { return _normal; }
			const LinePoint  DirectionVector() const { return { -_normal._y, _normal._x }; }
		};
	}
}