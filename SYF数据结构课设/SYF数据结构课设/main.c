#define _CRT_SECURE_NO_WARNINGS 1
#include"Menu.h"

int main()
{
	ALGraph G;
	int arr[MAX];		//存放拓扑排序顺序
	arr[MAX - 1] = 0;	//标志位来判断是否进行过拓扑排序
	arr[MAX - 2] = 0;	//标志位来判断是否进行过逆拓扑排序
	while (1)
	{
		switch (menu_select())
		{
		case 1:
			ALGraphInit(&G);
			break;
		case 2:
			PrintfAdjList(&G);
			break;
		case 3:
			TopologicalSorting(&G,arr);
			break;
		case 4:
			RTopologicalSorting(&G, arr);
			break;
		case 5:
			KeyActivites(&G, arr);
			break;
		case 0:
			printf("\t\t系统退出！！\n");
			system("pause");
			exit(0);
		}
	}

}
