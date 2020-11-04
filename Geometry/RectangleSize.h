// ☕ Привет
#pragma once

namespace Shared
{
	namespace Geometry
	{
		template <class T1, class T2, class T3>
		bool IsBetween(const T1 num, const T2 left_border, const T3 right_border) { return left_border <= num && num < right_border; }

		template <class T>
		struct RectangleSize
		{
			T _width;
			T _height;

			T Square() const { return _width * _height; }

			RectangleSize(T width, T height) : _width(width), _height(height) {}

			bool IsInRectangle(T x, T y) const { return IsBetween(x, (T)0, _width) && IsBetween(y, (T)0, _height); }
		};

		template <class T>
		void SetMinSize(RectangleSize<T>& dest, RectangleSize<T> src)
		{
			if (dest._width > src._width)
			{
				dest._width = src._width;
			}
			if (dest._height > src._height)
			{
				dest._height = src._height;
			}
		}
	}
}