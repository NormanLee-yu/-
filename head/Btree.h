#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef char TElemType;
//�������Ķ���������ṹ
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//���ö�������ɲ������
typedef char QType;
typedef int Status;
typedef struct QN {
	BiTree data;//����Ԫ��Ϊ�����
	struct QN *next;
}QN, *QPtr;

typedef struct {
	QPtr front, rear;
}LinkQueue_T;

//��ʼ��һ������
Status InitLinkQuue_T(LinkQueue_T*Q) {
	Q->front = Q->rear = (QPtr)malloc(sizeof(QN));
	if (!Q->front)
		return ERROR;
	Q->front->next = NULL;
	return OK;
}

//���
Status EnQueue_T(LinkQueue_T*Q, BiTree e) {
	QPtr s = (QPtr)malloc(sizeof(QN));
	if (!s)
		return ERROR;
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;
	Q->rear = s;
	return OK;
}

//����
Status DeQueue_T(LinkQueue_T*Q, BiTree*e) {
	QPtr p;
	if (Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)//�����ͷ�Ƕ�β
		Q->rear = Q->front;
	free(p);
	return OK;
}


void CreateTree(BiTree *T) {
	/*
		A
	B		C
	�����˶���������AB##C##
	*/
	TElemType c;
	scanf("%c",&c);
	if (c == '#')//���������ʶ��
		*T = NULL;
	else {
		(*T) = (BiTree)malloc(sizeof(BiTNode));
		if (!*T)
			exit(0);
		(*T)->data = c;
		CreateTree(&(*T)->lchild);//����������
		CreateTree(&(*T)->rchild);//����������
	}
}

void PreOrderTraverse(BiTree T) {
	//ǰ�����
	if (!T)
		return;
	printf("%c",T->data);
	PreOrderTraverse(T->lchild);//����������
	PreOrderTraverse(T->rchild);//����������
}

void InOrderTraverse(BiTree T) {
	//�������
	if (!T)
		return;
	InOrderTraverse(T->lchild);
	printf("%c",T->data);
	InOrderTraverse(T->rchild);
}

void PostOrderTraverse(BiTree T) {
	//�������
	if (!T)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c",T->data);
}

void LevelTraverse(BiTree T) {
	BiTree X = T;
	LinkQueue_T Q;
	InitLinkQuue_T(&Q);
	EnQueue_T(&Q, X);//���
	while (Q.front!=Q.rear) {
		DeQueue_T(&Q, &X);
		printf("%c",X->data);
		if (X->lchild)
			EnQueue_T(&Q, X->lchild);
		if (X->rchild)
			EnQueue_T(&Q, X->rchild);
	} 
}

//�����Ľڵ���
int TreeNodeNum(BiTree T) {
	if (!T)
		return 0;
	return 1 + TreeNodeNum(T->lchild) + TreeNodeNum(T->rchild);
}

//������Ҷ�ӽ��
int TreeLeafNum(BiTree T) {
	if (!T)
		return 0;
	if (T->lchild == NULL&&T->rchild == NULL)
		return 1;
	return TreeLeafNum(T->lchild) + TreeLeafNum(T->rchild);
}

//���������
int TreeDepth(BiTree T) {
	if (!T)
		return 0;
	return TreeDepth(T->lchild) > TreeDepth(T->rchild) ? TreeDepth(T->lchild) + 1 : TreeDepth(T->rchild) + 1;
}

//�ù�����ʾ������
void Print_Tree(BiTree T) {
	printf("%c",T->data);
	if (T->lchild != NULL) {
		printf("(");
		Print_Tree(T->lchild);
		if (T->rchild == NULL)
			printf(",)");
	}
	if (T->rchild != NULL) {
		if (T->lchild == NULL) 
			printf("(");
		printf(",");
		Print_Tree(T->rchild);
		printf(")");
	}
}

void Menue4() {
	printf("��������ϵͳ\n");
	printf("==============================================\n");
	printf("||             1--�����¶�����              ||\n");
	printf("||             2--������ʾ����ʾ          ||\n");
	printf("||             3--�������                  ||\n");
	printf("||             4--�������                  ||\n");
	printf("||             5--�������                  ||\n");
	printf("||             6--��α���                  ||\n");
	printf("||             7--��Ҷ�ӽ����              ||\n");
	printf("||             8--��������ܽ����          ||\n");
	printf("||             9--������������            ||\n");
	printf("||             0--����                      ||\n");
	printf("==============================================\n");
	printf("������˵���(0-9):");
}

void btree() {
	BiTree T;
	int i, n;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue4();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("��������������('#'��ʾ�ý��Ϊ��):");
			CreateTree(&T);
			printf("�����������ɹ�");
			getchar();
			break;
		case '2':
			printf("�������Ĺ�����ʾ��Ϊ:(");
			Print_Tree(T);
			printf(")");
			break;
		case '3':
			printf("�������������������Ϊ:");
			PreOrderTraverse(T);
			break;
		case '4':
			printf("�������������������Ϊ:");
			InOrderTraverse(T);
			break;
		case '5':
			printf("�������ĺ����������Ϊ:");
			PostOrderTraverse(T);
			break;
		case '6':
			printf("�������Ĳ�α�������Ϊ:");
			LevelTraverse(T);
			break;
		case '7':
			printf("�ö�������%d��Ҷ��",TreeLeafNum(T));
			break;
		case '8':
			printf("�ö�������%d�����",TreeNodeNum(T));
			break;
		case '9':
			printf("�ö����������Ϊ:%d",TreeDepth(T));
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("�������,������0-9����ѡ��!");
			break;

		}
		if (ch2 != '0') {
			printf("\n���س�����������������������˵�!\n");
			a = getchar();
			if (a != '\n') {
				getchar();
				ch1 = 'n';
			}
		}
	}
}