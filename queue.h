#pragma once
#include "List.h"

//模板参数
template<class T,class Container=List<T>>
class Queue1
{
public:
	Queue1()
	{}
	void Push(const T& data)
	{
		s.PushBack(data);
	}
	void Pop()
	{
		s.PopFront();
	}
	bool Empty()
	{
		return s.Empty();
	}
	size_t Size()
	{
		return s.Size();
	}
	T& Front()
	{
		return s.Front();
	}
	const T& Front()const
	{
		return s.Front();
	}
	T& Back()
	{
		return s.Back();
	}
	const T& Back()const
	{
		return s.Back();
	}
private:
	List<T> s;
};

//模板的模板参数
template<class T, template<class> class Container = List>
class Queue2
{
public:
	Queue2()
	{}
	void Push(const T& data)
	{
		s.PushBack(data);
	}
	void Pop()
	{
		s.PopFront();
	}
	bool Empty()
	{
		return s.Empty();
	}
	size_t Size()
	{
		return s.Size();
	}
	T& Front()
	{
		return s.Front();
	}
	const T& Front()const
	{
		return s.Front();
	}
	T& Back()
	{
		return s.Back();
	}
	const T& Back()const
	{
		return s.Back();
	}
private:
	List<T> s;
};