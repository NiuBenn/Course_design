#pragma once
#include<stdio.h>
#include<stdlib.h>

#define MAX 20
#define DataType char

typedef struct ArcNode 
{
	int _Adjvex;	//�������ָ�Ķ���λ��
	int _Weight;	//����ñߵ�Ȩ��
	struct ArcNode *_NextArc;		//ָ����һ���ߵ�ָ��
}ArcNode;


typedef struct VexNode
{
	DataType _data;		//������Ϣ
	int _InDegree;		//���
	int _Flag;			//���������������ж��Ƿ��Ź�
	int _Ve;			//���緢��ʱ��
	int _Vl;			//������ʱ��
	ArcNode *_FirstArc;		//ָ���һ�������ö���Ļ�
}VexNode;

typedef struct ALGraph
{
	VexNode *_AdjList;	//�ڽӱ�
	int _VexNum;	//�����Ŀ
	int _ArcNum;	//�ߵ���Ŀ
}ALGraph;


void ClearStdin()
{
	char ch; 
	while ((ch = getchar()) != '\n' && ch != EOF);
}

int IfHaveThisVex(ALGraph* graph, DataType data)
{
	//�жϸö����Ƿ���_AdjList(Vex����)��
	//���ڷ�������λ���±꣬�����ڷ���-1
	for (int i = 0; i < graph->_VexNum; ++i)
	{
		if (graph->_AdjList[i]._data == data)
		{
			return i;
		}
	}
	return -1;
}

void CreatAdjList(ALGraph* graph)
{
	int ArcNum = 0;		//����ArcNum��űߵĸ�������Ϊ�κ�����󷵻�ֵ
	int Weight;
	int FirstIndex, SecondIndex;	//��������index��űߵ����������������е��±�
	DataType FirstVex, SecondVex;	//����һ���ߵ���������ֵ�����ڽ����û�����ıߵ�����������Ϣ

	for (int i = 0; i < graph->_VexNum; ++i)
	{
		ClearStdin();		//������뻺����
		//���Ѿ�malloc������ÿ�������ʼ��
		printf("�������%d���������Ϣ(���綥����ΪA��������A):", i + 1);
		scanf("%c", &(graph->_AdjList[i]._data));
		graph->_AdjList[i]._Flag = 0;
		graph->_AdjList[i]._Ve = 0;
		graph->_AdjList[i]._Vl = INT_MAX;
		graph->_AdjList[i]._InDegree = 0;
		graph->_AdjList[i]._FirstArc = NULL;
	}

	system("cls");
	for (int i = 0; i < graph->_ArcNum; ++i)
	{
		ClearStdin();		//������뻺����
		printf("����������ͼ�бߵ����������Լ�Ȩ��(��:A->B ������A B)��");
		scanf("%c %c %d", &FirstVex, &SecondVex, &Weight);
		FirstIndex = IfHaveThisVex(graph, FirstVex);
		SecondIndex = IfHaveThisVex(graph, SecondVex);

		if (FirstIndex == -1 || SecondIndex == -1)
		{
			i = i - 1;
			printf("���붥����Ϣ�������������룡��\n");
			continue;
		}
		ArcNode * NewArc = (ArcNode*)malloc(sizeof(ArcNode));
		NewArc->_Adjvex = SecondIndex;
		NewArc->_Weight = Weight;
		NewArc->_NextArc = graph->_AdjList[FirstIndex]._FirstArc;
		graph->_AdjList[FirstIndex]._FirstArc = NewArc;
		graph->_AdjList[SecondIndex]._InDegree++;
	}
}

void ALGraphInit(ALGraph* graph)
{
	system("cls");
	printf("����������ͼ����ĸ�����");
	scanf("%d", &(graph->_VexNum));
	printf("����������ͼ�ߵ�������");
	scanf("%d", &(graph->_ArcNum));

	graph->_AdjList = (VexNode*)malloc(sizeof(VexNode)*(graph->_VexNum));
	CreatAdjList(graph);
}

void PrintfVexNode(VexNode *node)
{
	ArcNode* cur = node->_FirstArc;
	printf("[%c]", node->_data);
	if (cur)
	{
		printf("-->[ %d ]", cur->_Adjvex);
		cur = cur->_NextArc;
	}
	while (cur)
	{
		printf("-->[ %d ]", cur->_Adjvex);
		cur = cur->_NextArc;
	}
	printf("-->[NULL]\n");
}

void PrintfAdjList(ALGraph* graph)
{
	system("cls");
	for (int i = 0; i < graph->_VexNum; ++i)
	{
		printf("%d ", i);
		PrintfVexNode(&(graph->_AdjList[i]));
	}
	system("pause");
}

void TopologicalSorting(ALGraph* graph,int *arr)
{
	system("cls");
	int count = 0;
	int flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i = 0; i < graph->_ArcNum; ++i)
		{
			if (graph->_AdjList[i]._InDegree == 0 && graph->_AdjList[i]._Flag == 0)
			{
				flag = 1;
				graph->_AdjList[i]._Flag = 1;
				
				arr[count] = i;
				count++;

				ArcNode* cur = graph->_AdjList[i]._FirstArc;
				while (cur)
				{
					if (cur->_Weight + graph->_AdjList[i]._Ve > graph->_AdjList[cur->_Adjvex]._Ve)
					{
						graph->_AdjList[cur->_Adjvex]._Ve = cur->_Weight + graph->_AdjList[i]._Ve;
					}
					graph->_AdjList[cur->_Adjvex]._InDegree--;
					
					cur = cur->_NextArc;
				}
				break;
			}
		}
	}
	
	for (int i = 0; i < count; ++i)
	{
		printf("[%c][Ve: %d]--", graph->_AdjList[arr[i]]._data, graph->_AdjList[arr[i]]._Ve);
	}

	printf("[NULL]\n");

	if (count < graph->_VexNum)
	{
		printf("�¼��������С����������ͼ�д�������\n");
	}
	else
	{
		printf("�¼��������������������ͼ�в���������\n");
	}
	system("pause");
}

void RTopologicalSorting(ALGraph* graph, int *arr)
{
	system("cls");
	graph->_AdjList[arr[graph->_VexNum - 1]]._Vl = graph->_AdjList[arr[graph->_VexNum - 1]]._Ve;
	for (int i = graph->_VexNum - 2; i >= 0; --i)
	{
		ArcNode *cur = graph->_AdjList[arr[i]]._FirstArc;
		while (cur)
		{
			if ((graph->_AdjList[cur->_Adjvex]._Vl) - (cur->_Weight) < graph->_AdjList[arr[i]]._Vl)
			{
				graph->_AdjList[arr[i]]._Vl = (graph->_AdjList[cur->_Adjvex]._Vl) - (cur->_Weight);
			}
			cur = cur->_NextArc;
		}
	}

	for (int i = graph->_VexNum - 1; i >= 0; --i)
	{
		printf("[%c][Ve: %d]--", graph->_AdjList[arr[i]]._data, graph->_AdjList[arr[i]]._Vl);
	}
	printf("[NULL]");
	system("pause");
}

