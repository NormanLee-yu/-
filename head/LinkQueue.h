#pragma once
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
typedef int QElemType;
typedef int Status;
typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct {
	QueuePtr front, rear;
}LinkQueue;

Status InitLinkQuue(LinkQueue*Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		return ERROR;
	Q->front->next = NULL;
	return OK;
}

//���
Status EnQueue(LinkQueue*Q, QElemType e) {
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
	if (!s)
		return ERROR;
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;
	Q->rear = s;
	return OK;
}

//����
Status DeQueue(LinkQueue*Q, QElemType*e) {
	QueuePtr p;
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
//�ж϶ӿ�
Status EmptyQueue(LinkQueue *Q) {
	if (Q->front == Q->rear)//��
		return OK;
	return ERROR;
}

//ȡͷ
Status GetQueue(LinkQueue*Q, QElemType*e) {
	if (EmptyQueue(Q))
		return ERROR;
	*e = Q->front->next->data;
}


//��ʾ
void Print_Q(LinkQueue*Q) {
	QNode *p=Q->front->next;
	while (p) {
		printf("%-5d",p->data);
		p = p->next;
	}
	printf("\n");
}

void Menue2() {
	//�˵�
	printf("������ϵͳ\n");
	printf("==============================================\n");
	printf("||               1--��ʼ������              ||\n");
	printf("||               2--���                    ||\n");
	printf("||               3--����                    ||\n");
	printf("||               4--���ͷԪ��              ||\n");
	printf("||               5--��ʾ����Ԫ��            ||\n");
	printf("||               0--����                    ||\n");
	printf("==============================================\n");
	printf("������˵���(0-5):");
}

void linkqueue() {
	int i, n;
	QElemType x;
	LinkQueue Q;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue2();
		scanf("%c",&ch2);
		getchar();
		switch (ch2) {
		case '1':
			InitLinkQuue(&Q);
			printf("��ʼ���������");
			break;
		case '2':
			printf("������Ҫ��ӵ�Ԫ�ظ���:");
			scanf("%d",&n);
			printf("������%d��Ԫ��:",n);
			for (i = 0;i < n;i++) {
				scanf("%d",&x);
				EnQueue(&Q, x);
			}
			printf("��Ӻ����Ϊ:");
			Print_Q(&Q);
			getchar();
			break;
		case '3':
			printf("������Ҫ���ӵ�Ԫ�ظ���:");
			scanf("%d",&n);
			printf("���ӵ�Ԫ��˳������Ϊ:");
			for (i = 0;i < n;i++) {
				DeQueue(&Q, &x);
				printf("%-5d",x);
			}
			getchar();
			break;
		case '4':
			GetQueue(&Q, &x);
			printf("��ǰ��ͷԪ��Ϊ:%d",x);
			break;
		case '5':
			printf("��ǰ����Ԫ��Ϊ:");
			Print_Q(&Q);
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("�������,������0-5����ѡ��!");
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