#pragma once
/*
���������ͣ��������ϵͳ
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#define ERROR 0
#define OK 1
typedef int Status;
typedef struct {//��
	int start;//����ʱ��
	int end;//�뿪ʱ��
	int cost;//�̳����ѽ��
	char id[10];//���ƺ�
}CarOwner;

typedef struct TCNode {//ͣ������λ
	CarOwner data;//����
	struct TCNode *next;
}TCNode, *TCLinkList;

Status ParkingLot_Init(TCLinkList *L) {
	*L = (TCLinkList)malloc(sizeof(TCNode));
	if (!(*L))
		return ERROR;
	(*L)->next = NULL;
	return OK;
}


int ParkingLot_Num(TCLinkList L) {//ͣ�������ó�λ(0-100)
	TCLinkList p = L;
	int len = 0;
	while (p->next) {
		len++;
		p = p->next;
	}
	return len;
}


Status ParkingLot_Insert(TCLinkList *L, CarOwner e) {
	TCLinkList p, s;
	p = *L;
	while (p->next) 
		p = p->next;
	
	s = (TCLinkList)malloc(sizeof(TCNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}


Status ParkingLot_Delete(TCLinkList*L, char i[]) {//ͨ�����ƺ���ɾ��
	int j = 0;
	TCLinkList p, q;
	p = *L;
	while (p) {
		if (strcmp(i, p->next->data.id) == 0) {
			break;
		}
		p = p->next;
		j++;
	}
	if (j > ParkingLot_Num(*L)) 
		return ERROR;

	q = p->next;
	p->next = q->next;
	free(q);
	return OK;
}


//����
Status Enter(TCLinkList *L, CarOwner h) {
	int num = ParkingLot_Num(*L);
	if (num >= 100) {
		printf("��λ����!");
		return ERROR;
	}
	ParkingLot_Insert(L, h);
	printf("���ѽ���ͣ����");
	return OK;
}


void Update(CarOwner *h) {//���������ģ�����Ѻ�ͣ��ʱ��
	//�漰ͣ�����ü������������
	h->cost = rand() % 2000 + 1;
	h->end = rand() % 11 + 1;
}


//�뿪
void Leave(TCLinkList *L, CarOwner h) {
	if (h.cost >= 200)
		printf("�̳����ѳ���200RMB��ͣ���Ѽ��룬����֧��%dRMB\n", (h.end - h.start)*3);
	else
		printf("����֧��ͣ����%dRMB\n", (h.end - h.start) * 6);
	ParkingLot_Delete(L, h.id);
	printf("���ƺ�:%s�ĳ���,",h.id);
	printf("�����뿪ͣ����");
}

void TCLPrint(TCLinkList L) {
	TCLinkList p;
	p = L->next;
	while (p) {
		printf("%s\n",p->data.id);
		p = p->next;
	}
}

void Menue8() {
	printf("ͣ����������ϵͳ\n");
	printf("==============================================\n");
	printf("||           1--����ͣ����                  ||\n");
	printf("||           2--���³���������Ϣ���뿪ͣ����||\n");
	printf("||           3--��ʾͣ��������              ||\n");
	printf("||           4--��ȡͣ������������          ||\n");
	printf("||           0--����                        ||\n");
	printf("==============================================\n");
	printf("������˵���(0-3):");
}

void parkinglot() {
	TCLinkList L;
	ParkingLot_Init(&L);
	CarOwner h;
	int i, n;
	char ch1, ch2, a,s[10];
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue8();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("���������ĳ��ƺ�:");
			scanf("%s", &h.id);
			Enter(&L, h);
			h.start = 0;
			getchar();
			break;
		case '2':
			printf("���������ĳ��ƺ�:");
			scanf("%s",&s);
			strcpy(h.id, s);
			Update(&h);
			Leave(&L,h);
			getchar();
			break;
		case '3':
			printf("ͣ����������:\n");
			TCLPrint(L);
			break;
		case '4':
			printf("��ǰͣ������%d������",ParkingLot_Num(L));
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("�������,������0-3����ѡ��!");
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