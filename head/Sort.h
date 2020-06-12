#pragma once
#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAXSIZE 100
typedef int Status;
typedef struct {
	int r[MAXSIZE];
	int length;
}SqList;


void swap(SqList *L, int i, int j) {
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}


//ð������
void BubbleSort(SqList *L) {
	int i, j;
	for (i = 1;i <= L->length;i++) {
		for (j = L->length-1;j >= i;j--) {
			if (L->r[j]>L->r[j + 1])
				swap(L, j, j + 1);
		}
	}
}


//ѡ������
void SelectSort(SqList *L) {
	int i, j, min;
	for (i = 1;i < L->length;i++) {
		min = i;
		for (j = i + 1;j <= L->length;j++) {
			if (L->r[min] > L->r[j]) {
				min = j;
			}
		}
		if (i != min) {
			swap(L, i, min);
		}
	}
}


//��������
void InsertSort(SqList*L) {
	int i, j;
	for (i = 2; i<=L->length; i++) {
		if (L->r[i] < L->r[i - 1]) {
			L->r[0] = L->r[i];
			for (j = i - 1;L->r[j]>L->r[0];j--)
				L->r[j + 1] = L->r[j];
			L->r[j + 1] = L->r[0];
		}
	}
}


//ϣ������
void ShellSort(SqList *L, int n) {
	int i, j, k;
	int gap;	//����
	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = 1; i <= gap; i++) {
			for (j = i + gap; j < n; j += gap) {
				if (L->r[j] < L->r[j - gap]) {
					L->r[0] = L->r[j];	//�ڱ�
					k = j - gap;
					while (k >= 0 && L->r[k]>L->r[0]) {
						L->r[k + gap] = L->r[k];
						k = k - gap;
					}
					L->r[k + gap] = L->r[0];
				}
			}
		}
	}
}


//�鲢����
void Merge(int SR[], int TR[], int i, int m, int n) {
	//�������SR[i-m]��SR[m+1-n]�鲢Ϊ�����TR[i-n]
	//˫ָ�뷨
	int j, k, l;
	for (j = m + 1, k = i;i <= m&&j <= n;k++) {
		if (SR[i] < SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if (i <= m) {
		for (l = 0;l <= m - i;l++)
			TR[k + l] = SR[i + l];//��ʣ���SR[i-m]���Ƶ�TR
	}
	if (j <= n) {
		for (l = 0;l <= n - j;l++)
			TR[k + l] = SR[j + l];
	}
}

void MSort(int SR[], int TR1[], int s, int t) {
	int m;
	int TR2[MAXSIZE + 1];
	if (s == t)
		TR1[s] = SR[s];
	else {
		m = (s + t) / 2;//��SR[s-t]ƽ�ֳ�SR[s-m]��SR[m+1-t]
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m + 1, t);
		Merge(TR2, TR1, s, m, t);
	}
}

void MergeSort(SqList*L) {
	MSort(L->r, L->r, 1, L->length);
}


//��������
int Partition(SqList*L, int low, int high) {
	int pivotkey;
	pivotkey = L->r[low];
	while (low < high) {
		while (low < high&&L->r[high] >= pivotkey) {
			high--;
		}
		swap(L, low, high);
		while (low < high&&L->r[low] <= pivotkey)
			low++;
		swap(L, low, high);
	}
	return low;
}

void QSort(SqList*L, int low, int high) {
	int pivot;
	if (low < high) {
		pivot = Partition(L, low, high);
		QSort(L, low, pivot - 1);//�Ե��ӱ�ݹ�����
		QSort(L, pivot + 1, high);//�Ը��ӱ�ݹ�����
	}
}

void QuickSort(SqList*L) {
	QSort(L, 1, L->length);
}


//������
void HeapAdjust(SqList *L, int s, int m) {
	int temp, j;
	temp = L->r[s];
	for (j = 2 * s;j <= m;j *= 2) {
		if (j < m&&L->r[j] < L->r[j + 1])
			++j;	
		if (temp >= L->r[j])
			break;
		L->r[s] = L->r[j];
		s = j;
	}
	L->r[s] = temp;
}

void HeapSort(SqList *L) {
	int i;
	for (i = L->length / 2;i > 0;i--) 
		HeapAdjust(L, i, L->length);
	
	for (i = L->length;i > 1;i--) {
		swap(L, 1, i);
		HeapAdjust(L, 1, i - 1);
	}
}

void PrintS(SqList L) {
	for (int i = 1;i <= L.length;i++)
		printf("%-5d", L.r[i]);
	printf("\n");
}

void Menue7(){ 
	printf("������ϵͳ\n");
	printf("==============================================\n");
	printf("||                 1--������������          ||\n");
	printf("||                 2--ֱ�Ӳ�������          ||\n");
	printf("||                 3--ϣ������              ||\n");
	printf("||                 4--ð������              ||\n");
	printf("||                 5--��������              ||\n");
	printf("||                 6--ֱ��ѡ������          ||\n");
	printf("||                 7--������                ||\n");
	printf("||                 8--�鲢����              ||\n");
	printf("||                 0--����                  ||\n");
	printf("==============================================\n");
	printf("������˵���(0-8):");
}

void sort() {
	SqList L;
	int i, n;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue7();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("������������ĳ���:");
			scanf("%d",&n);
			printf("������%d������:",n);
			for (i = 1;i <= n;i++)
				scanf("%d",&L.r[i]);
			L.length = n;
			printf("�������");
			getchar();
			break;
		case '2':
			L.r[0] = 0;
			InsertSort(&L);
			printf("ֱ�Ӳ��������Ϊ:");
			PrintS(L);
			break;
		case '3':
			ShellSort(&L, L.length + 1);
			printf("ϣ�������Ϊ:");
			PrintS(L);
			break;
		case '4':
			BubbleSort(&L);
			printf("ð�������Ϊ:");
			PrintS(L);
			break;
		case '5':
			QuickSort(&L);
			printf("���������Ϊ:");
			PrintS(L);
			break;
		case '6':
			SelectSort(&L);
			printf("ֱ��ѡ�������Ϊ:");
			PrintS(L);
			break;
		case '7':
			HeapSort(&L);
			printf("�������Ϊ:");
			PrintS(L);
			break;
		case '8':
			MergeSort(&L);
			printf("�鲢�����Ϊ:");
			PrintS(L);
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("�������,������0-8����ѡ��!");
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