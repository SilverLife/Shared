// ☕ Привет
#pragma once

#include "../Common.h"

namespace EventGameEngine
{
	namespace FieldData
	{
		class FieldObject;
	}

	namespace EventData
	{
		using EventTypeInt = int;

		enum ActionEventType : EventTypeInt
		{
			AddObject,
			RemoveObject,
			MoveObject,
			Win,
			GameOver
		};

		enum class EventGroup
		{
			Action,
			Custom
		};

		struct Event
		{
			EventTypeInt _type;
			EventGroup _group;

			Event(EventTypeInt type, EventGroup group = EventGroup::Action) 
				: _type(type) 
				, _group(group)
			{}

			virtual ~Event() = default;
		};

		struct EventAddObject : Event
		{
			Point _pos;
			FieldData::FieldObject* _object;

			EventAddObject(Point pos, FieldData::FieldObject* object)
				: Event(ActionEventType::AddObject, EventGroup::Action)
				, _pos(pos)
				, _object(object)
			{}
		};

		struct EventRemoveObject : Event
		{
			Point _pos;

			EventRemoveObject(Point pos)
				: Event(ActionEventType::RemoveObject, EventGroup::Action)
				, _pos(pos)
			{}
		};

		struct EventMoveObject : Event
		{
			Point _src_pos;
			Point _dst_pos;

			EventMoveObject(Point src_pos, Point dst_pos)
				: Event(ActionEventType::MoveObject, EventGroup::Action)
				, _src_pos(src_pos)
				, _dst_pos(dst_pos)
			{}
		};
	}
}