#pragma once

#include "StarWarsAPI.h"
#include <exception>

namespace Core
{
	/**
	* Самодельная очередь
	*/
	template <class T>
	class StarWarsObject Queue
	{
	private:
		int _size, _head, _tail, _count;
		T* _buffer;
	public:
		Queue(int size)
		{
			if (size < 1)
				throw std::exception("Size can not be less than 1");
			_size = size;
			_buffer = new T[_size];
			_head = 0;
			_tail = 0;
			_count = 0;
		}
		/**
		* Извлечь элемент из начала очереди
		*/
		T Dequeue()
		{
			if (_count == 0)
				throw std::exception("Queue is empty");
			T result = _buffer[_head];
			_head++;
			if (_head == _size)
			{
				_head = 0;
			}
			_count--;
			return result;
		}
		/**
		* Добавить элемент в конец очереди
		*/
		void Enqueue(T data)
		{
			if (_count == _size)
				return;
			_buffer[_tail] = data;
			_tail++;
			if (_tail == _size)
			{
				_tail = 0;
			}			
			_count++;
		}
		/**
		* Возвращает максимальный размер очереди
		*/
		int Size()
		{
			return _size;
		}
		/**
		* Указывает, является ли очередь пустой
		*/
		bool Empty()
		{
			return _count == 0;
		}
		/**
		* Возвращает текущее число элементов в очереди
		*/
		int Count()
		{
			return _count;
		}
		/**
		* Указывает, является ли очередь полностью заполненной
		*/
		bool Full()
		{
			return _count == _size;
		}
		~Queue()
		{
			if (_buffer != nullptr)
			{
				delete[] _buffer;
				_buffer = nullptr;
			}
		}
	};
}
