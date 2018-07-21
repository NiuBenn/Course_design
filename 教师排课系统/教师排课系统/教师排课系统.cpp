#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

#include<stdlib.h>
#include<assert.h>
#include<string.h>

class Teacher
{
public:
	char _Name[10];
	char _Num[5];
	int _WorkLoad;
	char _CourseName[5][10];	//用来存放已分配给该老师的课程名称
	int _nCorse;	//用来记录已分配给该老师的课程

public:

	void SetTeacher(char* Name, char* Num, int WorkLoad)
	{
		strcpy(_Name, Name);
		strcpy(_Num, Num);
		_WorkLoad = WorkLoad;
		_nCorse = 0;
	}

	friend void AddCourseForTeacher(Teacher* teacher, char* CourseName);	//将课程添加到老师的课程里面
};

class Course
{
	char _Name[10];
	char _Num[5];
	int _WeekHour;
	int _SumHour;
	int _Level;

public:
	Course & operator = (const Course course)	//赋值运算符重载
	{
		strcpy(_Name, course._Name);
		strcpy(_Num, course._Num);
		_WeekHour = course._WeekHour;
		_SumHour = course._SumHour;
		_Level = course._Level;

		return *this;
	}

	void SetCourse(char* Name, char* Num, int WeekHour, int SumHour, int Level)
	{
		strcpy(_Name, Name);
		strcpy(_Num, Num);
		_WeekHour = WeekHour;
		_SumHour = SumHour;
		_Level = Level;
	}

	friend void SortCourse(Course* course, int nCourse);	//对课程按照优先级进行排序

	friend void ArrangCourse(Teacher* teacher, int nTeacher, Course* course, int nCourse);
};

void AddTeacher(Teacher* teacher, int* pnTeacher)
{
	system("cls");
	char Name[10], Num[5];
	int WorkLoad,nTeacher;
	cout<<"请输入参与教学工作的教师人数：";
	cin >> nTeacher;
	for (int i = 0; i < nTeacher; ++i)
	{
		system("cls");
		cout << "请输入第" << i + 1 << "位老师的信息" << endl;
		cout << "请输入老师的姓名:";
		cin >> Name;
		cout << "请输入老师的教师号:";
		cin >> Num;
		cout << "请输入老师的工作量(以课程数目为单位):";
		cin >> WorkLoad;

		teacher[i].SetTeacher(Name, Num, WorkLoad);	//将输入的信息设置到Teacher对象中
	}
	*pnTeacher = nTeacher;
	cout << "教师信息已添加完毕，请按任意键返回主菜单输入课程信息！！" << endl;
	system("pause");
}

void AddCourse(Course* course, int*  pnCourse)
{
	system("cls");
	char Name[15], Num[5];
	int WeekHour, SumHour, Level, nCourse;
	cout << "请输入总的课程数目：";
	cin >> nCourse;
	for (int i = 0; i < nCourse; ++i)
	{
		system("cls");
		cout << "请输入第" << i+1 << "个课程的信息" << endl;
		cout << "请输入课程名称：";
		cin >> Name;
		cout << "请输入课程号：";
		cin >> Num;
		cout << "请输入周课时：";
		cin >> WeekHour;
		cout << "请输入总课时：";
		cin >> SumHour;
		cout << "请输入该课程的优先级：";
		cin >> Level;

		course[i].SetCourse(Name, Num, WeekHour, SumHour, Level);

	}

	*pnCourse = nCourse;
	cout << "课程信息已经添加完毕！请按任意键返回主菜单进行排课！！" << endl;
	system("pause");
}

void SortCourse(Course* course, int nCourse)	//对课程按照优先级排序
{
	for (int i = 0; i < nCourse - 1; i++)
	{
		for (int j = 0; j < nCourse - 1 - i; j++)
		{
			if (course[j]._Level > course[j + 1]._Level)
			{
				Course tmp;
				tmp = course[j];
				course[j] = course[j + 1];
				course[j + 1] = tmp;
			}
		}
	}
}

int FindMaxExpect(int* Expect, int nExpect)	//找期望
{
	int MaxExpect, nMaxExpect = 0;
	MaxExpect = Expect[0];
	for (int i = 0; i < nExpect; ++i)	//找到最大期望
	{
		if (Expect[i] < MaxExpect)
		{
			MaxExpect = Expect[i];
		}
	}
	for (int i = 0; i < nExpect; ++i)	//统计最大期望的个数
	{
		if (Expect[i] == MaxExpect)
		{
			++nMaxExpect;
		}
	}

	int key = rand() % nMaxExpect;	//随机值确定第几个maxexpect
	nMaxExpect = 0;

	for (int i = 0; i < nExpect; ++i)
	{
		if (Expect[i] == MaxExpect)
		{
			if (key == nMaxExpect)
			{
				return i;
			}
			else
			{
				++nMaxExpect;
			}
		}
	}

}

void AddCourseForTeacher(Teacher* teacher,char* CourseName)	//将课程添加到老师的课程里面
{
	strcpy(teacher->_CourseName[teacher->_nCorse], CourseName);
	teacher->_nCorse++;
}

void ArrangCourse(Teacher* teacher, int nTeacher, Course* course, int nCourse)//排课
{
	int Expect[20];

	SortCourse(course, nCourse);	//先对课程按照优先级进行排序

	for (int i = 0; i < nCourse; ++i)
	{
		system("cls");
		cout << "当前对各位老师对于课程：" << course[i]._Name << "的期望值进行统计" << endl;
		cout << "注：课程已经选满的老师不参与统计" << endl;

		for (int j = 0; j < nTeacher; ++j)
		{
			if (teacher[j]._nCorse < teacher[j]._WorkLoad)
			{
				cout << "请输入 " << teacher[j]._Name << " 老师对该课程的期望值：";
				cin >> Expect[j];
			}
			else
			{
				Expect[j] = 500;
			}
		}

		AddCourseForTeacher(&teacher[FindMaxExpect(Expect, nTeacher)], course[i]._Name);//将该课程添加到老师的课程里面
	}

	cout << "所有课程已经分配完成，可主菜单进行查看排课结果！！" << endl;
	system("pause");
}

void Display(Teacher* teacher,int nTeacher)
{
	system("cls");
	for (int i = 0; i < nTeacher; ++i)
	{
		cout << teacher[i]._Name << "： ";
		for (int j = 0; j < teacher[i]._nCorse; ++j)
		{
			cout << teacher[i]._CourseName[j]<<"  ";
		}
		cout << endl;
	}
	system("pause");
}

void WriteDateForFile(Teacher* teacher, int nTeacher)		//将数据写入到文件
{
	const char* OUTPUT = "教师排课信息.txt";
	FILE *pOut = fopen(OUTPUT, "w");
	assert(pOut != NULL);

	for (int i = 0; i < nTeacher; ++i)
	{
		fprintf(pOut, "%s:  ", teacher[i]._Name);
		for (int j = 0; j < teacher[i]._nCorse; ++j)
		{
			fprintf(pOut, "%s  ", teacher[i]._CourseName[j]);
		}
		fprintf(pOut,"\n");
	}
}

void DiplayAndWriteDateForFile(Teacher* teacher, int nTeacher)	//显示排课结果并输出到文件
{
	WriteDateForFile(teacher, nTeacher);
	Display(teacher, nTeacher);
}

int MenuSelect()//主界面菜单
{
	char c;//此处用char类型相比int节省3字节空间;
	do {
		system("cls");
		printf("\t\t ╭—————————■□■□—————╮\n");
		printf("\t\t│              教师排课系统            │\n");
		printf("\t\t╰—————■□■□——————————╯\n");
		printf("\t\t┌————————————————————┐\n");
		printf("\t\t│     1.录入教师信息                     │\n");
		printf("\t\t│     2.录入课程信息                     │\n");
		printf("\t\t│     3.排课                             │\n");
		printf("\t\t│     4.显示排课结果并输出到文件         │\n");
		printf("\t\t│     0.退出程序                         │\n");
		printf("\t\t└————————————————————┘\n");
		printf("\t\t请您选择(0-4):");
		fflush(stdin);//清空输入缓冲区，因为getchar是从输入缓冲区获取字符，确保输入缓冲区干净;
		c = getchar();//获取字符;
	} while (c<'0' || c>'4');//确保输入合法;

	return (c - '0');//将数字字符转为对应asscll码值返回;
}

int main()
{
	Teacher teacher[20];
	Course course[30];
	int nTeacher = 0, nCourse = 0;
	while (1)
	{
		switch (MenuSelect())
		{
		case 1:
			AddTeacher(teacher, &nTeacher);
			break;
		case 2:
			AddCourse(course, &nCourse);
			break;
		case 3:
			ArrangCourse(teacher, nTeacher, course, nCourse);	//排课
			break;
		case 4:
			DiplayAndWriteDateForFile(teacher, nTeacher);
			break;
		case 0:
			cout<<"\n谢谢使用，再见!\n";
			system("pause");
			exit(0);
		}
	}
	return 0;
}
