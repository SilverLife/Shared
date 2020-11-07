// ☕ Привет
#pragma once

#include "../../ConsoleHelper/ConsoleHelper.h"
#include "../EventData/Event.h"
#include "IntersectionResult.h"

namespace EventGameEngine
{
	namespace FieldData
	{
		class FieldObject
		{
			unsigned char _draw_symbol = ' ';
			Shared::ConsoleHelper::Color _color;
		public:
			FieldObject() = default;
			FieldObject(unsigned char draw_symbol, Shared::ConsoleHelper::Color color = Shared::ConsoleHelper::Color::White) 
				: _draw_symbol(draw_symbol) 
				, _color(color)
			{}

			virtual void OnTick(int tick_num) {};

			virtual void OnPlaceToFieldFailure(Point pos) 
			{
				throw std::logic_error("Error");
			};

			// Возникает когда объект мувается за поле.
			// Возвращаемое значение - нужно ли удалять объект
			virtual bool OnMoveOutOfField(Point pos) { return false; }

			// Вызывается, когда надо нарисовать данный объект в указанной точке
			virtual void OnDraw(Point point_to_draw)
			{
				Shared::ConsoleHelper::Console().Print(point_to_draw, _draw_symbol, _color);
			}

			// Вызывается, когда надо затереть объект в указанной точке
			virtual void OnDrawTrace(Point point_to_draw)
			{
				Shared::ConsoleHelper::Console().Print(point_to_draw, ' ');
			}

			virtual void OnMove(Point prev_pos, Point new_pos) {}
			
			// Вызывается когда один объект (Active) при движении пересекается с другим объектом (Passive)
			// По умолчанию при пересечении все выживают и никто никуда не двигается
			virtual int  OnActiveIntersect(Point active_pos, Point passive_pos, FieldObject* intersected_object) { return 0; }
			virtual int OnPassiveIntersect(Point active_pos, Point passive_pos, FieldObject* intersected_object) { return 0; }

			// Вызывается, когда поле решает, что объект надо уничтожить
			virtual void OnRemove() {}

			virtual void OnEvent(EventData::Event* event) {}
		};
	}
}