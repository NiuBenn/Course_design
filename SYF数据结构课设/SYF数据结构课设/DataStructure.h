#pragma once
#include<stdio.h>
#include<stdlib.h>

#define MAX 20
#define DataType char

typedef struct ArcNode 
{
	int _Adjvex;	//储存边所指的顶点位置
	int _Weight;	//储存该边的权重
	struct ArcNode *_NextArc;		//指向下一条边的指针
}ArcNode;


typedef struct VexNode
{
	DataType _data;		//顶点信息
	int _InDegree;		//入度
	int _Flag;			//拓扑排序是用来判断是否排过
	int _Ve;			//最早发生时间
	int _Vl;			//最晚发生时间
	ArcNode *_FirstArc;		//指向第一条依附该顶点的弧
}VexNode;

typedef struct ALGraph
{
	VexNode *_AdjList;	//邻接表
	int _VexNum;	//结点数目
	int _ArcNum;	//边的数目
}ALGraph;


void ClearStdin()
{
	char ch; 
	while ((ch = getchar()) != '\n' && ch != EOF);
}

int IfHaveThisVex(ALGraph* graph, DataType data)
{
	//判断该顶点是否在_AdjList(Vex数组)中
	//存在返回所在位置下标，不存在返回-1
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
	int ArcNum = 0;		//定义ArcNum存放边的个数，作为次函数最后返回值
	int Weight;
	int FirstIndex, SecondIndex;	//定义两个index存放边的两个顶点在数组中的下标
	DataType FirstVex, SecondVex;	//定义一个边的两个顶点值，用于接收用户输入的边的两个顶点信息

	for (int i = 0; i < graph->_VexNum; ++i)
	{
		ClearStdin();		//清空输入缓冲区
		//对已经malloc出来的每个顶点初始化
		printf("请输入第%d个顶点的信息(例如顶点名为A，则输入A):", i + 1);
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
		ClearStdin();		//清空输入缓冲区
		printf("请输入有向图中边的两个顶点以及权重(例:A->B 则输入A B)：");
		scanf("%c %c %d", &FirstVex, &SecondVex, &Weight);
		FirstIndex = IfHaveThisVex(graph, FirstVex);
		SecondIndex = IfHaveThisVex(graph, SecondVex);

		if (FirstIndex == -1 || SecondIndex == -1)
		{
			i = i - 1;
			printf("输入顶点信息错误，请重新输入！！\n");
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
	printf("请输入有向图顶点的个数：");
	scanf("%d", &(graph->_VexNum));
	printf("请输入有向图边的条数：");
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
		printf("事件输出数量小于总数量，图中带环！！\n");
	}
	else
	{
		printf("事件输出数量等于总数量，图中不带环！！\n");
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

