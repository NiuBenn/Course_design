#define _CRT_SECURE_NO_WARNINGS 1
#include"Menu.h"

int main()
{
	ALGraph G;
	int arr[MAX];		//�����������˳��
	arr[MAX - 1] = 0;	//��־λ���ж��Ƿ���й���������
	arr[MAX - 2] = 0;	//��־λ���ж��Ƿ���й�����������
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
			printf("\t\tϵͳ�˳�����\n");
			system("pause");
			exit(0);
		}
	}

}
