#define _CRT_SECURE_NO_WARNINGS 1//���vs��scanf����
#include"StudetSystem.h"

int main()

{
	Load();
	while(1)
	{

		switch (MenuSelect())
		{
		case 1:
			DisplayStuData();//��ʾ
			break;
		case 2:
			AddDate();//��
			break;
		case 3:
			QueryStuData();//��
			break;
		case 4:
			ReviseStuData();//��
			break;
		case 5:
			DeleteStuData();//ɾ
			break;
		case 0:
			printf("\n\t\tллʹ�ã��ټ�!\n");
			printf("\n\t\t");
			system("pause");
			exit(0);
			}
	}
	return 0;	
}