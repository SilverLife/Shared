// ☕ Привет
#pragma once

namespace Shared
{
	namespace Geometry
	{
		template <class T>
		bool IsBetween(const T num, const T left_border, const T right_border) { return left_border <= num && num < right_border; }

		template <class T>
		struct RectangleSize
		{
			T _width;
			T _height;

			T Square() const { return _width * _height; }

			RectangleSize(T width, T height) : _width(width), _height(height) {}

			bool IsInRectangle(T x, T y) const { return IsBetween(x, (T)0, _width) && IsBetween(y, (T)0, _height); }
		};
	}
}