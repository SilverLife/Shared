// ☕ Привет
#pragma once

#include <vector>
#include <iostream>

namespace Shared
{
	namespace Containers
	{
		template <class T>
		class RoundList
		{
			std::vector<T> _elems;
			int _index = 0;
			
			int LastIndex() const { return (_index == 0 ? _elems.size() - 1 : _index - 1); }

		public:
			RoundList()
			{
				_elems.reserve(100);
			}

			void MoveToNext()
			{
				_index = (_index + 1) % _elems.size();
			}
			
			void MoveToPrev()
			{
				if (_index == 0)
				{
					_index = _elems.size() - 1;
				}
				else
				{
					_index = (_index - 1) % (int)_elems.size();
				}
			}

			void PushAfterLast(const T& t)
			{
				_elems.insert(_elems.begin() + _index, t);
				_index = (_index + 1) % _elems.size();
			}

			template<typename ... Type>
			void EmplaceAfterLast(Type... args)
			{
				_elems.emplace(_elems.begin() + _index, std::forward<Type>(args)...);
				_index = (_index + 1) % _elems.size();
			}

			T& First() { return _elems[_index]; }
			const T& First() const { return _elems[_index]; }

			T& Last()  { return _elems.operator[](LastIndex()); }
			const T& Last() const { return _elems.operator[](LastIndex()); }

			void PushBeforeFirst(const T& t)
			{
				_elems.insert(_elems.begin() + _index, t);
			}

			auto Size() const { return _elems.size(); }

			T& operator[](int index_offset)
			{
				return _elems.operator[]((_index + index_offset) % _elems.size());
			}

			class Iterator
			{
				friend RoundList;

				RoundList* _list;
				int _pos;
			public:
				Iterator(RoundList* list, int pos)
					: _list(list),
					_pos(pos)
				{}

				bool operator!=(const Iterator& it) const
				{
					return (_list != it._list || _pos != it._pos);
				}

				bool operator==(const Iterator& it) const
				{
					return (_list == it._list && _pos == it._pos);
				}

				void operator++()
				{
					++_pos;
				}
				
				T& operator*() { return  _list->operator[](_pos); }
				const T& operator*() const { return  _list->operator[](_pos); }
			};

			Iterator begin()  { return Iterator(this, 0); }
			Iterator end()    { return Iterator(this, _elems.size()); }

			void EraseToLast(const Iterator& it)
			{
 				const int real_index = (_index + it._pos) % _elems.size();

				if (real_index >= _index)
				{
					_elems.erase(_elems.begin() + real_index, _elems.end());
					_elems.erase(_elems.begin(), _elems.begin() + _index);
					_index = 0;
					return;
				}

				_elems.erase(_elems.begin() + real_index, _elems.begin() + _index);
				_index = real_index;
			}

			Iterator Find(const T& elem)
			{
				auto result_it = begin();
				const auto end_it = end();
				for (; result_it != end_it; ++result_it)
				{
					if (*result_it == elem)
					{
						break;
					}
				}
				return result_it;
			}
		};

		
	}
}