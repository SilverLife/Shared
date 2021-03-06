﻿// ☕ Привет
#pragma once

#include "../Geometry/Point.h"
#include "../Geometry/RectangleSize.h"

#include <vector>
#include <memory>

namespace Shared
{
	namespace FieldData
	{
		
		template <class T, class PointCoordType = short>
		class Field
		{
			using Point = Shared::Geometry::Point<PointCoordType>;
			using FieldSize = Shared::Geometry::RectangleSize<PointCoordType>;

			const FieldSize _size;
			std::unique_ptr<T[]> _data;

		public:
			Field(PointCoordType width, PointCoordType height)
				: _size(width, height)
			{
				_data = std::make_unique<T[]>(_size.Square());
			}

			Field(std::initializer_list<std::initializer_list<T>> init_data)
				: _size(static_cast<PointCoordType>(init_data.begin()->size()), static_cast<PointCoordType>(init_data.size()))
			{
				_data = std::make_unique<T[]>(_size.Square());
				unsigned short i = 0;
				for (auto& row : init_data)
				{
					for (auto& elem : row)
					{
						_data[i] = std::move(elem);
						++i;
					}
				}
			}

			void SetObject(Point p, const T& object) { _data[p._y * _size._width + p._x] = object; }
				  T& Object(Point p)       { return _data[p._y * _size._width + p._x]; }
			const T& Object(Point p) const { return _data[p._y * _size._width + p._x]; }

			bool IsOutOfField(Point p) const { return !_size.IsInRectangle(p._x, p._y); }
			
			FieldSize Size() const { return _size; }
		};
	}
}