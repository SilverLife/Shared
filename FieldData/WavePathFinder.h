// ☕ Привет
#pragma once

#include "Field.h"
#include <array>

#include <deque>

namespace Shared
{
	namespace FieldData
	{
		template <class FieldObjectType, class PointCoordType = short>
		class WavePathFinder
		{
			using Field = Field<FieldObjectType, PointCoordType>;
			using Point = Shared::Geometry::Point<PointCoordType>;

			const Field& _field;

			Shared::FieldData::Field<int, PointCoordType> _field_marks;

			std::deque<Point> _points_to_check;
			int _min_mark = 1;
			static inline int kMarksTreshold = 1000000000;

			static inline std::vector<Point> _deltas = { {-1,0}, {1,0} , {0,-1}, {0,1} };

			void ResetFieldMarks()
			{
				for (PointCoordType i = 0; i < _field_marks.Size()._width; ++i)
				{
					for (PointCoordType j = 0; j < _field_marks.Size()._height; ++j)
					{
						_field_marks.SetObject({ i,j }, 0);
					}
				}
			}

		public:
			WavePathFinder(const Field& field)
				: _field(field),
				  _field_marks(field.Size()._width, field.Size()._height)
			{}


			std::vector<Point> Find(Point start_point, Point end_point, unsigned int result_size = 1)
			{
				if (_min_mark > kMarksTreshold)
				{
					_min_mark = 1;
					ResetFieldMarks();
				}

				_field_marks.SetObject(start_point, _min_mark);

				_points_to_check.clear();
				_points_to_check.push_back(start_point);

				bool is_finded = false;
				while (!_points_to_check.empty() && !is_finded)
				{
					const auto point_to_check = _points_to_check.front();
					_points_to_check.pop_front();

					const auto cur_depth = _field_marks.Object(point_to_check);

					for (const auto& delta : _deltas)
					{
						const auto new_point = point_to_check + delta;
						
						if (_field_marks.IsOutOfField(new_point))
						{
							continue;
						}

						if (new_point == end_point)
						{
							_field_marks.SetObject(new_point, cur_depth + 1);
							is_finded = true;
							break;
						}

						if (_field_marks.Object(new_point) < _min_mark)
						{
							_field_marks.SetObject(new_point, cur_depth + 1);
							_points_to_check.push_back(new_point);
						}
					}
				}

				_points_to_check.clear();

				auto cur_depth = _field_marks.Object(end_point);
				auto cur_point = end_point;
				_points_to_check.push_back(cur_point);
				
				while (cur_depth > _min_mark)
				{
					bool is_next_point_finded = false;
					for (const auto& delta : _deltas)
					{
						const auto new_point = cur_point - delta;

						if (_field_marks.IsOutOfField(new_point))
						{
							continue;
						}

						if (_field_marks.Object(new_point) == cur_depth - 1)
						{
							cur_point = new_point;
							_points_to_check.push_back(cur_point);
							--cur_depth;
							is_next_point_finded = true;
							break;
						}
					}

					if (!is_next_point_finded)
					{
						throw std::logic_error("Next point must be find");
					}
				}

				_min_mark = _field_marks.Object(end_point) + 1;

				if (cur_point != start_point)
				{
					throw std::logic_error("Start point must be reached");
				}

				std::vector<Point> result;
				result.reserve(result_size);
				std::copy_n(_points_to_check.begin(), std::min(result_size, _points_to_check.size()), std::back_inserter(result));

				return std::move(result);
			}
		};
	}
}