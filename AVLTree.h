#pragma once

#include <iostream>
using namespace std;
#include <stdlib.h>

template <class K,class V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key,const V& value)
	:_pLeftChild(NULL)
	, _pRightChild(NULL)
	, _pParent(NULL)
	, _key(key)
	, _value(value)
	, _bf(0)
	{}
	AVLTreeNode<K, V>* _pLeftChild;
	AVLTreeNode<K, V>* _pRightChild;
	AVLTreeNode<K, V>* _pParent;
	K _key;
	V _value;
	int _bf;
};

template <class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
	typedef AVLTreeNode<K, V>* pNode;
public:

	AVLTree()
		:_pRoot(NULL)
	{}

	//����
	bool Insert(const K& key, const V& value)
	{
		//�����Ĳ���
		if (_pRoot == NULL)
		{
			_pRoot = new Node(key, value);
			return true;
		}
		pNode parent = NULL;
		pNode cur = _pRoot;

		//Ѱ�Ҵ�����ڵ��λ��
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_pLeftChild;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_pRightChild;
			}
			else
				return false;
		}
		//����ڵ�
		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_pRightChild = cur;
			cur->_pParent = parent;
		}
		else
		{
			parent->_pLeftChild = cur;
			cur->_pParent = parent;
		}
		//������
		while (parent)
		{
			if (parent->_pRightChild == cur)
				parent->_bf++;
			else
				parent->_bf--;
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_pParent;
			}
			else 
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)//����ڵ�λ���Һ��Ӵ�
						RotateL(parent);
					else
						RotateRL(parent);
				}
				else
				{
					if (cur->_bf == -1)
						RotateR(parent);
					else
						RotateLR(parent);
				}
				break;
			}
		}
		return true;
	}

	//�������
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}

	//�ж��Ƿ�Ϊƽ�������
	bool IsBalance()
	{
		return _IsBalance(_pRoot);
	}

	//�����ĸ߶�
	int Height()
	{
		return _Height(_pRoot);
	}

private:

	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeftChild);
			cout << "<" << pRoot->_key << "," << pRoot->_value << ">" << endl;
			_InOrder(pRoot->_pRightChild);
		}
	}

	int _Height(pNode pRoot)
	{
		if (pRoot == NULL)
			return 0;

		int leftHeight = _Height(pRoot->_pLeftChild);
		int rightHeight = _Height(pRoot->_pRightChild);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
	bool _IsBalance(pNode pRoot)
	{
		if (pRoot == NULL)
			return true;

		int leftHeight = _Height(pRoot->_pLeftChild);
		int rightHeight = _Height(pRoot->_pRightChild);

		if (abs(leftHeight - rightHeight) >= 2)
			return false;

		return _IsBalance(pRoot->_pLeftChild) && _IsBalance(pRoot->_pRightChild);
	}

	//����
	void RotateL(pNode parent)
	{
		pNode subR = parent->_pRightChild;
		pNode subRL = subR->_pLeftChild;

		parent->_pRightChild = subRL;
		if (subRL)
			subRL->_pParent = parent;
		
		subR->_pLeftChild = parent;
		pNode pparent = parent->_pParent;
		subR->_pParent = pparent;
		parent->_pParent = subR;

		if (parent == _pRoot)
		{
			_pRoot = subR;
		//	subR->_pParent = NULL;
		}
		else//�����游�ڵ�����Һ���
		{
			if (pparent->_pLeftChild == parent)
				pparent->_pLeftChild = subR;
			else
				pparent->_pRightChild = subR;
		}
		parent->_bf = subR->_bf = 0;
	}

	//�ҵ���
	void RotateR(pNode parent)
	{
		pNode subL = parent->_pLeftChild;
		pNode subLR = subL->_pRightChild;

		parent->_pLeftChild = subLR;
		if (subLR)
			subLR->_pParent = parent;

		subL->_pRightChild = parent;
		pNode pparent = parent->_pParent;
		parent->_pParent = subL;
		subL->_pParent = pparent;

		if (parent == _pRoot)
		{
			_pRoot = subL;
		//	subL->_pParent = NULL;
		}
		else
		{
			if (pparent->_pLeftChild == parent)
				pparent->_pLeftChild = subL;
			else
				pparent->_pRightChild = subL;
		}
		parent->_bf = subL->_bf = 0;
	}

	//����˫��
	void RotateRL(pNode parent)
	{
		pNode pSubR = parent->_pRightChild;
		pNode pSubRL = NULL;
		if (pSubR!=NULL)
			pSubRL = pSubR->_pLeftChild;

		RotateR(parent->_pRightChild);
		RotateL(parent);

		if (pSubRL->_bf == 1)
			parent->_bf = -1;
		else if (pSubRL->_bf == -1)
			parent->_bf = 0;
	}

	//����˫��
	void RotateLR(pNode parent)
	{
		pNode pSubL = parent->_pLeftChild;
		pNode pSubLR = NULL;
		if (pSubL)
			pSubLR = pSubL->_pRightChild;

		RotateL(parent->_pLeftChild);
		RotateR(parent);

		if (pSubLR->_bf == 1)
			parent->_bf = 0;
		else if (pSubLR->_bf == -1)
			parent->_bf = 1;
	}

private:
	pNode _pRoot;
};

