// ☕ Привет
#pragma once

#include "ConsoleHelper.h"

namespace Shared
{
	namespace ConsoleHelper
	{
		class Label
		{
			Point _position;
			std::string _text;

		public:
			Label(Point position)
			: _position(position)
			{}

			Label(const Label&) = delete;
			Label(Label&&) = default;

			void SetText(std::string_view text)
			{
				_text = text;
				Update();
			}

			void Update() const
			{
				if (_text.empty())
				{
					return;
				}
				Shared::ConsoleHelper::Console().PrintString(_position, _text);
			}
		};
	}
}