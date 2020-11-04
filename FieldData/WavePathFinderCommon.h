// ☕ Привет
#pragma once

#include "Field.h"
#include <array>

#include <deque>

#include "Shared\ConsoleHelper\ConsoleHelper.h"

namespace Shared
{
	namespace FieldData
	{
		// FieldView - класс, который представляет поле.
		using PointCoordType = short;
		template <class FieldView, class EmptyChecker>
		class WavePathFinderCommon
		{
			using Point = Shared::Geometry::Point<PointCoordType>;

			FieldView	 _field_view;
			EmptyChecker _empty_checker;
			const std::vector<Point> _deltas;

			Shared::FieldData::Field<int, PointCoordType> _field_marks;

			std::deque<Point> _points_to_check;
			int _min_mark = 1;

		

		public:
			WavePathFinderCommon(FieldView field_view, EmptyChecker empty_checker, std::vector<Point> deltas)
			: _field_view(field_view)
			, _empty_checker(empty_checker)
			, _deltas(std::move(deltas))
			, _field_marks(field_view.Width(), field_view.Height())
			{}

			Point GetNextPoint(Point start_point, Point end_point)
			{

			}

			Point GetNextPoints(const std::vector<Point> start_points, Point end_point, std::vector<Point>& o_next_points)
			{

			}
		};
	}



	void TestWavePathFinderCommon()
	{
		const int size = 10;
		int arr[size][size];

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				arr[i][j] = std::rand() % 100 > 70 ? 1 : 0;
			}
		}

		const auto start_point = Point{ std::rand() % size,std::rand() % size };
		const auto end_point = Point{ std::rand() % size,std::rand() % size };

		using PointCoordType = short;
		using Point = Shared::Geometry::Point<PointCoordType>;

		class ArrayFieldView
		{
			int** _array;
			int _width;
			int _height;
		public:
			ArrayFieldView(int** arr, int width, int height)
				: _array(arr)
				, _width(width)
				, _height(height)
			{}

			int Width()  const { return _width; }
			int Height() const { return _height; }

			int At(Point p) const
			{
				return _array[p._x][p._y];
			}
		};

		const auto EmptyChecker = [](int val) -> bool
		{
			return val == 0;
		};


		FieldData::WavePathFinderCommon path_finder{ ArrayFieldView((int**)arr, size, size), EmptyChecker, { {0,1}, {0,-1},{1,0},{-1,0} } };
	}
}