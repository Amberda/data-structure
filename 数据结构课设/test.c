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
	bitree stack[Max];  //���ڴ��ջ��Ԫ�ص�һά����
	int top;
}SeqStack;
void InitStack(SeqStack *s) //��ʼ��ջ
{
	s->top = -1;//����һ����ջ
}
int isempty(SeqStack *s)//�п�
{
	if (s->top == -1)
		return true;
	else
		return false;
}
int push(SeqStack *s, bitree x)//��ջ
{//��x����Sջ��ջ��
	if (s->top == Max - 1)//ջ����
		return(false);
	else
	{
		s->top++;
		s->stack[s->top] = x;
		return(true);
	}
}
int pop(SeqStack *s, bitree *x)
{//��Sջ��Ԫ�ص������ŵ�x��ָ�Ĵ洢�ռ��д���
	if (s->top == -1)
		return(false);
	else
	{
		*x = s->stack[s->top];
		s->top--;//�޸�ջ��ָ��
		return(true);
	}
}
int GetTop(SeqStack *s, bitree *x)
{//��ջ��Ԫ�ض������ŵ�x��ָ�Ĵ洢�ռ��У�ջ��ָ�뱣�ֲ���
	if (s->top == -1)
		return true;
	else
	{
		*x = s->stack[s->top];
		return false;
	}
}
void preorder(bitree root)/*�������������*/
{
	SeqStack S; bitree p;
	InitStack(&S);
	p = root;
	printf("  ����������Ϊ��");
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
void inorder(bitree root) /*�������������*/
{
	SeqStack S; bitree p;
	InitStack(&S);
	p = root;
	printf("  ����������Ϊ��");
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
void postorder(bitree root) /*�������������*/
{
	SeqStack S; bitree p, q;
	InitStack(&S);
	p = root;
	q = NULL;
	printf("  ����������Ϊ��");
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
	printf("  �������������еĶ�����(ע�⣺��������'.'��ʾ!!!)��>");
	bt = creatbitree();
	while (a != 0)
	{
		printf("  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		printf("  **              1.��ʾ����������             **\n");
		printf("  **              2.��ʾ����������             **\n");
		printf("  **              3.��ʾ����������             **\n");
		printf("  **              0.�� �� �� ��                  **\n");
		printf("  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		printf("  ��ѡ����Ӧ�Ĳ�����ţ�>");
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