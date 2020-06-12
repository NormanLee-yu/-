//#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR 0
#define OK 1
typedef char ElemType_S;
typedef int Status;

//�������ֲ�ͬ���͵�ջ������׺���ʽת��׺���ʽ����
//�ַ�ջ
typedef struct StackNode {
	ElemType_S data;
	struct StackNode*next;
}StackNode, *LinkStackPtr;

typedef struct LinkStack {
	LinkStackPtr top;
	int count;
}LinkStack;

//����ջ
typedef struct StackNode_num {
	int data;
	struct StackNode_num*next;
}StackNode_num, *LinkStackPtr_num;

typedef struct LinkStack_num {
	LinkStackPtr_num top;
	int count;
}LinkStack_num;


//��ʼ��
Status InitStack(LinkStack *s) {
	s->top = (LinkStackPtr)malloc(sizeof(StackNode));
	s->top = NULL;
	s->count = 0;
	return OK;
}
Status InitStack_num(LinkStack_num *s) {//����ջ
	s->top = (LinkStackPtr_num)malloc(sizeof(StackNode_num));
	s->top = NULL;
	s->count = 0;
	return OK;
}

//��ջ
Status Push(LinkStack*S, ElemType_S e) {
	LinkStackPtr p = (LinkStackPtr)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S->top;
	S->top = p;
	S->count++;
	return OK;
}
Status Push_num(LinkStack_num*S, int e) {
	LinkStackPtr_num p = (LinkStackPtr_num)malloc(sizeof(StackNode_num));
	p->data = e;
	p->next = S->top;
	S->top = p;
	S->count++;
	return OK;
}

//��ջ
Status Pop(LinkStack*S, ElemType_S*e) {
	LinkStackPtr p;
	if (!S->top)
		return ERROR;
	*e = S->top->data;
	p = S->top;
	S->top = S->top->next;
	S->count--;
	free(p);
	return OK;
}
Status Pop_num(LinkStack_num*S, int*e) {
	LinkStackPtr_num p;
	if (!S->top)
		return ERROR;
	*e = S->top->data;
	p = S->top;
	S->top = S->top->next;
	S->count--;
	free(p);
	return OK;
}

//����ת��
LinkStack_num BinaryConversion(int num) {
	LinkStack_num S;
	InitStack_num(&S);
	while (num) {
		Push_num(&S, num % 2);
		num /= 2;
	}
	return S;
}

Status EmptyStack(LinkStack_num *S) {
	if (S->top == NULL) {
		return ERROR;
	}
	return OK;
}

Status GetTop(LinkStack_num *S) {
	if (EmptyStack(S) == 0)
		return ERROR;

	return S->top->data;
}

//��ӡ
void PrintStack(LinkStack*S) {
	LinkStackPtr p = S->top;
	if (!p)
		return;
	while (p) {
		printf("%-c", p->data);
		p = p->next;
	}
	printf("\n");
}

void PrintStack_num(LinkStack_num*S) {
	LinkStackPtr_num p = S->top;
	if (!p)
		return;
	while (p) {
		printf("%-5d", p->data);
		p = p->next;
	}
	printf("\n");
}


//�ж����ȼ�,���ڱ��ʽ���㹦��
int level(char a) {
	if (a == '+' || a == '-')
		return 1;
	else if (a == '*' || a == '/')
		return 2;
	else if (a == '(')
		return 1;
	else if (a == ')')
		return -1;
}


/*
��׺���ʽת��׺���ʽ
9 +��3 - 1��* 3 + 10 / 2    ---->   9 3 1 - 3 *+ 10 2 /+
*/
int Mid_to_Rear(ElemType_S *data, LinkStack *S) {
	int len = strlen(data);
	int i, k = 0, flag = 1;
	ElemType_S e;
	for (i = 0;i < len;i++) {
		if (data[i] <= '9'&&data[i] >= '0') {
			data[k] = data[i];
			k++;
			/*if (data[i + 1] <= '9'&&data[i] >= '0'&&data[i])
			continue;
			else {
			data[]
			}*/
		}
		else if (flag) {
			//��һ���������ַ���ջ
			Push(S, data[i]);
			flag = 0;
		}
		else if (data[i] == ' ') {
			data[k] = data[i];
			k++;
		}
		else if (level(data[i]) >= level(S->top->data)) {
			//���ȼ���ջ��Ԫ�ص����ȼ��Ƚϣ�������ȼ����ڻ��ߵ�������ջ
			Push(S, data[i]);
		}
		else if (level(data[i]) < level(S->top->data)) {
			//�������ջ��һֱ����û�б�������ȼ���С
			if (level(data[i]) == -1) {
				//������')'ʱ��һֱ��ջ��'('��
				//printf("ƥ�䵽������\n");
				while (S->top->data != '('&&S->top) {
					Pop(S, &e);
					data[k] = e;
					k++;
				}
				Pop(S, &e);
			}
			else {
				while ((level(data[i]) <= level(S->top->data)) && S->top) {
					Pop(S, &e);
					data[k] = e;
					k++;
					if (!S->top)
						break;
				}
				Push(S, data[i]);
			}
		}
	}
	while (S->top) {//��ջ��ʣ�µķ����Ƴ�
		Pop(S, &e);
		data[k] = e;
		k++;
	}
	return k;
}


//��׺���ʽ����
Status Cal(LinkStack_num *S, ElemType_S *data, int k) {//SΪ����ջ��data����Ϊ��׺���ʽ��kΪdata�����λ��
	int result = 0, i, j = -1, x = 0, num1, num2;//9   3  1 -  3 *+ 10  2/+
	for (i = 0;i < k;i++) {
		j = -1;
		if (data[i] == ' ') {
			continue;
		}
		else if (data[i] >= '0'&&data[i] <= '9') {
			if (data[i + 1] >= '0'&&data[i + 1] <= '9') {
				j = i + 1;
				x = x * 10 + data[i] - '0';
				while (data[j] >= '0'&&data[j] <= '9'&&j<k) {
					x = x * 10 + data[j] - '0';
					j++;
					i++;
				}
				i++;
			}
			if (j == -1)
				x = x * 10 + data[i] - '0';
			Push_num(S, x);
			x = 0;

		}
		else {
			Pop_num(S, &num2);
			Pop_num(S, &num1);
			switch (data[i]) {
			case '+':
				result = num1 + num2;
				break;
			case '-':
				result = num1 - num2;
				break;
			case '*':
				result = num1 * num2;
				break;
			case '/':
				result = num1 / num2;
				break;
			}
			Push_num(S, result);
		}
	}
	return result;
}

void han(int n, char a, char b, char c) {
	if (n == 1)
		printf("�� %c �� %c\n", a, c);
	else {
		han(n - 1, a, c, b);
		printf("�� %c �� %c\n", a, c);
		han(n - 1, b, a, c);
	}
}

void Menue1() {
	//�˵�
	printf("ջ��ϵͳ\n");
	printf("==============================================\n");
	printf("||               1--��ʼ��ջ                ||\n");
	printf("||               2--��ջ                    ||\n");
	printf("||               3--��ջ                    ||\n");
	printf("||               4--��ջ��Ԫ��              ||\n");
	printf("||               5--��ʾջ��Ԫ��            ||\n");
	printf("||               6--ʮ��������ת��          ||\n");
	printf("||               7--���ʽת������ֵ        ||\n");
	printf("||               8--��ŵ���ƶ�����          ||\n");
	printf("||               0--����                    ||\n");
	printf("==============================================\n");
	printf("������˵���(0-6):");
}

void linkstack() {
	int i, e, n, result;
	LinkStack_num S;
	char ch1, ch2, data[200], a;
	ch1 = 'y';
	LinkStack N;
	InitStack(&N);

	while (ch1 == 'y' || ch1 == 'Y') {
		Menue1();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			InitStack_num(&S);
			printf("��ʼ�����");
			break;
		case '2':
			printf("������Ҫ��ջ��Ԫ�ظ���:");
			scanf("%d", &n);
			printf("��������ջԪ��:");
			for (i = 0;i < n;i++) {
				scanf("%d", &e);
				Push_num(&S, e);
			}
			printf("��ջ��Ϊ:");
			PrintStack_num(&S);
			getchar();
			break;
		case '3':
			printf("������Ҫ��ջ��Ԫ�ظ���:");
			scanf("%d", &n);
			printf("��ջԪ��Ϊ:");
			for (i = 0;i < n;i++) {
				Pop_num(&S, &e);
				printf("%-5d", e);
			}
			getchar();
			break;
		case '4':
			e = GetTop(&S);
			printf("ջ��Ԫ��Ϊ:%d", e);
			break;
		case '5':
			printf("ջ��Ԫ��Ϊ:");
			PrintStack_num(&S);
			break;
		case '6':
			printf("������ʮ����������:");
			scanf("%d", &e);
			printf("ת���ɶ�����Ϊ:");
			PrintStack_num(&(BinaryConversion(e)));
			getchar();
			break;
		case '7':
			printf("������һ���������ʽ(ֻ��+��-��*��/��������,ÿ��Ԫ���м��ÿո����):");
			gets_s(data);
			n = Mid_to_Rear(data, &N);
			printf("��׺���ʽת��׺���ʽ��Ϊ:");
			for (i = 0;i < n;i++)
				printf("%c", data[i]);
			result = Cal(&S, data, n);
			printf("\n���ʽ��ֵΪ:%d", result);
			break;
		case '8':
			printf("������A���ж��ٲ�n:");
			scanf("%d",&n);
			printf("����������A��B��C,A��������%d��,��A�ƶ���C����Ҫ����:\n",n);
			han(n, 'A', 'B', 'C');
			getchar();
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("�������,����������ѡ��!");
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
