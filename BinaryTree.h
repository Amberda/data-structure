#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <queue>
#include <stack>

template <class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
	:_pLeft(NULL)
	, _pRight(NULL)
	, _data(data)
	{}

	BinaryTreeNode<T>* _pLeft;
	BinaryTreeNode<T>* _pRight;
	T _data;
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T>* pNode;
	typedef BinaryTreeNode<T> Node;
public:
	//�޲ι��캯��
	BinaryTree()
		: _pRoot(NULL)
	{}
	//�������Ĺ��캯��
	BinaryTree(T* arr, size_t size, const T& invalid)
	{
		size_t index = 0;
		_CreateBinaryTree(_pRoot, arr, size, index, invalid);
	}
	//�������캯��
	BinaryTree(const BinaryTree<T>& bt)
	{
		_pRoot = _CopyBinaryTree(bt._pRoot);
	}
	//��ֵ���������
	//BinaryTree& operator=(const BinaryTree<T>& bt)
	//{
	//	if (this != &bt)
	//	{
	//		_DestoryBinaryTree(_pRoot);
	//		_pRoot = _CopyBinaryTree(bt._pRoot);
	//	}
	//	return *this;
	//}
	BinaryTree& operator=(const BinaryTree<T>& bt)
	{
		swap(_pRoot, bt._pRoot);
		return *this;
	}
	//��������
	~BinaryTree()
	{
		_DestoryBinaryTree(_pRoot);
	}
	//�ݹ�ǰ�����
	void PreOrder()
	{
		_PreOrder(_pRoot);
		cout << endl;
	}
	//�ݹ��������
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}
	//�ݹ�������
	void PostOrder()
	{
		_PostOrder(_pRoot);
		cout << endl;
	}
	//�������(�ö���)
	void LevelOrder()
	{
		queue<pNode> q;
		if (_pRoot)
			q.push(_pRoot);
		while (!q.empty())
		{
			pNode cur = q.front();
			q.pop();
			cout << cur->_data << " ";
			if (cur->_pLeft)
			{
				q.push(cur->_pLeft);
			}
			if (cur->_pRight)
			{
				q.push(cur->_pRight);
			}
		}
		cout << endl;
	}
	//�ǵݹ�ǰ�����
	void PreOrderNoR()
	{
		_PreOrderNoR2(_pRoot);
	}
	//�ǵݹ��������
	void InOrderNoR()
	{
		_InOrderNoR(_pRoot);
	}
	//�ǵݹ�������
	void PostOrderNoR()
	{
		_PostOrderNoR(_pRoot);
	}
	//�������ڵ����
	size_t Size()
	{
		return _Size(_pRoot);
	}
	//������Ҷ�ӽڵ����
	size_t LeafSize()
	{
		return _LeafSize(_pRoot);
	}
	//��������K��ڵ����
	size_t KSize(size_t k)
	{
		return _KSize(_pRoot, k);
	}
	//�������߶�
	size_t Height()
	{
		return _Height(_pRoot);
	}
	//Ѱ�Ҷ������еĽڵ�
	pNode Find(const T& data)
	{
		return _Find(_pRoot, data);
	}
	//Ѱ��ĳ�ڵ��˫�׽ڵ�
	pNode FindParent(pNode node)
	{
		return _FindParent(_pRoot, node);
	}
	//Ѱ��ĳ�ڵ�����ӽڵ�
	pNode FindLeftChild(pNode node)
	{
		return _FindLeftChild(_pRoot, node);
	}
	//Ѱ��ĳ�ڵ���Һ��ӽڵ�
	pNode FindRightChild(pNode node)
	{
		return _FindRightChild(_pRoot, node);
	}
	//�ж϶������Ƿ�Ϊ��ȫ������
	bool IsCompleteTree()
	{
		queue<pNode> q;
		if (_pRoot)//���ڵ㲻Ϊ�������
		{
			q.push(_pRoot);
		}
		while (!q.empty())
		{
			pNode front = q.front();//ȡ�����ײ�Ԫ��
			q.pop();
			if (front)//�жϣ���Ϊ�վͰѸýڵ�����Ӻ��Һ��������
			{
				q.push(front->_pLeft);
				q.push(front->_pRight);
			}
			else//Ϊ�վ�����ѭ��
				break;
		}
		while (!q.empty())
		{
			pNode front = q.front();
			q.pop();
			if (front == NULL)//�����ж��ײ�Ԫ�أ���ֱ�����п�ȡ���Ķ��ǿգ���Ϊ��ȫ������
				q.pop();
			else
				return false;
		}
		return true;
	}
	//�ݹ�ʵ�ֶ���������
	void Mirror()
	{
		_Mirror(_pRoot);
	}
	//�ǵݹ�ʵ�ֶ���������
	void MirrorNoR()
	{
		_MirrorNoR(_pRoot);
	}


	//��װ����
private:
	//����������(ǰ�����)
	void _CreateBinaryTree(pNode& pRoot, T* arr, size_t size, size_t& index, const T& invalid)
	{
		if (index < size&&invalid != arr[index])
		{
			pNode pNewNode = new Node(arr[index]);
			_CreateBinaryTree(pNewNode->_pLeft, arr, size, ++index, invalid);
			_CreateBinaryTree(pNewNode->_pRight, arr, size, ++index, invalid);
			pRoot = pNewNode;
		}
	}
	//����������
	pNode _CopyBinaryTree(pNode pRoot)
	{
		if (pRoot == NULL);
		{
			return NULL;
		}
		pNode tmp = new Node(pRoot->_data);
		tmp->_pLeft = _CopyBinaryTree(pRoot->_pLeft);
		tmp->_pRight = _CopyBinaryTree(pRoot->_pRight);
		return tmp;
	}
	//�ݹ�ǰ�����
	void _PreOrder(pNode pRoot)
	{
		if (pRoot)
		{
			cout << pRoot->_data << " ";
			_PreOrder(pRoot->_pLeft);
			_PreOrder(pRoot->_pRight);
		}
	}
	//�ݹ��������
	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
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
	//�ǵݹ�ǰ�����(���ʸ�֮��ֱ�ӷ���������������)
	void _PreOrderNoR(pNode pRoot)
	{
		stack<pNode> s;
		pNode cur = pRoot;
		while (cur || !s.empty())
		{	
			while (cur)
			{
				cout << cur->_data << " ";
				s.push(cur);
				cur = cur->_pLeft;
			}//��ʱ������������
			//ȡջ��Ԫ�ط���������(��ʱջ��Ԫ���Ѿ�����)
			pNode top = s.top();
			s.pop();
			//������
			cur = top->_pRight;
		}
		cout << endl;
	}
	void _PreOrderNoR2(pNode pRoot)
	{
		if (pRoot == NULL)
			return;
		stack<pNode> s;
		s.push(pRoot);//���ڵ���ջ
		while (!s.empty())
		{
			pNode top = s.top();
			cout << top->_data << " ";
			s.pop();
			if (top->_pRight)//��ѹ������
				s.push(top->_pRight);
			if (top->_pLeft)//��ѹ������
				s.push(top->_pLeft);
		}
		cout << endl;
	}
	//�ǵݹ��������
	void _InOrderNoR(pNode pRoot)
	{
		stack<pNode> s;
		pNode cur = pRoot;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_pLeft;
			}//ֱ������ڵ�
			//ȡջ��Ԫ�ط��ʸ�Ԫ�ز�����������
			pNode top = s.top();
			cout << top->_data << " ";
			s.pop();
			//������
			cur = top->_pRight;
		}
		cout << endl;
	}
	//�ǵݹ�������
	void _PostOrderNoR(pNode pRoot)
	{
		stack<pNode> s;
		pNode cur = pRoot;
		pNode prev = NULL;//���������ʹ��Ľڵ�
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_pLeft;
			}//ֱ������ڵ�

			pNode top = s.top();//ȡջ��Ԫ��
			if (top->_pRight == NULL || top->_pRight == prev)//�жϸýڵ���������Ƿ�Ϊ��
			{												 //���ж��ǲ��ǵ�һ����ջ��ȡ����Ԫ�� 
				cout << top->_data << " ";
				prev = top;
				s.pop();
			}
			else//��Ϊ�գ�����������
			{
				cur = top->_pRight;
			}
		}
		cout << endl;
	}
	//��������ݹ����ٶ�����
	void _DestoryBinaryTree(pNode pRoot)
	{
		if (pRoot)
			return;
		_DestoryBinaryTree(pRoot->_pLeft);
		_DestoryBinaryTree(pRoot->_pRight);
		delete pRoot;
		pRoot = NULL;
	}
	//��ڵ����
	size_t _Size(pNode pRoot)
	{
		if (!pRoot)
		{
			return 0;
		}
		return _Size(pRoot->_pLeft) + _Size(pRoot->_pRight) + 1;
	}
	//��Ҷ�ӽڵ����
	size_t _LeafSize(pNode pRoot)
	{
		if (!pRoot)
			return 0;
		if (pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
			return 1;
		return _LeafSize(pRoot->_pLeft) + _LeafSize(pRoot->_pRight);
	}
	//���K��ڵ�ĸ���
	size_t _KSize(pNode pRoot, size_t k)
	{
		if (pRoot == NULL)
			return 0;
		if (k == 1)
			return 1;
		return _KSize(pRoot->_pLeft, k - 1) + _KSize(pRoot->_pRight, k - 1);
	}
	//��������߶�
	size_t _Height(pNode pRoot)
	{
		if (!pRoot)
			return 0;
		if (pRoot->_pLeft == NULL&&pRoot->_pRight == NULL)
			return 1;
		size_t LeftHeight = _Height(pRoot->_pLeft);
		size_t RightHeight = _Height(pRoot->_pRight);
		return LeftHeight > RightHeight ? LeftHeight + 1 : RightHeight + 1;
	}
	//�Ҷ������еĽڵ�
	pNode _Find(pNode pRoot, const T& data)
	{
		if (pRoot == NULL)
			return NULL;
		if (pRoot->_data == data)
			return pRoot;
		pNode ret = NULL;
		ret = _Find(pRoot->_pLeft, data);
		if (ret)
			return ret;
		return _Find(pRoot->_pRight, data);
	}
	//�Ҷ������нڵ��˫�׽ڵ�
	pNode _FindParent(pNode pRoot, pNode node)
	{
		//��Ϊ����   Ѱ�ҵĽڵ�Ϊ�սڵ�   Ѱ�ҵĽڵ��Ǹ��ڵ�(��˫�׽ڵ�)
		if (pRoot == NULL || node == NULL || pRoot == node)
		{
			return NULL;
		}
		if (node == pRoot->_pLeft || node == pRoot->_pRight)
			return pRoot;
		if (pRoot->_pLeft)
			return _FindParent(pRoot->_pLeft, node);
		return _FindParent(pRoot->_pRight, node);
	}
	//Ѱ�ҽڵ������
	pNode _FindLeftChild(pNode pRoot, pNode node)
	{
		if (node == NULL || pRoot == NULL)
		{
			return NULL;
		}
		pNode cur = _Find(pRoot, node->_data);
		return cur->_pLeft;
	}
	//Ѱ�ҽڵ���Һ���
	pNode _FindRightChild(pNode pRoot, pNode node)
	{
		if (node == NULL || pRoot == NULL)
		{
			return NULL;
		}
		pNode cur = _Find(pRoot, node->_data);
		return cur->_pRight;
	}
	//�������ľ���(�ݹ�)
	void _Mirror(pNode pRoot)
	{
		if (pRoot == NULL)
			return;
		if (pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
			return;

		pNode tmp = pRoot->_pLeft;
		pRoot->_pLeft = pRoot->_pRight;
		pRoot->_pRight = tmp;

		if (pRoot->_pLeft)
			_Mirror(pRoot->_pLeft);
		if (pRoot->_pRight)
			_Mirror(pRoot->_pRight);
	}
	//�������ľ���(�ǵݹ�)
	void _MirrorNoR(pNode pRoot)
	{
		if (pRoot == NULL)
			return;
		queue<pNode> q;
		q.push(pRoot);
		while (!q.empty())
		{
			pNode front = q.front();
			if (front->_pLeft)
				q.push(front->_pLeft);
			if (front->_pRight)
				q.push(front->_pRight);
			swap(front->_pLeft, front->_pRight);
			q.pop();
		}
	}

private:
	pNode _pRoot;
};