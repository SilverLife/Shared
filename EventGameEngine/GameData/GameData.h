// ☕ Привет
#pragma once

#include "../FieldData/Field.h"
#include "../ActionData/ActionManager.h"
#include "../EventData/EventManager.h"

namespace EventGameEngine
{
	template <size_t kCustomEventsCount>
	class GameData
	{
	public:
		EventGameEngine::FieldData::Field _field;
		Action::ActionManager<kCustomEventsCount> _action_manager;
		EventData::EventManager _event_manager;

		GameData(Size field_size)
			: _field(field_size)
			, _action_manager(&_event_manager, &_field)
		{}
	};
}