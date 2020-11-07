// ☕ Привет
#pragma once

#include "Event.h"

using namespace EventGameEngine;

namespace EventGameEngine
{
	namespace EventData
	{
		class EventManager;

		void SetEventManager(EventManager* manager);

		void PushEvent(Event* event);
	}
}