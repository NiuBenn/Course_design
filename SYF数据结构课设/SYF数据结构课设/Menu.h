#pragma once
#include"DataStructure.h"
int menu_select()
{
	int i;
	do {
		system("cls");
		printf("\t\t �q���������������������������������������r\n");
		printf("\t\t��        �� �� �� �� �� �� �� ��       ��\n");
		printf("\t\t�t���������������������������������������s\n");
		printf("\t\t   ������������������������������������\n");
		printf("\t\t   ��     1. ���ڽӱ�洢����ͼ      ��\n");
		printf("\t\t   ��                                ��\n");
		printf("\t\t   ��     2. �� ʾ �� �� ��          ��\n");
		printf("\t\t   ��                                ��\n");
		printf("\t\t   ��     3. ��  ��  ��  ��          ��\n");
		printf("\t\t   ��                                ��\n");
		printf("\t\t   ��     4. �� �� �� �� ��          ��\n");
		printf("\t\t   ��                                ��\n");
		printf("\t\t   ��     0.�˳�                     ��\n");
		printf("\t\t   ������������������������������������\n");
		printf("\t\t��ѡ��(0-4):");
		scanf("%d", &i);
	} while (i < 0 || i>4);
	return i;
}

