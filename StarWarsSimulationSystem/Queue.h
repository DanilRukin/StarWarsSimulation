#pragma once

#include "StarWarsAPI.h"
#include <exception>

namespace Core
{
	/**
	* ����������� �������
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
		* ������� ������� �� ������ �������
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
		* �������� ������� � ����� �������
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
		* ���������� ������������ ������ �������
		*/
		int Size()
		{
			return _size;
		}
		/**
		* ���������, �������� �� ������� ������
		*/
		bool Empty()
		{
			return _count == 0;
		}
		/**
		* ���������� ������� ����� ��������� � �������
		*/
		int Count()
		{
			return _count;
		}
		/**
		* ���������, �������� �� ������� ��������� �����������
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
