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
		template <class FieldObjectType, class PointCoordType = short>
		class WavePathFinder
		{
			using Field = Field<FieldObjectType, PointCoordType>;
			using Point = Shared::Geometry::Point<PointCoordType>;

			const Field& _field;

			Shared::FieldData::Field<int, PointCoordType> _field_marks;

			std::deque<Point> _points_to_check;
			int _min_mark = 1;
			
			std::vector<Point> _cur_end_points;
			
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

			void Find(Point start_point, const std::vector<Point>& end_points, std::vector<Point>& o_next_points)
			{
				// Копируем конечные точки в новый массив, чтоб можно было их удалять как только мы найдем точку
				_cur_end_points.clear();
				_cur_end_points = end_points;

				int finded_end_points_count = 0;
				if (_min_mark > kMarksTreshold)
				{
					_min_mark = 1;
					ResetFieldMarks();
				}

				_field_marks.SetObject(start_point, _min_mark);

				_points_to_check.clear();
				_points_to_check.push_back(start_point);

				auto max_mark = _min_mark;
				while (!_points_to_check.empty() && !_cur_end_points.empty())
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

						if (_field_marks.Object(new_point) >= _min_mark)
						{
							// Уже просматривали эту точку
							continue;
						}
						
						const auto IsNotNewPoint = [&new_point](const auto& point)
						{
							return point != new_point;
						};

						if (const auto it_to_matched_points = std::partition(_cur_end_points.begin(), _cur_end_points.end(), IsNotNewPoint);
						it_to_matched_points != _cur_end_points.end())
						{
							_field_marks.SetObject(new_point, cur_depth + 1);
							max_mark = cur_depth + 1;
							_cur_end_points.erase(it_to_matched_points, _cur_end_points.end());
						}
						
						if (_field_marks.Object(new_point) < _min_mark)
						{
							_field_marks.SetObject(new_point, cur_depth + 1);
							max_mark = cur_depth + 1;
							_points_to_check.push_back(new_point);
						}
					}
				}

				_points_to_check.clear();

				for (unsigned int i = 0; i < end_points.size(); i++)
				{
					// По умолчнаию считаем что точке надо остаться на месте
					o_next_points[i] = end_points[i];

					const auto depth = _field_marks.Object(end_points[i]);

					if (depth < _min_mark)
					{
						continue; // Не полулось найти путь до точки
					}

					for (const auto& delta : _deltas)
					{
						const auto new_point = end_points[i] - delta;

						if (_field_marks.IsOutOfField(new_point))
						{
							continue;
						}

						if (_field_marks.Object(new_point) == depth - 1)
						{
							o_next_points[i] = new_point;
							break;
						}
					}
				}	
				_min_mark = max_mark;
			}


		public:
			WavePathFinder(const Field& field)
				: _field(field),
				  _field_marks(field.Size()._width, field.Size()._height)
			{}

			void FindNextPoints(Point start_point, const std::vector<Point>& end_points, std::vector<Point>& o_next_points)
			{
				Find(start_point, end_points, o_next_points);
			}
		};
	}
}