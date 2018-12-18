#pragma once
#include"DataStructure.h"
int menu_select()
{
	int i;
	do {
		system("cls");
		printf("\t\t ╭——————————■□■□—————╮\n");
		printf("\t\t│        数 据 结 构 课 程 设 计       │\n");
		printf("\t\t╰———■□■□————————————╯\n");
		printf("\t\t   ┌————————————————┐\n");
		printf("\t\t   │     1. 用邻接表存储有向图      │\n");
		printf("\t\t   │                                │\n");
		printf("\t\t   │     2. 显 示 邻 接 表          │\n");
		printf("\t\t   │                                │\n");
		printf("\t\t   │     3. 拓  扑  排  序          │\n");
		printf("\t\t   │                                │\n");
		printf("\t\t   │     4. 逆 拓 扑 排 序          │\n");
		printf("\t\t   │                                │\n");
		printf("\t\t   │     0.退出                     │\n");
		printf("\t\t   └————————————————┘\n");
		printf("\t\t请选择(0-4):");
		scanf("%d", &i);
	} while (i < 0 || i>4);
	return i;
}

