#define _CRT_SECURE_NO_WARNINGS 1//解决vs中scanf报错
#include"StudetSystem.h"

int main()

{
	Load();
	while(1)
	{

		switch (MenuSelect())
		{
		case 1:
			DisplayStuData();//显示
			break;
		case 2:
			AddDate();//增
			break;
		case 3:
			QueryStuData();//查
			break;
		case 4:
			ReviseStuData();//改
			break;
		case 5:
			DeleteStuData();//删
			break;
		case 0:
			printf("\n\t\t谢谢使用，再见!\n");
			printf("\n\t\t");
			system("pause");
			exit(0);
			}
	}
	return 0;	
}