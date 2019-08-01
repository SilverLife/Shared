// ☕ Привет
#pragma once
#include <cstdint>

namespace Shared
{
	namespace CommonStructs
	{
		// Класс, который просто на каждый _ticks_to_action вызов PerformTick() выдает true
		template <class TickType>
		class Ticker
		{
			TickType _current_tick = 0;
			TickType _ticks_to_action;

		public:
			Ticker(TickType ticks_to_action)
				: _current_tick(0),
				_ticks_to_action(ticks_to_action)
			{}

			bool PerformTick()
			{
				++_current_tick;
				if (_current_tick >= _ticks_to_action)
				{
					_current_tick = 0;
					return true;
				}
				return false;
			}

			void SetTicksToAction(TickType new_ticks_to_action)
			{
				_ticks_to_action = new_ticks_to_action;
			}

			TickType TicksToAction() const { return _ticks_to_action; }
		};

		using TickerByte = Ticker<uint8_t>;
		using TickerShort = Ticker<uint16_t>;
		using TickerInt = Ticker<uint32_t>;
		using TickerLong = Ticker<uint64_t>;
	}
}