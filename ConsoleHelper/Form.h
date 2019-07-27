// ☕ Привет
#pragma once

#include "Label.h"
#include "Shared\Geometry\RectangleSize.h"
#include "Shared\ConsoleHelper\PrintHelper.h"

#include <vector>

namespace Shared
{
	namespace ConsoleHelper
	{
		class Form
		{
			static const int kMaxLabels = 20;
		public:
			using FormSize = Shared::Geometry::RectangleSize<short>;

		private:
			const Point	 _position;
			const FormSize _size;

			std::vector<Label> _labels;

			void DrawBorder() const
			{
				Shared::ConsoleHelper::DrawBorder(_position, _size._width, _size._height);
			}

		public:

			Form(Point position, FormSize size)
				: _position(position),
				  _size(size)
			{
				_labels.reserve(kMaxLabels);
				DrawBorder();
			}

			void Update() const
			{
				DrawBorder();
				for (auto& label : _labels)
				{
					label.Update();
				}
			}

			Label& AddLabel(Point position_offset)
			{
				if (_labels.size() > kMaxLabels)
				{
					throw std::logic_error("Max labels in from reacehd");
				}
				_labels.emplace_back(_position + position_offset);
				return _labels.back();
			}
		};
	}
}