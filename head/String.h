#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define MAX 200
typedef int Status;

typedef struct String {
	char data[MAX + 1];
	int n;
}String;

//��ʼ�������´�
Status InitString(String *S) {
	int i = 0,n=0;
	while ((S->data[i] = getchar()) != '\n') {
		i++;
		n++;
	}
	S->n = n;
	return OK;
}

//��ӡ
void Print_S(String S) {
	for (int i = 0;i < S.n;i++)
		printf("%c",S.data[i]);
	printf("\n");
}

//�󴮳�
int GetSlength(String S) {
	return S.n;
}

//���Ӵ�
Status SubStr(String S, String *T,int pos, int len) {
	if (pos<1 || pos>S.n || len<0 || pos + len - 1>S.n)
		return ERROR;
	int i;
	for (i = 0;i <= len;i++) {
		T->data[i] = S.data[i + pos - 1];
	}
	T->n = len;
	return OK;
}

//����
Status StrInsert(String *S1, String S2, int pos) {
	if (pos<1 || pos>S1->n)
		return ERROR;
	int j;
	for (j = S1->n - 1;j >= pos - 1;j--)
		S1->data[j + S2.n] = S1->data[j];
		
	for (j = 0;j < S2.n;j++)
		S1->data[pos + j - 1] = S2.data[j];
	S1->n = S1->n + S2.n;
	return OK;
}

//ɾ���Ӵ�
Status DeleteStr(String *S, int pos, int len) {
	if (pos<1 || pos>S->n || len + pos - 1>S->n)
		return ERROR;
	for (int i = pos + len;i <= S->n;i++)
		S->data[i - len] = S->data[i];
	S->n -= len;
	return OK;
}

//���Ƚ�
int Strcmp(String S1, String S2) {
	int i;
	for (i = 0;i < S1.n&&i < S2.n;i++) {
		if (S1.data[i] > S2.data[i])
			return 1;
		else if (S1.data[i] < S2.data[i])
			return -1;
	}
	if (i < S1.n)
		return 1;
	if (i < S2.n)
		return -1;
	return 0;
}

//������
Status Concat(String *S1, String S2) {
	if (S1->n == MAX || S1->n + S2.n >= MAX)
		return ERROR;
	int i,j,length=S1->n+S2.n;
	for (i = S1->n,j=0;i < length;i++,j++) {
		S1->data[i] = S2.data[j];
	}
	S1->n = length;
	return OK;
}

void getNext(String p, int * next){
	next[0] = -1;
	int i = 0, j = -1;
	while (i < p.n){
		if (j == -1 || p.data[i] == p.data[j]){
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}
//KMP�����Ӵ�
int KMP(String S, String T) {
	int i = 0;
	int j = 0;
	int next[255];
	getNext(T, next);
	while (i < S.n && j < T.n) {
		if (j == -1 || S.data[i] == T.data[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == T.n)
		return i - j;
	else
		return -1;
}

//�Ӵ��滻
Status StrRep(String *S, String T, String R) {
	int pos;
	if ((pos = KMP(*S, T)) == -1 || T.n != R.n) {
		printf("Ҫ���滻�Ĵ�����S��");
		return ERROR;

	}
	int i;
	while (pos != -1) {
		for (i = 0;i < T.n;pos++, i++)
			S->data[pos] = R.data[i];
		pos = KMP(*S, T);
	}
	return OK;
}


void Menue3() {
	printf("����ϵͳ\n");
	printf("==============================================\n");
	printf("||               1--�����´�                ||\n");
	printf("||               2--���Ӵ�                  ||\n");
	printf("||               3--�����Ӵ�                ||\n");
	printf("||               4--ɾ���Ӵ�                ||\n");
	printf("||               5--�����Ӵ�                ||\n");
	printf("||               6--�Ƚ�����                ||\n");
	printf("||               7--��������                ||\n");
	printf("||               8--�Ӵ��滻                ||\n");
	printf("||               9--��ʾ                    ||\n");
	printf("||               10--�󴮳�                 ||\n");
	printf("||               0--����                    ||\n");
	printf("==============================================\n");
	printf("������˵���(0-10):");
}

void string() {
	String S, T, R;
	int i, n;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue3();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("�����봮S������:");
			InitString(&S);
			printf("�½��ɹ�");
			break;
		case '2':
			printf("������S���Ӵ�����ʼλ�ú��Ӵ�����:");
			scanf("%d%d",&i,&n);
			SubStr(S, &T, i, n);
			printf("�Ӵ�Ϊ:");
			Print_S(T);
			getchar();
			break;
		case '3':
			printf("��������뵽��Sλ��:");
			scanf("%d",&i);
			getchar();
			printf("������Ҫ������Ӵ�:");
			InitString(&T);
			StrInsert(&S, T, i);
			printf("�������Ӵ�Ϊ:");
			Print_S(S);
			break;
		case '4':
			printf("������Ҫɾ��S���Ӵ���ʼλ�úͳ���:");
			scanf("%d%d",&i,&n);
			DeleteStr(&S, i-1, n);
			printf("ɾ����Ϊ:");
			Print_S(S);
			getchar();
			break;
		case '5':
			printf("������Ҫ��S�в��ҵ��Ӵ�:");
			InitString(&T);
			i = KMP(S, T);
			if (i == -1)
				printf("���Ӵ����ڴ�S��");
			else
				printf("���Ӵ��ڴ�S�ĵ�%dλ��%dλ",i+1,i+T.n);
			break;
		case '6':
			printf("������Ҫ��S�ȽϵĴ�T:");
			InitString(&T);
			i = Strcmp(S, T);
			if (i == 1)
				printf("S��");
			else if (i == 0)
				printf("�������");
			else
				printf("T��");
			break;
		case '7':
			printf("������Ҫ���ӵ�S�Ĵ�T:");
			InitString(&T);
			Concat(&S, T);
			printf("���Ӻ��SΪ:");
			Print_S(S);
			break;
		case '8':
			printf("������Ҫ��S��Ҫ���滻�Ĳ���:");
			InitString(&T);
			printf("������Ҫ�滻�Ĵ�:");
			InitString(&R);
			if (StrRep(&S, T, R)) {
				printf("�滻��SΪ:");
				Print_S(S);
			}
			break;
		case '9':
			printf("��Ϊ:");
			Print_S(S);
			break;
		case '10':
			printf("����Ϊ:%d", GetSlength(S));
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("�������,������0-10����ѡ��!");
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