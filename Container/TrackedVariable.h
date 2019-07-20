// ☕ Привет
#pragma once

namespace Shared
{
	template <class T, class CallbackFunctor>
	class TrackedVariable
	{
		T _value;
		CallbackFunctor&& _callback_functor;
		
	public:
		TrackedVariable(T&& value, CallbackFunctor&& callback_functor)
			: _value(std::forward<T>(value)),
			_callback_functor(std::forward<CallbackFunctor>(callback_functor))
		{}

		void Set(T&& new_value)
		{
			_value = std::forward<T>(new_value);
			_callback_functor(_value);
		}

		void operator=(T&& new_value)
		{
			_value = std::forward<T>(new_value);
			_callback_functor(_value);
		}

		operator T() const
		{
			return _value;
		}
	};
}