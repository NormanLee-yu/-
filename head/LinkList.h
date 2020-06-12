#pragma once
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
typedef int ElemType_T;
typedef int Status;

typedef struct Node {
	ElemType_T data;
	struct Node *next;
}Node, *LinkList;


//��ʼ��
Status ListInit(LinkList *L) {
	*L = (LinkList)malloc(sizeof(Node));
	if (!(*L))
		return ERROR;
	(*L)->next = NULL;
	return OK;
}


//��
int ListLength(LinkList L) {
	LinkList p = L;
	int len = 0;
	while (p->next) {
		len++;
		p = p->next;
	}
	return len;
}


//��ȡԪ��,��e����
Status GetElem(LinkList L, int i, ElemType_T *e) {
	int j;
	LinkList p;
	p = L->next;
	j = 1;
	while (p->next&&j < i) {
		p = p->next;
		j++;
	}
	if (i == j) {
		*e = p->data;
		return OK;
	}
	else
		return ERROR;
}


//����
Status ListInsert(LinkList*L, int i, ElemType_T e) {
	int j;
	LinkList p, s;
	p = *L;
	j = 1;
	while (p->next&&j < i) {
		p = p->next;
		++j;
	}
	if (j == i) {
		s = (LinkList)malloc(sizeof(Node));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return OK;
	}
}


//ɾ��
Status ListDelete(LinkList*L, int i, ElemType_T *e) {
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next&&j < i) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j>i)
		return ERROR;
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;

}

Status ListDelete_L(LinkList*L, int i) {
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next&&j < i) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j>i)
		return ERROR;
	q = p->next;
	p->next = q->next;
	free(q);
	return OK;
}

//ͷ��
void CreateList_Head(LinkList *L, int n) {
	LinkList p;
	int i;
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	printf("����������:");
	for (i = 0;i < n;i++) {
		p = (LinkList)malloc(sizeof(Node));
		scanf("%d", &(p->data));
		p->next = (*L)->next;
		(*L)->next = p;
	}
}


//β��
void CreateList_Tail(LinkList*L, int n) {
	LinkList p, r;
	int i;
	*L = (LinkList)malloc(sizeof(Node));
	r = *L;
	printf("����������:");
	for (i = 0;i < n;i++) {
		p = (Node*)malloc(sizeof(Node));
		scanf("%d", &(p->data));
		r->next = p;
		r = p;
	}
	r->next = NULL;
}


//��λ�ò��ң����ؽڵ�
Status ListFind(LinkList L, int i) {
	LinkList p = L->next;
	int j = 1;
	while (p&&j < i) {
		p = p->next;
		j++;
	}
	if (p&&j == i)
		return j;
	else
		return ERROR;
}


//��Ԫ��ֵ����
Status ListFind_elem(LinkList L, ElemType_T x) {
	LinkList p = L->next;
	while (p) {
		if (p->data == x)
			return OK;
		else
			p = p->next;
	}
	return ERROR;
}


//����ɾ��
Status ClearList(LinkList *L) {
	LinkList p, q;
	p = (*L)->next;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	return OK;
}

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//˫ָ�붼��ͷ��ʼ
LinkList partation(LinkList low, LinkList high) {
	int key = low->data;
	LinkList p = low;
	LinkList q = low->next;

	while (q != high) {
		if (q->data < key) {
			p = p->next;
			swap(p->data, q->data);
		}
		q = q->next;
	}
	swap(p->data, low->data);
	return p;
}

void Qsort(LinkList low, LinkList high) {
	if (low != high) {
		LinkList pivot = partation(low, high);
		Qsort(low, pivot);
		Qsort(pivot->next, high);
	}
}

void sort(LinkList L) {
	Qsort(L->next, NULL);
}

LinkList remove(LinkList L) {
	//ȥ��
	LinkList p = L->next;
	int count = 1;
	while (p->next) {
		if (p->data == p->next->data) {
			ListDelete_L(&L, count + 1);
		}
		else {
			count++;
			p = p->next;
		}
	}
	return L;
}

//������˫ָ��
LinkList intersection(LinkList L1, LinkList L2) {
	LinkList p = L1->next, head, q, t;
	//ListInit(&head);
	ListInit(&q);
	head = q;
	int i = 1;
	while (p) {
		if (ListFind_elem(L2, p->data)) {
			ListInsert(&q, i, p->data);
			i++;
		}
		p = p->next;
	}
	return head;
}

//�������ϲ�ȥ��
LinkList Union(LinkList L1, LinkList L2) {
	LinkList L, p = L1->next, q = L2->next;
	int count = 1;
	ListInit(&L);
	while (p) {
		ListInsert(&L, count, p->data);
		count++;
		p = p->next;
	}
	while (q) {
		ListInsert(&L, count, q->data);
		count++;
		q = q->next;
	}
	sort(L);
	remove(L);
	return L;

}

void Print(LinkList L) {
	LinkList p = L->next;
	while (p) {
		printf("%-5d", p->data);
		p = p->next;
	}
}

void Menue() {
	//��ʾ�˵�
	printf("���Ա���ϵͳ\n");
	printf("==============================================\n");
	printf("||                 1--����                  ||\n");
	printf("||                 2--����                  ||\n");
	printf("||                 3--ɾ��                  ||\n");
	printf("||                 4--��λ�ò���            ||\n");
	printf("||                 5--��ֵ����              ||\n");
	printf("||                 6--���                ||\n");
	printf("||                 7--�󽻼�                ||\n");
	printf("||                 8--�󲢼�                ||\n");
	printf("||                 0--����                  ||\n");
	printf("==============================================\n");
	printf("������˵���(0-6):");
}

void linklist() {
	LinkList L,L1,L2,p;
	ElemType_T e;
	int length,length2, i,j;
	char c1, c2, a;
	c1 = 'y';
	while (c1 == 'y' || c1 == 'Y') {
		Menue();
		scanf("%c", &c2);
		getchar();
		switch (c2) {
		case '1':
			ListInit(&L);
			printf("������Ҫ�������Ա�ĳ���:");
			scanf("%d", &length);
			CreateList_Tail(&L, length);
			printf("����������Ա�Ϊ:\n");
			Print(L);
			getchar();
			break;
		case '2':
			printf("������Ҫ�����Ԫ��λ��:");
			scanf("%d", &i);
			printf("������Ҫ�����Ԫ��ֵ:");
			scanf("%d", &e);
			ListInsert(&L, i, e);
			printf("����Ԫ��%d������Ա�Ϊ:\n", e);
			Print(L);
			getchar();
			break;
		case '3':
			printf("������Ҫɾ��Ԫ�ص�λ��:");
			scanf("%d", &i);
			ListDelete(&L, i, &e);
			printf("ɾ����%dλ���Ԫ�غ�����Ա�Ϊ:\n", i);
			Print(L);
			getchar();
			break;
		case '4':
			printf("��������ҵ�Ԫ��λ��(���ڵ���1������):");
			scanf("%d", &i);
			if (ListFind(L, i))
				printf("���ҳɹ�");
			else
				printf("����ʧ��");
			getchar();
			break;
		case '5':
			printf("������Ҫ���ҵ�Ԫ��:");
			scanf("%d", &e);
			if (ListFind_elem(L, e))
				printf("���ҳɹ�");
			else
				printf("����ʧ��");
			getchar();
			break;
		case '6':
			printf("���Ա�ĳ���Ϊ:%d\n", ListLength(L));
			break;
		case '7':
			ListInit(&L1);
			printf("������Ҫ�����ڶ������Ա�ĳ���:");
			scanf("%d", &length2);
			CreateList_Tail(&L1, length2);
			printf("������ĵڶ������Ա�Ϊ:\n");
			Print(L1);
			p = intersection(L, L1);
			printf("\n����Ϊ:");
			Print(p);
			getchar();
			break;
		case '8':
			ListInit(&L2);
			printf("������Ҫ�����ڶ������Ա�ĳ���:");
			scanf("%d", &length2);
			CreateList_Tail(&L2, length2);
			printf("������ĵڶ������Ա�Ϊ:\n");
			Print(L2);
			p = Union(L, L2);
			printf("\n����Ϊ:");
			Print(p);
			break;
		case '0':
			c1 = 'n';
			break;
		default:
			printf("�������������0-9����ѡ��\n");
			break;
		}
		if (c2 != '0') {
			printf("\n���س�����������������������˵�\n");
			a = getchar();
			if (a != '\n') {
				getchar();
				c1 = 'n';
			}
		}
	}
}