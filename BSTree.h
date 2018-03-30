#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>

template <class K,class V>
struct BSTreeNode
{
	BSTreeNode<K, V>* _pLeftChild;
	BSTreeNode<K, V>* _pRightChild;
	BSTreeNode<K, V>* _pParent;

	K _key;
	V _value;

	BSTreeNode(const K& key, const V& value)
		:_pLeftChild(NULL)
		, _pRightChild(NULL)
		, _pParent(NULL)
		, _key(key)
		, _value(value)
	{}
};

//迭代器
template <class K, class V>
struct BSTreeIterator
{
	typedef BSTreeNode<K, V>*  pNode;
	typedef BSTreeIterator<K, V> Self;

	BSTreeIterator()
		:_pHead(NULL)
		, _pNode(NULL)
	{}

	BSTreeIterator(pNode pHead, pNode pNode)
		:_pHead(pHead)
		, _pNode(pNode)
	{}

	BSTreeIterator(Self& it)
	{
		_pHead = it._pHead;
		_pNode = it._pNode;
	}

	Self &operator++()
	{
		Increase();
		return *this;
	}

	Self& operator++(int)
	{
		Self tmp(*this);
		Increase();
		return tmp;
	}

	Self &operator--()
	{
		Decrease();
		return *this;
	}

	Self& operator--(int)
	{
		Self tmp(*this);
		Decrease();
		return tmp;
	}

	bool operator==(const Self& s)
	{
		return s._pNode == _pNode;
	}

	bool operator!=(const Self& s)
	{
		return _pNode != s._pNode;;
	}

	K operator*()
	{
		return _pNode->_key;
	}

	pNode operator->()
	{
		return _pNode;
	}

	void Increase()
	{
		if (_pNode->_pRightChild != NULL)//当前节点存在右子树
		{
			//找右子树中的最左节点
			_pNode = _pNode->_pRightChild;
			while (_pNode->_pLeftChild)
				_pNode = _pNode->_pLeftChild;
		}
		else
		{
			pNode parent = _pNode->_pParent;
			while (_pNode == parent->_pRightChild)
			{
				_pNode = parent;
				parent = _pNode->_pParent;
			}
			if (parent != _pNode->_pRightChild)
				_pNode = parent;
		}
	}
	void Decrease()
	{
		if (_pHead == _pNode)//节点在end的位置
			_pNode = _pNode->_pRightChild;
		else if (_pNode->_pLeftChild != NULL)//该节点存在左子树
		{
			_pNode = _pNode->_pLeftChild;
			while (_pNode->_pRightChild)
				_pNode = _pNode->_pRightChild;
		}
		else
		{
			pNode parent = _pNode->_pParent;
			while (_pNode == parent->_pLeftChild)
			{
				_pNode = parent;
				parent = _pNode->_pParent;
			}
			_pNode = parent;
		}
	}

private:
	pNode _pHead;
	pNode _pNode;
};



#if 1
template <class K,class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
	typedef BSTreeNode<K, V>* pNode;
public:
	//构造函数
	BSTree()
	{
		_pRoot = NULL;
	}
	//中序遍历
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}
	//插入---非递归
	bool Insert(const K& key, const V& value)
	{
		if (_pRoot == NULL)
		{
			_pRoot = new Node(key, value);
			return true;
		}
		pNode parent = NULL;
		pNode cur = _pRoot;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_pRightChild;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_pLeftChild;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_pLeftChild = cur;
		}
		else
		{
			parent->_pRightChild = cur;
		}
		return true;
	}
	
	//删除---非递归
	bool DelNode(const K& key)
	{
		if (_pRoot == NULL)
			return false;
		pNode cur = _pRoot;
		pNode parent = NULL;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_pRightChild;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_pLeftChild;
			}
			else
				break;
		}
		pNode del = cur;
		//1.左为空
		if (del->_pLeftChild == NULL)
		{
			if (parent == NULL)
				_pRoot = del->_pRightChild;
			else
			{
				if (parent->_pLeftChild == del)
					parent->_pLeftChild = del->_pRightChild;
				else
					parent->_pRightChild = del->_pRightChild;
			}
		}
		//2.右为空
		else if (del->_pRightChild == NULL)
		{
			if (parent == NULL)
				_pRoot = del->_pLeftChild;
			else
			{
				if (parent->_pLeftChild = del)
					parent->_pLeftChild = del->_pLeftChild;
				else
					parent->_pRightChild = del->_pLeftChild;
			}
		}
		//3.左右都不为空
		else
		{
			pNode firstInRight = del->_pRightChild;//用右子树中序遍历的最左节点来替换左右孩子都存在的节点
			pNode parent = del;
			while (firstInRight->_pLeftChild)
			{
				parent = firstInRight;
				firstInRight = firstInRight->_pLeftChild;
			}
			del->_key = firstInRight->_key;
			del->_value = firstInRight->_value;
			if (parent->_pLeftChild == firstInRight)
				parent->_pLeftChild = firstInRight->_pRightChild;
			else
				parent->_pRightChild = firstInRight->_pRightChild;
			del = firstInRight;
		}
		delete del;
		return true;
	}

	//查找
	pNode Find(const K& key)
	{
		pNode cur = _pRoot;
		while (cur)
		{
			if (cur->_key == key)
				return cur;
			else if (cur->_key > key)
				cur = cur->_pLeftChild;
			else
				cur = cur->_pRightChild;
		}
		return NULL;
	}

	//把二叉搜索树转为有序的单向链表
	pNode BSTtoList()
	{
		if (_pRoot == NULL)
			return NULL;
		
		pNode pHead = _pRoot;
		while (pHead->_pLeftChild)
		{
			pHead = pHead->_pLeftChild;//找最左节点，为链表的头结点
		}

		pNode prev = NULL;
		_BSTtoList(_pRoot, prev);

		return pHead;
	}

	//获取二叉搜索树的最左节点
	K MostLNode()
	{
		pNode cur = _pRoot;
		if (cur == NULL)
		{
			return NULL;
		}
		while (cur->_pLeftChild)
		{
			cur = cur->_pLeftChild;
		}
		return cur->_key;
	}

	//获取二叉搜索树的最右节点
	K MostRNode()
	{
		pNode cur = _pRoot;
		if (cur == NULL)
		{
			return NULL;
		}
		while (cur->_pRightChild)
		{
			cur = cur->_pRightChild;
		}
		return cur->_key;
	}
	void _BSTtoList(pNode pRoot, pNode& prev)
	{
		if (pRoot == NULL)
			return;

		_BSTtoList(pRoot->_pLeftChild, prev);

		pRoot->_pLeftChild = prev;
		if (prev)
			prev->_pRightChild = pRoot;
		prev = pRoot;

		_BSTtoList(pRoot->_pRightChild, prev);
	}

private:
	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeftChild);
			cout << pRoot->_key << " ";
			_InOrder(pRoot->_pRightChild);
		}
	}

private:
	BSTreeNode<K, V>* _pRoot;
};
#endif

#if 0
//递归版本
template <class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
	typedef BSTreeNode<K, V>* pNode;
public:

	BSTree()
		:_pRoot(NULL)
	{}

	//中序遍历
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}

	pNode Find(const K& key)
	{
		pNode cur = NULL;
		cur = _Find(_pRoot, key);
		return cur;
	}
	pNode _Find(pNode& pRoot, const K& key, const V& value)
	{
		if (pRoot->_key == key)
			return pRoot;
		else
		{
			_Find(pRoot->_pLeftChild, key, value);

		}
	}

	bool Insert(const K& key, const V& value)
	{
		return _Insert(_pRoot, key, value);
	}
	bool _Insert(pNode& pRoot, const K& key, const V& value)
	{
		if (NULL == pRoot)
		{
			pRoot = new Node(key, value);
			return true;
		}
		else
		{
			if (key < pRoot->_key)
				_Insert(pRoot->_pLeftChild, key, value);
			else if (key>pRoot->_key)
				_Insert(pRoot->_pRightChild, key, value);
			else
				return false;
		}
	}

	bool Delete(const K& key)
	{
		return _Delete(_pRoot, key);
	}
	bool _Delete(pNode& pRoot, const K& key)
	{
		if (pRoot == NULL)
			return false;
		if (pRoot->_key < key)
			return _Delete(pRoot->_pRightChild, key);
		else if (pRoot->_key>key)
			return _Delete(pRoot->_pLeftChild, key);
		else
		{
			pNode del = pRoot;
			if (del->_pLeftChild == NULL)
				pRoot = pRoot->_pRightChild;
			else if (del->_pRightChild == NULL)
				pRoot = pRoot->_pLeftChild;
			else
			{
				pNode FirstOfIn = pRoot->_pRightChild;
				while (FirstOfIn->_pLeftChild)
					FirstOfIn = FirstOfIn->_pLeftChild;
				del->_key = FirstOfIn->_key;
				del->_value = FirstOfIn->_value;
				del = FirstOfIn;
				return _Delete(pRoot->_pRightChild, key);
			}
			delete del;
			return true;
		}
	}

	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeftChild);
			cout << pRoot->_key << " ";
			_InOrder(pRoot->_pRightChild);
		}
	}
private:
	pNode _pRoot;
};
#endif