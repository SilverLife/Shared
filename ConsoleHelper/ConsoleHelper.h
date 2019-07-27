// ☕ Привет
#pragma once

#include <iostream>

#include "../Geometry/Point.h"
#include <string>

using Point = Shared::Geometry::Point<short>;

namespace Shared
{
	static Point _offset{ 1,1 };

	namespace ConsoleHelper
	{
		namespace
		{
			#include <windows.h>
		}

		enum class Color : WORD
		{
			Black = 0,
			Grey = FOREGROUND_INTENSITY,
			LightGrey = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			Blue = FOREGROUND_BLUE,
			Green = FOREGROUND_GREEN,
			Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
			Red = FOREGROUND_RED,
			Purple = FOREGROUND_RED | FOREGROUND_BLUE,
			LightBlue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			LightGreen = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
			LightCyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			LightRed = FOREGROUND_RED | FOREGROUND_INTENSITY,
			LightPurple = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			Orange = FOREGROUND_RED | FOREGROUND_GREEN,
			Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		};

		class ConsoleHelper {
			HANDLE _console_handle;
			CONSOLE_CURSOR_INFO info;

			ConsoleHelper() {
				_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
				info.bVisible = false;
				info.dwSize = 100;
				SetConsoleCursorInfo(_console_handle, &info);
			}

		public:
			void SetPosition(short x, short y)
			{
				SetConsoleCursorPosition(_console_handle, { x, y });
			}

			ConsoleHelper(const ConsoleHelper&) = delete;

			static ConsoleHelper& Get()
			{
				static ConsoleHelper object;
				return object;
			}

			std::pair<short, short> Size() const
			{
				CONSOLE_SCREEN_BUFFER_INFO console_info;
				if (GetConsoleScreenBufferInfo(_console_handle, &console_info))
				{
					short width = console_info.srWindow.Right - console_info.srWindow.Left + 1;
					short height = console_info.srWindow.Bottom - console_info.srWindow.Top + 1;
					return { width, height };
				}
				else
				{
					printf("Error: %d\n", GetLastError());
				}
			}

			void Print(Point point, char ch)
			{
				SetPosition(point._x, point._y);
				std::cout.put(ch);
			}

			void Print(Point point, const std::string& str)
			{
				SetPosition(point._x, point._y);
				std::cout << str;
			}

			void Print(Point point, char ch, Color color)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
				Print(point, ch);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f); // вернем обратно
			}

			void Discard(Point point)
			{
				Print(point, ' ');
			}

			void PrintString(Point point, const std::string& text, Color color = Color::White)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
				Print(point, text);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f); // вернем обратно
			}
		};

		static ConsoleHelper& Console() { return ConsoleHelper::Get(); }

		// Инкапсулирует точку на консоле. Если объект существует, значит в указанной точке на консоле нарисован 
		// соответсвующий символ.
		class ConsolePoint
		{
			Point _point;
			char _symbol;
			bool _is_null = false;
			Color _color;

			void Print()
			{
				Console().Print(_point + _offset, _symbol, _color);
			}

			void Discard()
			{
				Console().Discard(_point + _offset);
			}

			ConsolePoint(const ConsolePoint&) = delete;

		public:
			ConsolePoint(Point point, char symbol, Color color)
				: _point(point),
				_symbol(symbol),
				_color(color)
			{
				Print();
			}

			ConsolePoint(ConsolePoint&& rhs)
				: _point(rhs._point),
				_symbol(rhs._symbol),
				_color(rhs._color)
			{
				rhs._is_null = true;
			}

			void operator=(ConsolePoint&& rhs)
			{
				_point = rhs._point;
				_symbol = rhs._symbol;
				_color = rhs._color;
				rhs._is_null = true;
				Print();
			}

			~ConsolePoint()
			{
				if (!_is_null)
				{
					Discard();
				}
			}

			void Move(const Point& delta)
			{
				Discard();
				_point += delta;
				Print();
			}

			void Set(const Point& point)
			{
				Discard();
				_point = point;
				Print();
			}

			Point GetPoint() const { return _point; }
		};
	}
}