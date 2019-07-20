// ☕ Привет
#pragma once

#include "Shared\ConsoleHelper\ConsoleHelper.h"

namespace Shared
{
	namespace ConsoleHelper
	{
		static void DrawBorder(Point position, short width, short height)
		{
			static const unsigned char    left_up = 201;
			static const unsigned char    up_down = 205;
			static const unsigned char   right_up = 187;
			static const unsigned char right_down = 188;
			static const unsigned char  left_down = 200;
			static const unsigned char left_right = 186;
			
			Console().Print({ position._x,         position._y              }, left_up,    Color::Red);
			Console().Print({ position._x,         position._y + height - 1 }, left_down,  Color::Red);
			Console().Print({ position._x + width, position._y              }, right_up,   Color::Red);
			Console().Print({ position._x + width, position._y + height - 1 }, right_down, Color::Red);

			std::string upper_lower_bound(width - 1, up_down);
			Console().PrintString({ position._x + 1, position._y }, upper_lower_bound, Color::Red);
			for (short y = position._y + 1; y < position._y + height - 1; y++)
			{
				Console().Print({ position._x , y },        left_right, Color::Red);
				Console().Print({ position._x + width, y }, left_right, Color::Red);
			}
			Console().PrintString({ position._x + 1, position._y + height - 1 }, upper_lower_bound, Color::Red);
		}

	}
}