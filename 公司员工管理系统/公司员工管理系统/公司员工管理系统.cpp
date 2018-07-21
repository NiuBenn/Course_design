#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
using namespace std;

#include<stdlib.h>
#include<assert.h>

class Move
{
private:
	int _ID;
	char _Name[15];
	int _LastJob;
	int _NowJob;

public:

	Move & operator = (const Move& move)
	{
		if (&move != this)
		{
			_ID = move._ID;
			strcpy(_Name, move._Name);
			_LastJob = move._LastJob;
			_NowJob = move._NowJob;
		}

		return *this;
	}

	void SetMove(int ID, char* Name, int LastJob, int NowJob)
	{
		_ID = ID;
		strcpy(_Name, Name);
		_LastJob = LastJob;
		_NowJob = NowJob;
	}

	friend void DisplayMoveInformation(Move* move, int nMove);

	friend void WriteDateForFileMoveInformation(Move* move, int nMove);

};

class Workers
{
private:
	int _ID;
	char _Name[15];
	int _Job;
	int _WorkTimeIn;		//考勤在
	int _WorkTimeNotIn;		//考勤不在
	int _OneTimeMoney;
	int _FinalMoney;

public:

	void SetWorkers(int ID, char* Name, int Job, int OneTimeMoney, int FinalMoney , int WorkTimeIn = 0, int WorkTimeNotIn = 0)
	{
		_ID = ID;
		strcpy(_Name, Name);
		_Job = Job;
		_WorkTimeIn = WorkTimeIn;
		_WorkTimeNotIn = WorkTimeNotIn;
		_OneTimeMoney = OneTimeMoney;
		_FinalMoney = FinalMoney;
	}

	Workers& operator = (const Workers& workers)	//赋值运算符重载
	{
		if (&workers != this)
		{
			_ID = workers._ID;
			strcpy(_Name, workers._Name);
			_Job = workers._Job;
			_WorkTimeIn = workers._WorkTimeIn;
			_WorkTimeNotIn = _WorkTimeNotIn;
			_OneTimeMoney = workers._OneTimeMoney;
			_FinalMoney = workers._FinalMoney;
		}
		return *this;
	}

	void printer()
	{
		cout << "员工号：" << _ID << endl;
		cout << "姓名：" << _Name << endl;
		cout << "职位：";
		switch (_Job)
		{
		case 1:
			cout << "经理" << endl;
			break;
		case 2:
			cout << "兼职技术人员" << endl;
			break;
		case 3:
			cout << "销售经理" << endl;
			break;
		case 4:
			cout << "兼职销售人员" << endl;
			break;
		}
		system("pause");
	}

	friend void DisplayWorkers(Workers* workers, int nWorkers);	//显示员工基本信息
	
	friend int SearchWorkers(Workers* workers, int nWorkers);	//查找员工信息
	
	friend void Revise(Workers* workers, int nWorkers);		//修改

	friend void AddAttendance(Workers* workers, int nWorkers);	//增加考勤

	friend int SearchAttendance(Workers* workers, int nWorkers);	//查询考勤

	friend void ReviseAttendance(Workers* workers, int nWorkers);	//修改考勤

	friend void DeleteAttendance(Workers* workers, int nWorkers);	//删除考勤

	friend void DisplayAttendance(Workers* workers, int nWorkers);	//显示考勤信息

	friend void AddMoveInformation(Workers* workers, int nWorkers, Move* move, int* nMove);

	friend void DisplayMoveInformation(Move* move, int nMove);

	friend void WriteDateForFileWorkers(Workers* workers, int nWorkers);

};

void printfJob(int job)
{
	if (job == 1)
	{
		cout << "经理    " ;
	}
	else if (job == 2)
	{
		cout << "兼职技术人员     ";
	}
	else if (job == 3)
	{
		cout << "销售经理     ";
	}
	else if (job == 4)
	{
		cout << "兼职推销员     ";
	}
}

//void DisplayOrReviseMoney(int* FinalMoney, int* OneTimeMoney)	//查看或者修改工资
//{
//	char flag = 'n';
//	system("cls");
//	cout << "当前经理月固定工资为：" << *FinalMoney << "(元)" << endl;
//	cout << "当前兼职人员每天(8小时)工资为：" << *OneTimeMoney << "(元)" << endl;
//	cout << "是否修改？？<y/n>:";
//	cin >> flag;
//	if (flag != 'y'&&flag != 'Y')
//	{
//		system("pause");
//		return;
//	}
//	else
//	{
//		cout << "请重新设定经理月固定工资：";
//		cin >> *FinalMoney;
//		cout << "请重新设定兼职人员每天(8小时)工资";
//		cin >> *OneTimeMoney;
//		cout << "修改成功！！" << endl;
//		system("pause");
//	}
//}

void AddWorkers(Workers* workers, int* nWorkers, int* nID, int FinalMoney,int OneTimeMoney)		//添加员工信息
{
	system("cls");
	char flag = 'y';
	char Name[15];
	int Job;

	while (flag != 'n' && flag != 'N')//当结尾输入N、n时结束继续添加
	{
		cout << "员工号由系统自动生成！！！" << endl;
		cout << "请输入你要添加的员工姓名:";
		cin >> Name;
		cout << "请输入该员工的职位\n(经理:1 兼职技术人员:2 销售经理:3 兼职推销员:4):";
		cin >> Job;

		workers[*nWorkers].SetWorkers(*nID + 1, Name, Job, OneTimeMoney ,FinalMoney);
		(*nWorkers)++;
		(*nID)++;

		cout << "是否继续添加?(y/n):" ;
		cin >> flag;
		system("cls");
	}
	WriteDateForFileWorkers(workers, *nWorkers);
}

void DisplayWorkers(Workers* workers, int nWorkers)		//显示员工信息
{
	system("cls");

	cout << "员工号   姓名   职位" << endl;
	for (int i = 0; i < nWorkers; ++i)
	{
		cout << workers[i]._ID << "     " << workers[i]._Name << "    ";
		printfJob(workers[i]._Job);
		cout << endl;
	}
	system("pause");
}

int SearchWorkers(Workers* workers, int nWorkers)	//查找员工信息
{
	int Index = 0;
	int ID;
	char Name[10];
	char c;
	do {
		system("cls");
		cout << "请选择" << endl;
		cout << "1.按照员工号" << endl;
		cout << "2.按照员工姓名" << endl;
		fflush(stdin);
		c = getchar();
	} while (c > '2' || c < '1');

	switch (c)
	{
	case '1':
		system("cls");
		{
			cout << "请输入你需要的员工号：";
			cin >> ID;
			for (; Index < nWorkers; ++Index)
			{
				if (workers[Index]._ID == ID)
				{
					workers[Index].printer();
					return Index;
				}
			}
			cout << "未找到该员工的相关信息！！" << endl;
			system("pause");
			return -1;
		}

	case '2':
		system("cls");
		{
			cout << "请输入你需要的员工姓名：";
			cin >> Name;

			for (; Index < nWorkers; ++Index)
			{
				if (strcmp(Name, workers[Index]._Name) == 0)
				{
					workers[Index].printer();
					return Index;
				}
			}
			cout << "未找到该员工的相关信息！！" << endl;
			system("pause");
			return -1;
		}
	}

}

void Revise(Workers* workers, int nWorkers)	//修改员工信息
{
	int Index = SearchWorkers(workers, nWorkers);
	if (Index == -1)
	{
		return;
	}

	char Name[15];
	int Job;
	cout << "员工号由系统生成！无法修改！";
	cout << "请输入修改后的姓名：";
	cin >> Name;
	cout << "请输入修改后的职位\n(经理:1 兼职技术人员:2 销售经理:3 兼职推销员:4):";
	cin >> Job;

	workers[Index].SetWorkers(workers[Index]._ID, Name, Job, workers[Index]._OneTimeMoney,
		workers[Index]._FinalMoney, workers[Index]._WorkTimeIn,workers[Index]._WorkTimeNotIn);
	
	WriteDateForFileWorkers(workers, nWorkers);
	cout << "信息修改成功！" << endl;
	system("pause");

}

void Delete(Workers* workers, int* nWorkers)		//删除员工信息
{
	int Index = SearchWorkers(workers, *nWorkers);
	if (Index == -1)
	{
		return;
	}
	char c;
	cout << "是否删除？？<y/n>：";
	cin >> c;
	if (c == 'n' || c == 'N')
	{
		cout << "删除已取消！！" << endl;
		system("pause");
		return;
	}
	else
	{
		for (; Index < *nWorkers - 1; ++Index)
		{
			workers[Index] = workers[Index + 1];
		}
		(*nWorkers)--;

		WriteDateForFileWorkers(workers, *nWorkers);
		cout << "删除成功！" << endl;
		system("pause");
	}
}

void AddAttendance(Workers* workers, int nWorkers)
{
	system("cls");
	char flag;
	cout << "\t\t\t员工考勤" << endl;
	for (int i = 0; i < nWorkers; ++i)
	{
		cout << "当前对" << workers[i]._ID << " 号 " << workers[i]._Name << " 进行考勤" << endl;
		cout << "是否缺勤？？<y/n>:";
		
		cin >> flag;
		fflush(stdin);

		if (flag == 'n' || flag == 'N')
		{
			workers[i]._WorkTimeIn++;
		}
		else
		{
			workers[i]._WorkTimeNotIn++;
		}
	}
	WriteDateForFileWorkers(workers, nWorkers);
	cout << "考勤完毕!!" << endl;
	system("pause");
}

int SearchAttendance(Workers* workers, int nWorkers)
{
	int Index = SearchWorkers(workers, nWorkers);
	if (Index == -1)
	{
		return -1;
	}
	else
	{
		cout << "到勤次数为：" << workers[Index]._WorkTimeIn << endl;
		cout << "缺勤次数为：" << workers[Index]._WorkTimeNotIn << endl;
		system("pause");
		return Index;
	}
}

void ReviseAttendance(Workers* workers, int nWorkers)
{
	int Index = SearchAttendance(workers, nWorkers);
	if (Index == -1)
	{
		return;
	}
	else
	{
	
		cout << "请输入修改后的到勤次数：";
		cin >> workers[Index]._WorkTimeIn;
		cout << "请输入修改后的缺勤次数：";
		cin >> workers[Index]._WorkTimeNotIn;

		WriteDateForFileWorkers(workers, nWorkers);
		cout << "考勤信息修改完毕！！" << endl;
		system("pause");
	}
}

void DeleteAttendance(Workers* workers, int nWorkers)
{
	int Index = SearchAttendance(workers, nWorkers);
	if (Index == -1)
	{
		return;
	}
	else
	{
		char flag = 'n';
		cout << "是否删除此人的考勤信息(此操作会将到勤，缺勤次数全部至0)<y/n>:";
		cin >> flag;
		if (flag == 'n' || flag == 'N')
		{
			cout << "删除已取消！！" << endl;
			system("pause");
			return;
		}
		else
		{
			workers[Index]._WorkTimeIn = 0;
			workers[Index]._WorkTimeNotIn = 0;
		}
	}
	WriteDateForFileWorkers(workers, nWorkers);
	cout << "考勤信息删除成功！！" << endl;
	system("pause");
}

void DisplayAttendance(Workers* workers, int nWorkers)
{
	system("cls");
	cout << "员工号   姓名   职位   到勤   缺勤" << endl;
	for (int i = 0; i < nWorkers; ++i)
	{
		cout << workers[i]._ID << "     " << workers[i]._Name << "    ";
		printfJob(workers[i]._Job);
		cout << workers[i]._WorkTimeIn << "     ";
		cout << workers[i]._WorkTimeNotIn << endl;
	}
	system("pause");
}

void AddMoveInformation(Workers* workers, int nWorkers, Move* move, int* nMove)
{
	int Index = SearchWorkers(workers, nWorkers);
	int NowJob;
	if (Index == -1)
	{
		return;
	}
	cout << "请输入调动后的职位\n(经理:1 兼职技术人员:2 销售经理:3 兼职推销员:4):";
	cin >> NowJob;

	move[*nMove].SetMove(workers[Index]._ID, workers[Index]._Name, workers[Index]._Job, NowJob);
	(*nMove)++;
	workers[Index].SetWorkers(workers[Index]._ID, workers[Index]._Name, NowJob,workers[Index]._OneTimeMoney,
		workers[Index]._FinalMoney, workers[Index]._WorkTimeIn, workers[Index]._WorkTimeNotIn);

	WriteDateForFileMoveInformation(move, *nMove);
	cout << "调动已完成！！" << endl;
	system("pause");
}

void DisplayMoveInformation(Move* move, int nMove)
{
	if (nMove == 0)
	{
		cout << "无相关信息！！\n";
		system("pause");
		return;
	}
	system("cls");
	cout << "序号  员工编号   姓名   调动前职位  调动后职位" << endl;
	for (int i = 0; i < nMove; ++i)
	{
		cout << i + 1 << "       ";
		cout << move[i]._ID << "     ";
		cout << move[i]._Name << "     ";
		printfJob(move[i]._LastJob);
		printfJob(move[i]._NowJob);
		cout << endl;
	}
	system("pause");
}

void DeleteMoveInformation(Move* move, int* nMove)
{
	int Index;
	if (*nMove == 0)
	{
		cout << "无相关信息！！\n";
		system("pause");
		return;
	}
	DisplayMoveInformation(move, *nMove);
	cout << "请输入你要删除的调动信息序号：";
	cin >> Index;
	assert(Index <= *nMove );

	for (int i = Index - 1; i < *nMove - 1; ++i)
	{
		move[i] = move[i + 1];
	}
	(*nMove)--;

	WriteDateForFileMoveInformation(move, *nMove);
	cout << "删除成功！!" << endl;
	system("pause");
}

void LoadDateFromFile(Workers* workers, int* nWorkers, Move* move, int* nMove ,int* nID)
{
	FILE *fp1, *fp2;
	if (NULL == (fp1 = fopen("Workers.txt", "r")))//如果文件打开失败（不存在）
	{
		//创建文件后新增数据
		fp1 = fopen("Workers.txt", "a");
		fclose(fp1);
		cout << "第一次使用系统！将为您创建文件存放数据！" << endl;
		cout << "请您录入部分员工信息数据完成文件数据初始化！！" << endl;
		system("pause");
		AddWorkers(workers, nWorkers, nID, 6000, 150);
	}
	else
	{
		char Name[15];
		int ID, Job, WorkTimeIn, WorkTimeNotIn, OneTimeMoney, FinalMoney;
		char ch = fgetc(fp1);

		while (ch != '\n')//将第一行无效的数据字符读完
		{
			ch = fgetc(fp1);
		}

		while (ch = fgetc(fp1))
		{
			if (ch == EOF)//当读到文件结尾时候break,EOF为文件结尾标志
			{
				break;
			}
			//ungetc(ch, fp);

			fscanf(fp1, "%d%s%d%d%d%d%d", &ID, Name,&Job, &WorkTimeIn, &WorkTimeNotIn, &OneTimeMoney, &FinalMoney);

			workers[*nWorkers].SetWorkers(ID, Name,Job,OneTimeMoney,FinalMoney,WorkTimeIn,WorkTimeNotIn);
			(*nWorkers)++;
		}
		(*nWorkers)--;
		if (*nWorkers != 0)
		{
			*nID = ID;
		}
		fclose(fp1);
	}

	if (NULL == (fp2 = fopen("MoveInformation.txt", "r")))//如果文件打开失败（不存在）
	{
		fp1 = fopen("MoveInformation.txt", "a");
		return;
	}
	else
	{
		char Name[15];
		int ID, LastJob, NowJob;
		char ch = fgetc(fp2);

		while (ch != '\n')//将第一行无效的数据字符读完
		{
			ch = fgetc(fp2);
		}

		while (ch = fgetc(fp2))
		{
			if (ch == EOF)//当读到文件结尾时候break,EOF为文件结尾标志
			{
				break;
			}
			//ungetc(ch, fp);

			fscanf(fp1, "%d%s%d%d", &ID, Name, &LastJob, &NowJob);

			move[*nMove].SetMove(ID, Name, LastJob, NowJob);
			(*nMove)++;
		}
		(*nMove)--;
		fclose(fp2);
	}
}

void WriteDateForFileWorkers(Workers* workers, int nWorkers)
{
	FILE *fp = fopen("Workers.txt", "w");
	assert(fp != NULL);
	fprintf(fp, "员工号   姓名    职位   到勤   缺勤   天工资   月工资\n\n");
	for (int i = 0; i < nWorkers; ++i)
	{
		fprintf(fp, "%d    %s  %d   %d   %d   %d   %d\n", workers[i]._ID, workers[i]._Name, workers[i]._Job, 
			workers[i]._WorkTimeIn, workers[i]._WorkTimeNotIn, workers[i]._OneTimeMoney, workers[i]._FinalMoney);
	}
	fclose(fp);
}

void WriteDateForFileMoveInformation(Move* move, int nMove)
{
	FILE *fp = fopen("MoveInformation.txt", "w");
	assert(fp != NULL);
	fprintf(fp, "员工号   姓名   调动前职位  调动后职位\n\n");
	for (int i = 0; i < nMove; ++i)
	{
		fprintf(fp, "%d\t%s\t%d\t%d\n", move[i]._ID, move[i]._Name, move[i]._LastJob, move[i]._NowJob);
	}
	fclose(fp);
}

int menu_select()
{
	int i;
	do {
		system("cls");
		cout << "\t\t ╭——————————————■□■□—————╮\n";
		cout << "\t\t│                公司员工管理系统              │\n";
		cout << "\t\t╰———————■□■□————————————╯\n";
		cout << "\t\t   ┌—————————————————————┐\n";
		cout << "\t\t   │           1. 员工基本信息管理            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           2. 员工考勤信息管理            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           3. 员工调动信息管理            │\n";
		/*cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           4. 查看或设置经理固定月工资    │\n";
		cout << "\t\t   │              及兼职员工每日(8小时)工资   │\n";*/
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           0. 退出系统                    │\n";
		cout << "\t\t   └—————————————————————┘\n";
		cout << "\t\t请您选择(0-4):";
		cin >> i;
	} while (i < 0 || i>3);//确保输入合法;

	return i;
}

int menu_select1()
{
	int i;
	do {
		system("cls");
		cout << "\t\t ╭——————————————■□■□—————╮\n";
		cout << "\t\t│                 员工基本信息管理             │\n";
		cout << "\t\t╰———————■□■□————————————╯\n";
		cout << "\t\t   ┌—————————————————————┐\n";
		cout << "\t\t   │           1. 添加员工基本信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           2. 修改员工基本信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           3. 查询员工基本信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           4. 删除员工基本信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           5. 显示员工基本信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           0. 返回上一菜单                │\n";
		cout << "\t\t   └—————————————————————┘\n";
		cout << "\t\t请您选择(0-5):";
		cin >> i;
	} while (i < 0 || i>5);//确保输入合法;

	return i;
}

int menu_select2()
{
	int i;
	do {
		system("cls");
		cout << "\t\t ╭——————————————■□■□—————╮\n";
		cout << "\t\t│                 员工考勤信息管理             │\n";
		cout << "\t\t╰———————■□■□————————————╯\n";
		cout << "\t\t   ┌—————————————————————┐\n";
		cout << "\t\t   │           1. 添加员工考勤信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           2. 修改员工考勤信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           3. 查询员工考勤信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           4. 删除员工考勤信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           5. 显示员工考勤信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           0. 返回上一菜单                │\n";
		cout << "\t\t   └—————————————————————┘\n";
		cout << "\t\t请您选择(0-5):";
		cin >> i;
	} while (i < 0 || i>5);//确保输入合法;

	return i;
}

int menu_select3()
{
	int i;
	do {
		system("cls");
		cout << "\t\t ╭——————————————■□■□—————╮\n";
		cout << "\t\t│                 员工调动信息管理             │\n";
		cout << "\t\t╰———————■□■□————————————╯\n";
		cout << "\t\t   ┌—————————————————————┐\n";
		cout << "\t\t   │           1. 添加员工调动信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           2. 查看员工调动信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           3. 删除员工调动信息            │\n";
		cout << "\t\t   │                                          │\n";
		cout << "\t\t   │           0. 返回上一菜单                │\n";
		cout << "\t\t   └—————————————————————┘\n";
		cout << "\t\t请您选择(0-3):";
		cin >> i;
	} while (i < 0 || i>3);//确保输入合法;

	return i;
}

int main()
{
	Workers workers[15];
	Move move[15];
	int FinalMoney = 6000;	//月固定工资
	int OneTimeMoney = 150;	//兼职员工一天(8个小时)的工资
	int nWorkers = 0, nID = 0, nMove = 0;

	LoadDateFromFile(workers, &nWorkers, move, &nMove, &nID);

	while (1)
	{
	flag:
		switch (menu_select())
		{
		case 1:
			while (1)
			{
				switch (menu_select1())
				{
				case 1:
					AddWorkers(workers, &nWorkers, &nID, FinalMoney, OneTimeMoney);
					break;
				case 2:
					Revise(workers, nWorkers);
					break;
				case 3:
					SearchWorkers(workers, nWorkers);
					break;
				case 4:
					Delete(workers, &nWorkers);
					break;
				case 5:
					DisplayWorkers(workers, nWorkers);
					break;
				case 0:
					goto flag;
				}
			}

		case 2:
			while (1)
			{
				switch (menu_select2())
				{
				case 1:
					AddAttendance(workers, nWorkers);
					break;
				case 2:
					ReviseAttendance(workers, nWorkers);
					break;
				case 3:
					SearchAttendance(workers, nWorkers);
					break;
				case 4:
					DeleteAttendance(workers, nWorkers);
					break;
				case 5:
					DisplayAttendance(workers, nWorkers);
					break;
				case 0:
					goto flag;
				}
			}

		case 3:
			while (1)
			{
				switch (menu_select3())
				{
				case 1:
					AddMoveInformation(workers,nWorkers,move,&nMove);
					break;
				case 2:
					DisplayMoveInformation(move, nMove);
					break;
				case 3:
					DeleteMoveInformation(move, &nMove);
					break;
				case 0:
					goto flag;
				}
			}

		/*case 4:
			DisplayOrReviseMoney(&FinalMoney, &OneTimeMoney);
			break;*/

		case 0:
			cout << "\n\t\t谢谢使用，再见!\n";
			system("pause");
			exit(0);

		}
	}

	return 0;
}