#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 100
typedef char VertexType;
typedef int EdgeType;
bool visited[MAXVEX];

typedef struct EdgeNode {//�߱�
	int adjvex;//�ڽӵ��򣬴���õ��Ӧ���±�
	struct EdgeNode *next;//����ָ����һ���ڽӵ�
}EdgeNode;

typedef struct VertexNode {//�����
	VertexType data;//������
	EdgeNode*firstedge;//�߱�ͷָ��
}VertexNode, AdjList[MAXVEX];

typedef struct {
	AdjList adjList;
	int numVertexes, numEdges;//ͼ�еĶ������ͱ���
}GraphAdjList;

//���ö������BFS
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int ElemTypeG;
typedef int Status;
typedef struct {
	ElemTypeG data[MAXSIZE];
	int front;
	int rear;
}SqQueue;

//��ʼ��
Status InitQueue_G(SqQueue *Q) {
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//���--β��
Status EnQueue_G(SqQueue *Q, ElemTypeG e) {
	if ((Q->rear + 1) % MAXSIZE == Q->front)//������Ҫ��һ����ȱ��
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;//rearָ�������һ��λ�ã������������ת����ͷ
}

//����--ͷ��
Status DeQueue_G(SqQueue*Q, ElemTypeG*e) {
	if (Q->front == Q->rear)//�ӿ�
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

void CreatALGraph(GraphAdjList *G, int n) {
	if (n == 1)
		printf("=========������һ������ͼ=========\n");
	else
		printf("=========������һ������ͼ=========\n");
	int i, j, k;
	EdgeNode *e;
	printf("���붥�����ͱ���:");
	scanf("%d%d", &G->numVertexes, &G->numEdges);
	for (i = 0;i < G->numVertexes;i++) {
		//���������
		printf("�����%d����:", i);
		scanf("\n%c", &(G->adjList[i].data));
		G->adjList[i].firstedge = NULL;//�Ƚ��߱���Ϊ�ձ�
	}

	for (k = 0;k < G->numEdges;k++) {
		//�����߱�
		printf("�����%d����(Vi,Vj)�ϵĶ������:", k);
		scanf("\n%d,%d", &i, &j);
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex = j;//�ڽ����Ϊj
		e->next = G->adjList[i].firstedge;//����ͷ�巨����
		G->adjList[i].firstedge = e;

		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}
void DFS(GraphAdjList GL, int i) {
	EdgeNode *p;
	visited[i] = true;
	printf("%c ", GL.adjList[i].data);
	p = GL.adjList[i].firstedge;
	while (p) {
		if (!visited[p->adjvex])
			DFS(GL, p->adjvex);//��Ϊ���ʵ��ڽӶ���ݹ����
		p = p->next;
	}
}

void DFSTraverse(GraphAdjList GL) {
	int i;
	for (i = 0;i < GL.numVertexes;i++)
		visited[i] = false;
	for (i = 0;i < GL.numVertexes;i++)
		if (!visited[i])
			DFS(GL, i);
}

void Print_G(GraphAdjList G) {
	int i;
	EdgeNode *e;
	for (i = 0;i < G.numVertexes;i++) {
		printf("%c", G.adjList[i].data);
		e = G.adjList[i].firstedge;
		while (e) {
			printf("-->%d", e->adjvex);
			e = e->next;
		}
		printf("\n");
	}
}

void BFSTraverse(GraphAdjList GL) {
	int i;
	EdgeNode *p;
	SqQueue Q;
	for (i = 0;i < GL.numVertexes;i++)
		visited[i] = false;
	InitQueue_G(&Q);
	for (i = 0;i < GL.numVertexes;i++) {
		if (!visited[i]) {
			visited[i] = true;
			printf("%c ", GL.adjList[i].data);
			EnQueue_G(&Q, i);
			while (Q.front != Q.rear) {
				DeQueue_G(&Q, &i);
				p = GL.adjList[i].firstedge;
				while (p) {
					if (!visited[p->adjvex]) {
						visited[p->adjvex] = true;
						printf("%c ", GL.adjList[p->adjvex].data);
						EnQueue_G(&Q, p->adjvex);
					}
					p = p->next;
				}
			}
		}
	}

}

void Menue5() {
	printf("ͼ��ϵͳ\n");
	printf("==============================================\n");
	printf("||                 1--�����ڽӱ�            ||\n");
	printf("||                 2--������ȱ���          ||\n");
	printf("||                 3--������ȱ���          ||\n");
	printf("||                 4--��ʾ�ڽ�ͼ            ||\n");
	printf("||                 0--����                  ||\n");
	printf("==============================================\n");
	printf("������˵���(0-4):");
}

void graph() {
	GraphAdjList G;
	int i, n;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue5();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("Ҫ������������ͼ(1)��������ͼ(0),��ѡ��(����1����0):");
			scanf("%d",&n);
			CreatALGraph(&G,n);
			getchar();
			break;
		case '2':
			printf("������ȱ���������Ϊ:");
			DFSTraverse(G);
			break;
		case '3':
			printf("������ȱ���������Ϊ:");
			BFSTraverse(G);
			break;
		case '4':
			printf("ͼΪ:\n");
			Print_G(G);
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