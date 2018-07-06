#define _CRT_SECURE_NO_WARNINGS 1//解决visual studio中scanf不安全报错;
#include"StudetSystem.h"

char* filename = "D:/StudentData.dat";//要读取以及写入的文件

StudentNode* Student;//链表头指针

void Load()//初始化
{
	printf("\n\t\t\t   学生信息管理系统\n\n");
	printf("\t\t\t     版本号：2.0\n");
	printf("\n\t\t\t    2018年6月18日\n");
	printf("\t\t\t      制作人：田丰\n");
	printf("\t\t\t系统启动中，请稍等.....\n");

	LoadDataFromFile();//从文件中加载数据
	system("pause");//卡屏
}

void LoadDataFromFile()//从文件加载数据
{
	FILE *fp;//File指针fp用于后续文件操作
	StudentNode* NowStudent;//当前进行操作的结点指针
	int count = 0;//用于统计读取创建结点进行次数

	if ( NULL ==(fp = fopen(filename, "r")))//如果文件打开失败（不存在）
	{
		//创建文件后return退出此层函数栈桢
		fp = fopen(filename, "a");
		fclose(fp);
		return;
	}

	Student = BuyStudentNode("","",0,0);//以空num,空name创建结点，
	NowStudent = Student;//将刚创建的结点指针给当前进行操作的结点指针
	while (!feof(fp))//while循环,直到文件结尾EOF
	{
		//从文件读取StudentNode大小数据给当前进行操作的结点
		fread(NowStudent, sizeof(StudentNode), 1, fp);
		NowStudent->_Next = BuyStudentNode("", "", 0, 0);//开辟新节点链在当前节点后
		NowStudent = NowStudent->_Next;//当前结点指针指向后续节点
		count++;//count++
	}

	//上面从文件读取操作，因为提前开结点，会导致多开两个("", "", 0, 0)结点
	//所以后面操作删除多开结点
	NowStudent = Student;//链表头指针给当前进行操作的结点指针
	while (strcmp(NowStudent->_Next->_num, ""))//while循环找到->_Next学号为""的结点
	{
		NowStudent = NowStudent->_Next;
	}

	free(NowStudent->_Next->_Next); //free掉多开的两个结点 
	NowStudent->_Next->_Next = NULL;
	free(NowStudent->_Next);
	NowStudent->_Next = NULL;

	if (count == 1)//count为1时表示未读到有效数据，也就是头结点是多开的无效数据结点
	{
		free(Student);//free掉头，指针置空
		Student = NULL;
	}
	fclose(fp);//关闭文件
}

void WriteDataToFile()
{
	FILE* fp;//FILE指针
	StudentNode* tmp = Student;//tmp指针指向头

	if ((fp = fopen(filename, "w")) == NULL)//以w只写方式打开，失败return
	{
		printf("cannot open the files\n");
		system("pause");//卡屏
		return;
	}

	while (tmp)//从头节点依次将各个节点写入文件
	{
		if (fwrite(tmp, sizeof(StudentNode), 1, fp) != 1)//每次写StudentNode大小
			printf("file write error\n");
		tmp = tmp->_Next;//写完当前结点，指针指向后续结点
	}

	fclose(fp);//关闭文件
}

int MenuSelect()//主界面菜单
{
	char c;//此处用char类型相比int节省3字节空间;
	do {
		system("cls");
		printf("\t\t ╭————————■□■□————╮\n");
		printf("\t\t│         学生成绩管理系统         │\n");
		printf("\t\t╰—————■□■□————————╯\n");
		printf("\t\t   ┌——————————————┐\n");
		printf("\t\t   │ 1. 显示成绩    2. 新增成绩 │\n");
		printf("\t\t   │                            │\n");
		printf("\t\t   │ 3. 成绩查询    4. 成绩修改 │\n");
		printf("\t\t   │                            │\n");
		printf("\t\t   │ 5. 删除成绩    0.退出程序  │\n");
		printf("\t\t   └——————————————┘\n");
		printf("\t\t请您选择(0-5):");
		fflush(stdin);//清空输入缓冲区，因为getchar是从输入缓冲区获取字符，确保输入缓冲区干净;
		c = getchar();//获取字符;
	} while (c<'0' || c>'5');//确保输入合法;

	return (c - '0');//将数字字符转为对应asscll码值返回;
}

StudentNode* BuyStudentNode(char* num, char* name, int English, int Math)//创建学生结点
{
	StudentNode* tmp = (StudentNode*)malloc(sizeof(StudentNode));//malloc申请空间开辟节点

	if (tmp != NULL)//判断结点是否开辟成功
	{
		strcpy(tmp->_num, num);//将num字符串拷贝到新开结点tmp的_num;
		strcpy(tmp->_name, name);//将name字符串拷贝到新开结点tmp的_name;
		tmp->_English = English;
		tmp->_Math = Math;
		tmp->_Next = NULL;//English，math赋值后返回tmp指针；

		return tmp;
	}

	printf("结点创建失败！！");
	return NULL;//结点malloc失败，返回空指针
}

void DisplayStuData()//显示成绩数据
{
	StudentNode* tmp = Student;//tmp指针指向头结点
	system("cls");//清除屏幕

	if (tmp == NULL)//头结点为空,即无有效数据，return退出此层函数栈桢
	{
		printf("当前无学生相关成绩数据,请添加数据后再试！！\n");
		system("pause");//卡屏
		return;
	}

	printf("学号\t     姓名\t 英语成绩   数学成绩\n");

	while (tmp)//依次打印各个节点数据
	{
		printf("%s  %s  \t    %d \t    %d\n", tmp->_num, tmp->_name, tmp->_English, tmp->_Math);
		tmp = tmp->_Next;//指向后续结点
	}

	system("pause");//卡屏
}

void AddDate()
{
	char flag = 'y';//flag用来判断是否需要继续添加
	char num[15], name[15];
	int English, Math;
	StudentNode** ppHead = &Student;//ppHead二级指针指向头结点指针用于处理头结点为空的情况
	StudentNode* tmp = *ppHead;//tmp指针指向头结点
	StudentNode* newNode;//newNode指针用于放新开结点的地址
	system("cls");//清除屏幕

	while (flag != 'n' && flag != 'N')//当结尾输入N、n时结束继续添加
	{
		printf("\t\t\t ----学生纪录添加----\n");
		printf("请输入您要添加的学生学号：");
		scanf("%s", num);
		printf("请输入您要添加的学生姓名：");
		scanf("%s", name);
		printf("请输入您要添加的学生英语成绩：");
		scanf("%d", &English);
		printf("请输入您要添加的学生数学成绩：");
		scanf("%d", &Math);
		
		newNode = BuyStudentNode(num, name, English, Math);//用输入的数据开辟新的节点
		
		if (NULL == *ppHead)//当头结点为空的情况,将新开结点直接给头，同时将tmp重新指向头结点
		{
			*ppHead = newNode;
			(*ppHead)->_Next = NULL;
			tmp = *ppHead;
		}
		else
		{
			while (tmp->_Next)//将tmp至到尾节点，链上新的结点
			{
				tmp = tmp->_Next;
			}
			tmp->_Next = newNode;
			newNode->_Next = NULL;
		}
		
		printf("是否继续添加?(y/n)");
		scanf("\t%c", &flag);
		system("cls");
	}

	WriteDataToFile();//将上述数据改动写入到文件
}

StudentNode* QueryStuData()//查找数据,返回找到结点的指针，没找到返回空
{
	StudentNode* tmp = Student;//tmp指针指向头结点
	char num[15];
	system("cls");

	if (tmp == NULL)//当头为空
	{
		printf("当前无学生相关成绩数据,请添加数据后再试！！\n");
		system("pause");
		return NULL;
	}

	printf("请输入你所需学生的学号：");
	scanf("%s", num);

	//用strcmp比较num字符串直到找到所需数据，或者所有数据全部找完结束循环
	while ( tmp != NULL && strcmp(tmp->_num, num))
	{
		tmp = tmp->_Next;
	}

	if (tmp == NULL)//没找到时返回空指针
	{
		printf("未查询到该学生相关成绩信息！");
		system("pause");
		return NULL;
	}
	else//找到后输出数据到屏幕
	{
		printf("学号:%s\n姓名:%s\n1.英语成绩:%d\n2.数学成绩:%d\n",tmp->_num,tmp->_name,tmp->_English,tmp->_Math);
		system("pause");
		return tmp;//返回tmp指针做函数返回值
	}
}

int ReviseStuData()//修改数据
{
	StudentNode* Query = QueryStuData();//先用QueryStuData函数找要修改的结点
	char c;
	if (NULL == Query)
	{
		printf("学生成绩修改失败！");
		system("pause");
		return 1;
	}
	
	printf("请输入你要修改成绩的科目(1或2)：");
	do {
		fflush(stdin);//清空输入缓冲区，因为getchar是从输入缓冲区获取字符，确保输入缓冲区干净;
		c = getchar();//获取字符;
	} while (c<'1' || c>'2');//确保输入合法;
	printf("请输入该科目新的成绩：");

	switch (c)
	{
	case '1':
		scanf("%d", &(Query->_English));
		break;
	case '2':
		scanf("%d", &(Query->_Math));
		break;
	}

	WriteDataToFile();//将上述数据改动写入到文件

	printf("成绩修改成功！");
	system("pause");
	return 0;
}

void DeleteStuData()
{
	StudentNode* Delete,* tmp;
	tmp = Student;//tmp指向头结点
	system("cls");

	if (NULL == tmp)//当头为空时候return
	{
		printf("当前无学生相关成绩数据,请添加数据后再试！！\n");
		system("pause");
		return;
	}

	Delete = QueryStuData();//用QueryStuData函数找要删除的结点
	if (NULL == Delete)//没找到时return
	{
		printf("请核对有无该学生信息后再试！");
		system("pause");
		return;
	}
	else
	{
		if (Delete == tmp)//当要删除的为头结点时，将Student指向后续结点，free头结点
		{
			Student = Student->_Next;
			free(tmp);
			tmp = NULL;
		}
		else
		{
			while (tmp->_Next != Delete)//while循环直到tmp的next为要删除的结点
			{
				tmp = tmp->_Next;
			}
			tmp->_Next = tmp->_Next->_Next;//tmp的next指针指向后面的后面
			free(Delete);//free掉要删除的结点
			Delete = NULL;
		}
	}

	WriteDataToFile();//将上述数据改动写入到文件

	printf("删除成功！");
	system("pause");
}

