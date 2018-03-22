#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdlib.h>
#include <iostream>
using namespace std;


template<class T>
struct ListNode
{
	ListNode(const T& data = T())
	: _pPre(0)
	, _pNext(0)
	, _data(data)
	{}

	ListNode<T>* _pPre;
	ListNode<T>* _pNext;
	T _data;
};

template<class T,class Ref,class Ptr>
class ListIterator
{
	typedef ListIterator<T, Ref, Ptr> Self;
public:
	ListIterator()
		:_pCur(0)
	{}

	ListIterator(ListNode<T>* pCur)
		: _pCur(pCur)
	{}

	ListIterator(const Self& s)
		: _pCur(s._pCur)
	{}

	Ref operator*()
	{
		return _pCur->_data;
	}

	Ptr operator->()
	{
		return &(operator*());
		//return &(_pCur->_data); 
	}

	Self& operator++()
	{
		_pCur = _pCur->_pNext;
		return*this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		_pCur = _pCur->_pNext;
		return temp;
	}

	Self& operator--()
	{
		_pCur = _pCur->_pPre;
		return*this;
	}

	Self operator--(int)
	{
		Self temp(*this);
		_pCur = _pCur->_pPre;
		return temp;
	}

	bool operator!=(const Self& s)
	{
		return _pCur != s._pCur;
	}

	bool operator==(const Self& s)
	{
		return _pCur == s._pCur;
	}

	ListNode<T>* _pCur;
};

template <class T>
class List
{
public:
	typedef ListIterator<T, T&, T*> Iterator;
	typedef ListNode<T> Node;
public:
	List()
		: _pHead(new Node)
	{
		_pHead->_pNext = _pHead;//带头节点的循环链表
		_pHead->_pPre = _pHead;
	}

	// 1 2 3 4 5 
	List(const T* array, size_t size)
		:_pHead(new Node)
	{
		_pHead->_pNext = _pHead;
		_pHead->_pPre = _pHead;
		for (size_t i = 0; i < size; i++)
		{
			PushBack(array[i]);
		}
	}
	List(const List<T>& l)
		:_pHead(new Node)
	{
		_pHead->_pNext = _pHead;
		_pHead->_pPre = _pHead;
		Node* cur = l._pHead->_pNext;
		for (size_t i = 0; i < l.Size();i++)
		{
			PushBack(cur->_data);
			cur = cur->_pNext;
		}

	}
	List<T>& operator=(const List<T>& l)
	{
		if (this != &l)
		{
			Node* pRet = l._pHead->_pNext;
			for (size_t i = 0; i < l.Size(); i++)
			{
				PushBack(pRet->_data);
				pRet = pRet->_pNext;
			}
		}
		return *this;
	}
	~List()
	{
		Clear();
		delete _pHead;
		_pHead = NULL;
	}

		///////////////////////////////////////////////////// 
	Iterator Begin()
	{
		return Iterator(_pHead->_pNext);
	}

	Iterator End()
	{
		return Iterator(_pHead);
	}
	/////////////////////Modify////////////////////////// 
	void PushBack(const T& data)
	{
		Node* _pNewNode = new Node(data);
		if (Empty())//链表为空
		{
			_pHead->_pNext = _pNewNode;
			_pHead->_pPre = _pNewNode;
			_pNewNode->_pNext = _pHead;
			_pNewNode->_pPre = _pHead;
		}
		else
		{
			Node* pTail = _pHead->_pPre;
			pTail->_pNext = _pNewNode;
			_pNewNode->_pNext = _pHead;
			_pNewNode->_pPre = pTail;
			_pHead->_pPre = _pNewNode;
		}
	}
	void PopBack()
	{
		if (Empty())//链表为空
		{
			return;
		}
		else
		{
			Node* del = _pHead->_pPre;//要删除的节点
			Node* tail = del->_pPre;//新的尾节点
			delete del;
			tail->_pNext = _pHead;
			_pHead->_pPre = tail;
		}
	}
	void PushFront(const T& data)
	{
		Node* _pNewNode = new Node(data);
		_pHead->_pNext->_pPre = _pNewNode;
		_pNewNode->_pNext = _pHead->_pNext;
		_pNewNode->_pPre = _pHead;
		_pHead->_pNext = _pNewNode;
	}
	void PopFront()
	{
		if (Empty())
		{
			return;
		}
		else
		{
			Node* pDel = _pHead->_pNext;
			_pHead->_pNext = pDel->_pNext;
			pDel->_pNext->_pPre = _pHead;
			delete pDel;
		}
	}
	Iterator Insert(Iterator pos, const T& data)
	{
		Node* _pNewNode = new Node(data);
		pos._pCur->_pPre->_pNext = _pNewNode;
		_pNewNode->_pNext = pos._pCur;
		_pNewNode->_pPre = pos._pCur->_pPre;
		pos._pCur->_pPre = _pNewNode;
		return Iterator(_pNewNode);
	}
	Iterator Erase(Iterator pos)
	{
		Node* pCur = pos._pCur->_pNext;
		pos._pCur->_pNext->_pPre = pos._pCur->_pPre;
		pos._pCur->_pPre->_pNext = pos._pCur->_pNext;
		delete pos._pCur;
		return Iterator(pCur);
	}
	Iterator Find(const T& d)        //通过迭代器来查找
	{
		Iterator it = Begin();
		while (it != End())
		{
			if ((*it) == d)
				return it;
			it++;
		}
		return End();
	}
	bool Empty()const
	{
		return _pHead->_pNext == _pHead;
	}
	size_t Size()const
	{
		Node* pCur = _pHead->_pNext;
		size_t count = 0;
		while (pCur != _pHead)
		{
			++count;
			pCur = pCur->_pNext;
		}
		return count;
	}
	T& Front()
	{
		return _pHead->_pNext->_data;
	}
	const T& Front()const
	{
		return _pHead->_pNext->_data;
	}
	T& Back()
	{
		return _pHead->_pPre->_data;
	}
	const T& Back()const
	{
		return _pHead->_pPre->_data;
	}
	void Clear()
	{
		Iterator it = Begin();
		while (it != End())
		{
			it = Erase(it);
		}
		_pHead->_pNext = _pHead;
		_pHead->_pPre = _pHead;
	}
private:
	ListNode<T>* _pHead;
};
void PrintList( List<int>& l)
{
	List<int>::Iterator It = l.Begin();
	while (It != l.End())
	{
		cout << *It << " ";
		++It;
	}
	cout << endl;
}
