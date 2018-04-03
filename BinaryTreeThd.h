#pragma once

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string.h>

enum PointerTag
{
	THREAD,
	LINK
};

template<class T>
struct ThdBinaryTreeNode
{
	T _data;//����
	ThdBinaryTreeNode<T>* _pLeft;//����
	ThdBinaryTreeNode<T>* _pRight;//�Һ���
	PointerTag _leftTag;//������
	PointerTag _rightTag;//������

	ThdBinaryTreeNode(const T& data)
		:_data(data)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};

template<class T, class Ref, class Ptr>
class BinaryTreeIterator
{
	typedef ThdBinaryTreeNode<T>* pNode;
	typedef BinaryTreeIterator<T, Ref, Ptr> Self;
public:
	BinaryTreeIterator()
		:_node(NULL)
	{}
	BinaryTreeIterator(pNode node)
		:_node(node)
	{}
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &(operator*());
	}
	Self& operator++()
	{
		
	}

private:
	pNode _node;
};

template<class T>
class ThdBinaryTree
{
	typedef ThdBinaryTreeNode<T> Node;
	typedef ThdBinaryTreeNode<T>* pNode;
public:
	ThdBinaryTree()
		:_pRoot(NULL)
	{}
	ThdBinaryTree(T* arr, size_t size, const T& invalid)
	{
		size_t index = 0;
		_CreateThdBinaryTree(_pRoot, arr, size, index, invalid);
	}
	void PreOrder()
	{
		_PreOrder(_pRoot);
		cout << endl;
	}
	void PreOrderThreading()
	{
		pNode prev = NULL;
		_PreOrderThreading(_pRoot, prev);
	}
	void PreOrderThdNoR()
	{
		_PreOrderThdNoR(_pRoot);
	}
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}
	void InOrderThreading()
	{
		pNode prev = NULL;
		_InOrderThreading(_pRoot, prev);
	}
	void InOrderThdNoR()
	{
		_InOrderThdNoR(_pRoot);
	}
	void PostOrder()
	{
		_PostOrder(_pRoot);
		cout << endl;
	}
	void PostOrderThreading()
	{
		pNode prev = NULL;
		_PostOrderThreading(_pRoot, prev);
	}


private:
	void _CreateThdBinaryTree(pNode& pRoot, T* arr, size_t& size, size_t& index, const T& invalid)
	{
		if (index < size&&arr[index] != invalid)
		{
			pNode pNewNode = new Node(arr[index]);
			_CreateThdBinaryTree(pNewNode->_pLeft, arr, size, ++index, invalid);
			_CreateThdBinaryTree(pNewNode->_pRight, arr, size, ++index, invalid);
			pRoot = pNewNode;
		}
	}
	//�ݹ�ǰ��������
	void _PreOrderThreading(pNode pCur, pNode& prev)
	{
		if (pCur == NULL)
			return;
		//��������ǰ�ڵ����ָ����
		if (pCur->_pLeft == NULL)
		{
			pCur->_pLeft = prev;
			pCur->_leftTag = THREAD;
		}
		//������ǰһ���ڵ����ָ����
		if (prev&&prev->_pRight == NULL)//(��֤��һ��prevΪ��ʱ������)
		{
			prev->_pRight = pCur;
			prev->_rightTag = THREAD;
		}
		prev = pCur;
		if (pCur->_leftTag == LINK)
			_PreOrderThreading(pCur->_pLeft, prev);
		if (pCur->_rightTag == LINK)
			_PreOrderThreading(pCur->_pRight, prev);
	}
	//ǰ�����
	void _PreOrder(pNode pRoot)
	{
		if (pRoot)
		{
			cout << pRoot->_data << " ";
			if (pRoot->_leftTag == LINK)
				_PreOrder(pRoot->_pLeft);
			if (pRoot->_rightTag == LINK)
				_PreOrder(pRoot->_pRight);
		}
	}
	//�ǵݹ�ǰ�����(������)
	void _PreOrderThdNoR(pNode pCur)
	{
		while (pCur)
		{
			while (pCur->_leftTag == LINK)
			{
				cout << pCur->_data << " ";
				pCur = pCur->_pLeft;
			}
			cout << pCur->_data << " ";
			pCur = pCur->_pRight;//pCur�Ѿ��������ڵ���
		}
		cout << endl;
	}
	void _PreOrderThdNoR2(pNode pCur)
	{
		while (pCur)
		{
			//�������·���еĽڵ㲢����
			while (pCur->_leftTag == LINK)
			{
				cout << pCur->_data << " ";
				pCur = pCur->_pLeft;
			}
			cout << pCur->_data << " ";
			//��������һ��ĺ�̽ڵ�
			while (pCur->_rightTag == THREAD)
			{
				pCur = pCur->_pRight;
				cout << pCur->_data << " ";
			}
			if (pCur->_leftTag == LINK)
			{
				pCur = pCur->_pLeft;
			}
			else
				pCur = pCur->_pRight;
		}
		cout << endl;
	}
	//�ݹ�����������
	void _InOrderThreading(pNode pCur, pNode& prev)
	{
		if (pCur == NULL)
			return;
		_InOrderThreading(pCur->_pLeft, prev);
		//
		if (pCur->_pLeft == NULL)
		{
			pCur->_pLeft = prev;
			pCur->_leftTag = THREAD;
		}
		if (prev&&prev->_pRight == NULL)
		{
			prev->_pRight = pCur;
			prev->_rightTag = THREAD;
		}
		prev = pCur;
		_InOrderThreading(pCur->_pRight, prev);
	}
	//�������
	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}
	//�ǵݹ��������(������)
	void _InOrderThdNoR(pNode pCur)
	{
		while (pCur)
		{
			while (pCur->_leftTag == LINK)
			{
				pCur = pCur->_pLeft;
			}
			cout << pCur->_data << " ";
			while (pCur->_rightTag == THREAD)
			{
				pCur = pCur->_pRight;
				if (pCur == NULL)
				{
					cout << endl;
					return;
				}
				cout << pCur->_data << " ";
			}
			pCur = pCur->_pRight;
			//if (pCur->_rightTag == THREAD)
			//{
			//	while (pCur->_rightTag == THREAD)
			//	{
			//		pCur = pCur->_pRight;
			//		if (pCur == NULL)
			//		{
			//			cout << endl;
			//			return;
			//		}
			//		cout << pCur->_data << " ";
			//	}
			//}
			//else
			//{
			//	pCur = pCur->_pRight;
			//}
		}
		cout << endl;
	}
	//�ݹ�������
	void _PostOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_PostOrder(pRoot->_pLeft);
			_PostOrder(pRoot->_pRight);
			cout << pRoot->_data << " ";
		}
	}
	//�ݹ�������������
	void _PostOrderThreading(pNode pCur, pNode& prev)
	{
		if (pCur == NULL)
			return;
		_PostOrderThreading(pCur->_pLeft, prev);
		_PostOrderThreading(pCur->_pRight, prev);
		if (pCur->_pLeft == NULL)
		{
			pCur->_pLeft = prev;
			pCur->_leftTag = THREAD;
		}
		if (prev&&prev->_pRight == NULL)
		{
			prev->_pRight = pCur;
			prev->_rightTag = THREAD;
		}
		prev = pCur;
	}
	//�ǵݹ������������� 
	void _PostOrderThdNoR(pNode pRoot)
	{
		
	}

private:
	pNode _pRoot;
};