#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <malloc.h>
#define Max 50
#define false 0
#define true 1
typedef struct Node
{
	char data;
	struct Node *Lchild;
	struct Node *Rchild;
}bitnode, *bitree;
typedef struct
{
	bitree stack[Max];  //用于存放栈中元素的一维数组
	int top;
}SeqStack;
void InitStack(SeqStack *s) //初始化栈
{
	s->top = -1;//构造一个空栈
}
int isempty(SeqStack *s)//判空
{
	if (s->top == -1)
		return true;
	else
		return false;
}
int push(SeqStack *s, bitree x)//入栈
{//将x置入S栈新栈顶
	if (s->top == Max - 1)//栈已满
		return(false);
	else
	{
		s->top++;
		s->stack[s->top] = x;
		return(true);
	}
}
int pop(SeqStack *s, bitree *x)
{//将S栈顶元素弹出，放到x所指的存储空间中带出
	if (s->top == -1)
		return(false);
	else
	{
		*x = s->stack[s->top];
		s->top--;//修改栈顶指针
		return(true);
	}
}
int GetTop(SeqStack *s, bitree *x)
{//将栈顶元素读出，放到x所指的存储空间中，栈顶指针保持不变
	if (s->top == -1)
		return true;
	else
	{
		*x = s->stack[s->top];
		return false;
	}
}
void preorder(bitree root)/*先序遍历二叉树*/
{
	SeqStack S; bitree p;
	InitStack(&S);
	p = root;
	printf("  先序遍历结果为：");
	while (p != NULL || !isempty(&S))
	{
		while (p != NULL)
		{
			printf("%c", (p->data));
			push(&S, p);
			p = p->Lchild;
		}
		if (!isempty(&S))
		{
			pop(&S, &p);
			p = p->Rchild;
		}
	}
}
void inorder(bitree root) /*中序遍历二叉树*/
{
	SeqStack S; bitree p;
	InitStack(&S);
	p = root;
	printf("  中序遍历结果为：");
	while (p != NULL || !isempty(&S))
	{
		if (p != NULL)
		{
			push(&S, p);
			p = p->Lchild;
		}
		else
		{
			pop(&S, &p);
			printf("%c", (p->data));
			p = p->Rchild;
		}
	}
}
void postorder(bitree root) /*后序遍历二叉树*/
{
	SeqStack S; bitree p, q;
	InitStack(&S);
	p = root;
	q = NULL;
	printf("  后序遍历结果为：");
	while (p != NULL || !isempty(&S))
	{
		if (p != NULL)
		{
			push(&S, p);
			p = p->Lchild;
		}
		else
		{
			GetTop(&S, &p);
			if (p->Rchild == NULL || p->Rchild == q)
			{
				printf("%c", (p->data));
				pop(&S, &p);
				q = p;
				p = NULL;
			}
			else
			{
				p = p->Rchild;
			}
		}
	}
}
bitree creatbitree()
{
	char ch;
	bitree bt;
	ch = getchar();
	if (ch == '.')
		bt = NULL;
	else
	{
		bt = (bitree)malloc(sizeof(bitnode));
		bt->data = ch;
		bt->Lchild = creatbitree();
		bt->Rchild = creatbitree();
	}
	return bt;
}
void main()
{
	int a = 1;
	bitree bt;
	printf("*************************************************************************\n");
	printf("  请输入先序序列的二叉树(注意：空子树用'.'表示!!!)：>");
	bt = creatbitree();
	while (a != 0)
	{
		printf("  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		printf("  **              1.显示先序遍历结果             **\n");
		printf("  **              2.显示中序遍历结果             **\n");
		printf("  **              3.显示后序遍历结果             **\n");
		printf("  **              0.结 束 操 作                  **\n");
		printf("  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		printf("  请选择相应的操作序号：>");
		scanf("%d", &a);
		switch (a)
		{
		case(1) :
			preorder(bt);
			break;
		case(2) :
			inorder(bt);
			break;
		case(3) :
			postorder(bt);
			break;
		case(0) :
			break;
		}
		printf("\n");
	}
	system("pause");
}