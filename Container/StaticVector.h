// ☕ Привет
#pragma once

#include <vector>
#include <iostream>
#include <cstddef>

namespace Shared
{
	namespace Containers
	{
		// Класс с интерфейсом вектора, который хранит данные на стеке. 
		// Имеет ограниченный объем
		template <class T, size_t kMaxSize = 10>
		class StaticVector
		{
			std::byte _data[kMaxSize * sizeof(T)];
			size_t _size = 0;

			void ThrowSizeOverflow()
			{
				throw std::length_error("Size of static vector >= max size");
			}

			void DestructElement(size_t i)
			{
				reinterpret_cast<T*>(&_data[i * sizeof(T)])->~T();
			}

			void ConstructElementByCopy(const T& t, size_t i)
			{
				new (&_data[i * sizeof(T)]) T(t);
			}
			
			void ConstructElementByCopy(T&& t, size_t i)
			{
				new (&_data[i * sizeof(T)]) T(std::move(t));
			}

			template <class... Args>
			void ConstructElementByCopy(size_t i, Args&&... args)
			{
				new (&_data[i * sizeof(T)]) T(std::forward<Args>(args)...);
			}


			const T& GetElem(size_t i) const
			{
				return *reinterpret_cast<const T*>(&_data[i * sizeof(T)]);
			}

		public:
			StaticVector() {}
			
			StaticVector(int start_size, const T& t = T())
			{
				if (start_size > kMaxSize)
				{
					ThrowSizeOverflow();
				}

				_size = start_size;
				for (int i = 0; i < _size; i++)
				{
					ConstructElementByCopy(t, i);
				}
			}
			
			StaticVector(std::initializer_list<T> args)
			{
				if (args.size() > kMaxSize)
				{
					ThrowSizeOverflow();
				}

				for (auto&& v : args)
				{
					ConstructElementByCopy(v, _size);
					_size++;
				}
			}
			
			StaticVector(const StaticVector& rhs)
			{
				_size = rhs._size;
				for (int i = 0; i < _size; i++)
				{
					ConstructElementByCopy(rhs.GetElem(i), i);
				}
			}
			
			~StaticVector()
			{
				clear();
			}

			size_t size() const { return _size; }
			size_t capacity() const { return kMaxSize; }

			void clear()
			{
				for (int i = 0; i < _size; i++)
				{
					DestructElement(i);
				}
				_size = 0;
			}
			
			
			void push_back(const T& t)
			{
				if (_size == kMaxSize)
				{
					ThrowSizeOverflow();
				}

				ConstructElementByCopy(t, _size);
				_size++;
			}

			void push_back(T&& t)
			{
				if (_size == kMaxSize)
				{
					ThrowSizeOverflow();
				}

				ConstructElementByCopy(std::move(t), _size);
				_size++;
			}

			template <class... Args>
			void emplace_back(Args&&... args)
			{
				if (_size == kMaxSize)
				{
					ThrowSizeOverflow();
				}

				ConstructElementByCopy(_size, std::forward<Args>(args)...);
				_size++;
			}
			

			void pop_back()
			{
				if (_size == 0)
				{
					throw std::length_error("Try pop empty static vector");
				}

				DestructElement(_size - 1);
				_size--;
			}

			void Print()
			{
				for (int i = 0; i < _size; i++)
				{
					std::cout << GetElem(i) << ' ';
				}
				std::cout << std::endl;
			}


		};


	}
}