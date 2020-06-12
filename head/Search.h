#pragma once
#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAXSIZE 100
typedef int Status;
typedef struct {
	int key;
}SearchL;

//˳�����
int Search(SearchL *a, int n, int key) {
	int i;
	a[0].key = key;
	i = n;
	while (a[i].key != key)
		i--;
	return i;
}

//���ֲ���
int Binary_Search(SearchL *a, int n, int key) {
	//�ǵݹ�
	int high, low,mid;
	low = 0;
	high = n;
	while (low <= high) {
		mid = (low + high) / 2;
		if (key < a[mid].key)
			high = mid - 1;
		else if (key>a[mid].key)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

typedef int KeyType;
typedef struct {
	KeyType key;
	int low;
	int high;
}IdxType;

int blocksearch(int key, SearchL a[], IdxType index_key[],int m,int n) {
	int i = 0, j = 1;
	int k = m / n;
	while (i < k) {
		index_key[i].low = j;
		index_key[i].high = j + n - 1;
		index_key[i].key = a[j + n - 1].key;
		j += n;
		i++;
	}
	if (m%n != 0) {
		index_key[i].low = j;
		index_key[i].high = m - 1;
		index_key[i].key = a[m - 1].key;
		i++;
	}
	k = i;

	for (i = 0;i<k && key>index_key[i].key;i++);
	if (i >= k) return 0;
	j = index_key[i].low;
	for (;j < index_key[i].high&&key != a[j].key;j++);
	if (j > index_key[i].high) return 0;
	return j;
}

typedef struct BiTNode_S {
	int data;
	struct BiTNode_S*lchild, *rchild;
}BiTNode_S, *BiTree_S;

/*
ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
������ҳɹ�����ָ��Pָ�������Ԫ�ؽڵ㣬������TRUE
����ָ��pָ�����·���Ϸ��ʵ����һ���ڵ㲢����FALSE
*/
Status SearchBST(BiTree_S T, int key, BiTree_S f, BiTree_S *p) {
	if (!T) {
		*p = f;
		return FALSE;
	}
	else if (key == T->data) {
		*p = T;
		return TRUE;
	}
	else if (key < T->data)
		return SearchBST(T->lchild, key, T, p);
	else
		return SearchBST(T->rchild, key, T, p);
}

//����
Status InsertBST(BiTree_S*T, int key) {
	BiTree_S p, s;
	if (!SearchBST(*T, key, NULL, &p)) {
		s = (BiTree_S)malloc(sizeof(BiTNode_S));//���Ҳ��ɹ������
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			*T = s;//����sΪ�µĸ��ڵ�
		else if (key < p->data)
			p->lchild = s;
		else
			p->rchild = s;
		return TRUE;
	}
	else
		return FALSE;
}

//����
void BuildBST(BiTree_S *T, int *data,int n) {
	int i;
	for (i = 1;i <= n;i++)
		InsertBST(T, data[i]);
}

//ɾ��
Status Delete(BiTree_S *p) {
	BiTree_S q, s;
	if ((*p)->rchild == NULL) {	//����������ֻ��Ҫ�ؽ�����������
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else if ((*p)->lchild == NULL) {//����������ֻ��Ҫ�ؽ�����������
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else {//�������������յ����
		  /*
		  ������
		  ȡ�������е���СԪ�����   ����   ȡ�������е����Ԫ�����
		  */
		  //�˴�ѡȡ�����������Ԫ�����
		q = *p;
		s = (*p)->lchild;
		while (s->rchild) {//ת��Ȼ�����ҵ���ͷ
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data;//sָ��ɾ�ڵ��ֱ��ǰ��
		if (q != *p)
			q->rchild = s->lchild;//�ؽ�q��������
		else//������ͬʱ�����������������ͬʱ��������Ҫ������
			q->lchild = s->lchild;
		free(s);
	}
	return TRUE;
}

Status DeleteBST(BiTree_S *T, int key) {
	if (!*T)
		return FALSE;
	else {
		if (key == (*T)->data)
			return Delete(T);
		else if (key < (*T)->data)
			return DeleteBST(&(*T)->lchild, key);
		else
			return DeleteBST(&(*T)->rchild, key);
	}
}

//�ù�����ʾ������
void Print_BTree(BiTree_S T) {
	printf("%d", T->data);
	if (T->lchild != NULL) {
		printf("(");
		Print_BTree(T->lchild);
		if (T->rchild == NULL)
			printf(",)");
	}
	if (T->rchild != NULL) {
		if (T->lchild == NULL)
			printf("(");
		printf(",");
		Print_BTree(T->rchild);
		printf(")");
	}
}

void MenueBTree() {
	printf("����������\n");
	printf("==============================================\n");
	printf("||             1--��������������            ||\n");
	printf("||             2--����һ��Ԫ��              ||\n");
	printf("||             3--ɾ��һ��Ԫ��              ||\n");
	printf("||             4--����һ��Ԫ��              ||\n");
	printf("||             5--������ʾ����ʾ          ||\n");
	printf("||             0--����                      ||\n");
	printf("==============================================\n");
	printf("���������(0-4)ѡ��Ҫ���еĲ���:");
}

void BTfunction() {
	KeyType s[MAXSIZE];
	BiTree_S T = NULL;
	BiTree_S p;
	int i, n, x;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		MenueBTree();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("������Ҫ���ɶ����������Ĺؼ��ֵĸ���:");
			scanf("%d",&n);
			printf("����������������ĸ����ؼ���:");
			for (i = 1;i <= n;i++) {
				scanf("%d",&s[i]);
			}
			BuildBST(&T, s, n);
			printf("���������������ɹ�,������ʾ��Ϊ:(");
			Print_BTree(T);
			printf(")");
			getchar();
			break;
		case '2':
			printf("������Ҫ�����Ԫ��ֵ:");
			scanf("%d",&x);
			InsertBST(&T, x);
			printf("�����Ķ���������Ϊ:");
			Print_BTree(T);
			getchar();
			break;
		case '3':
			printf("������Ҫɾ����Ԫ��:");
			scanf("%d",&x);
			DeleteBST(&T, x);
			printf("ɾ����Ķ���������Ϊ:");
			Print_BTree(T);
			getchar();
			break;
		case '4':
			printf("������Ҫ���ҵ�Ԫ��ֵ:");
			scanf("%d",&x);
			if(SearchBST(T, x, NULL, &p))
				printf("�ڶ����������д���Ԫ��%d",x);
			else
				printf("�ڶ����������в�����Ԫ��%d", x);
			getchar();
			break;
		case '5':
			printf("����������Ϊ:(");
			Print_BTree(T);
			printf(")");
			break;
		case '0':
			return;
			break;
		default:
			printf("�������,������0-5����ѡ��!");
			break;
		}
		if (ch2 != '0') {
			printf("\n���س�������������������ز�����ϵͳ!\n");
			a = getchar();
			if (a != '\n') {
				getchar();
				ch1 = 'n';
			}
		}
	}
}

void Menue6() {
	printf("������ϵͳ\n");
	printf("==============================================\n");
	printf("||                 1--˳�����              ||\n");
	printf("||                 2--�۰����              ||\n");
	printf("||                 3--�ֿ����              ||\n");
	printf("||                 4--��������������        ||\n");
	printf("||                 0--����                  ||\n");
	printf("==============================================\n");
	printf("������˵���(0-4):");
}

void search() {
	SearchL L[MAXSIZE];
	IdxType idx[MAXSIZE];
	int i, n,x,index,m;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue6();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("������Ԫ�ظ���(0-%d):",MAXSIZE-1);
			scanf("%d",&n);
			printf("������%d�����еĹؼ���(����):",n);
			for (i = 1;i <= n;i++)
				scanf("%d",&L[i].key);
			printf("������Ҫ���ҵĹؼ���:");
			scanf("%d",&x);
			if ((index = Search(L, n, x)) != 0)
				printf("��Ԫ���ڱ��е�λ��Ϊ:%d", index);
			else
				printf("��Ԫ�ز��ڱ���");
			getchar();
			break;
		case '2':
			printf("��������Ԫ�ظ���(0-%d):", MAXSIZE - 1);
			scanf("%d", &n);
			printf("�밴�մ�С�����˳������%d���ؼ���(Ϊ����):", n);
			for (i = 1;i <= n;i++)
				scanf("%d", &L[i].key);
			printf("������Ҫ���ҵĹؼ���:");
			scanf("%d", &x);
			if((index=Binary_Search(L,n,x))!=0)
				printf("��Ԫ���ڱ��е�λ��Ϊ:%d", index);
			else
				printf("��Ԫ�ز��ڱ���");
			getchar();
			break;
		case '3':
			printf("��������Ԫ�ظ���(0-%d):", MAXSIZE - 1);
			scanf("%d", &m);
			printf("��������еĹؼ���(Ϊ����)��Ҫ��������򣬿������:\n");
			for (i = 1;i <= m;i++)
				scanf("%d", &L[i].key);
			printf("������������ÿ��Ĵ�С:");
			scanf("%d", &n);
			printf("������Ҫ���ҵĹؼ���:");
			scanf("%d", &x);
			if((index=blocksearch(x, L, idx, m, n))!=0)
				printf("��Ԫ���ڱ��е�λ��Ϊ:%d", index);
			else
				printf("��Ԫ�ز��ڱ���");
			getchar();
			break;
		case '4':
			BTfunction();
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("�������,������0-4����ѡ��!");
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