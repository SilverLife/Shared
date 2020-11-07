#pragma once

#include "../Geometry/Point.h"
#include "../Geometry/RectangleSize.h"

namespace EventGameEngine
{
	using PointCoordsType = short;
	using Point = Shared::Geometry::Point<PointCoordsType>;
	using uint = unsigned int;
	using Size = Shared::Geometry::RectangleSize<PointCoordsType>;

	static const Point kDeltas[] =
	{
		{-1,0},{ 1,0 },{ 0,1 },{ 0,-1}
	};
}