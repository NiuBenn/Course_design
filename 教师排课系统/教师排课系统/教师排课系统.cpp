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
	char _CourseName[5][10];	//��������ѷ��������ʦ�Ŀγ�����
	int _nCorse;	//������¼�ѷ��������ʦ�Ŀγ�

public:

	void SetTeacher(char* Name, char* Num, int WorkLoad)
	{
		strcpy(_Name, Name);
		strcpy(_Num, Num);
		_WorkLoad = WorkLoad;
		_nCorse = 0;
	}

	friend void AddCourseForTeacher(Teacher* teacher, char* CourseName);	//���γ���ӵ���ʦ�Ŀγ�����
};

class Course
{
	char _Name[10];
	char _Num[5];
	int _WeekHour;
	int _SumHour;
	int _Level;

public:
	Course & operator = (const Course course)	//��ֵ���������
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

	friend void SortCourse(Course* course, int nCourse);	//�Կγ̰������ȼ���������

	friend void ArrangCourse(Teacher* teacher, int nTeacher, Course* course, int nCourse);
};

void AddTeacher(Teacher* teacher, int* pnTeacher)
{
	system("cls");
	char Name[10], Num[5];
	int WorkLoad,nTeacher;
	cout<<"����������ѧ�����Ľ�ʦ������";
	cin >> nTeacher;
	for (int i = 0; i < nTeacher; ++i)
	{
		system("cls");
		cout << "�������" << i + 1 << "λ��ʦ����Ϣ" << endl;
		cout << "��������ʦ������:";
		cin >> Name;
		cout << "��������ʦ�Ľ�ʦ��:";
		cin >> Num;
		cout << "��������ʦ�Ĺ�����(�Կγ���ĿΪ��λ):";
		cin >> WorkLoad;

		teacher[i].SetTeacher(Name, Num, WorkLoad);	//���������Ϣ���õ�Teacher������
	}
	*pnTeacher = nTeacher;
	cout << "��ʦ��Ϣ�������ϣ��밴������������˵�����γ���Ϣ����" << endl;
	system("pause");
}

void AddCourse(Course* course, int*  pnCourse)
{
	system("cls");
	char Name[15], Num[5];
	int WeekHour, SumHour, Level, nCourse;
	cout << "�������ܵĿγ���Ŀ��";
	cin >> nCourse;
	for (int i = 0; i < nCourse; ++i)
	{
		system("cls");
		cout << "�������" << i+1 << "���γ̵���Ϣ" << endl;
		cout << "������γ����ƣ�";
		cin >> Name;
		cout << "������γ̺ţ�";
		cin >> Num;
		cout << "�������ܿ�ʱ��";
		cin >> WeekHour;
		cout << "�������ܿ�ʱ��";
		cin >> SumHour;
		cout << "������ÿγ̵����ȼ���";
		cin >> Level;

		course[i].SetCourse(Name, Num, WeekHour, SumHour, Level);

	}

	*pnCourse = nCourse;
	cout << "�γ���Ϣ�Ѿ������ϣ��밴������������˵������ſΣ���" << endl;
	system("pause");
}

void SortCourse(Course* course, int nCourse)	//�Կγ̰������ȼ�����
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

int FindMaxExpect(int* Expect, int nExpect)	//������
{
	int MaxExpect, nMaxExpect = 0;
	MaxExpect = Expect[0];
	for (int i = 0; i < nExpect; ++i)	//�ҵ��������
	{
		if (Expect[i] < MaxExpect)
		{
			MaxExpect = Expect[i];
		}
	}
	for (int i = 0; i < nExpect; ++i)	//ͳ����������ĸ���
	{
		if (Expect[i] == MaxExpect)
		{
			++nMaxExpect;
		}
	}

	int key = rand() % nMaxExpect;	//���ֵȷ���ڼ���maxexpect
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

void AddCourseForTeacher(Teacher* teacher,char* CourseName)	//���γ���ӵ���ʦ�Ŀγ�����
{
	strcpy(teacher->_CourseName[teacher->_nCorse], CourseName);
	teacher->_nCorse++;
}

void ArrangCourse(Teacher* teacher, int nTeacher, Course* course, int nCourse)//�ſ�
{
	int Expect[20];

	SortCourse(course, nCourse);	//�ȶԿγ̰������ȼ���������

	for (int i = 0; i < nCourse; ++i)
	{
		system("cls");
		cout << "��ǰ�Ը�λ��ʦ���ڿγ̣�" << course[i]._Name << "������ֵ����ͳ��" << endl;
		cout << "ע���γ��Ѿ�ѡ������ʦ������ͳ��" << endl;

		for (int j = 0; j < nTeacher; ++j)
		{
			if (teacher[j]._nCorse < teacher[j]._WorkLoad)
			{
				cout << "������ " << teacher[j]._Name << " ��ʦ�Ըÿγ̵�����ֵ��";
				cin >> Expect[j];
			}
			else
			{
				Expect[j] = 500;
			}
		}

		AddCourseForTeacher(&teacher[FindMaxExpect(Expect, nTeacher)], course[i]._Name);//���ÿγ���ӵ���ʦ�Ŀγ�����
	}

	cout << "���пγ��Ѿ�������ɣ������˵����в鿴�ſν������" << endl;
	system("pause");
}

void Display(Teacher* teacher,int nTeacher)
{
	system("cls");
	for (int i = 0; i < nTeacher; ++i)
	{
		cout << teacher[i]._Name << "�� ";
		for (int j = 0; j < teacher[i]._nCorse; ++j)
		{
			cout << teacher[i]._CourseName[j]<<"  ";
		}
		cout << endl;
	}
	system("pause");
}

void WriteDateForFile(Teacher* teacher, int nTeacher)		//������д�뵽�ļ�
{
	const char* OUTPUT = "��ʦ�ſ���Ϣ.txt";
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

void DiplayAndWriteDateForFile(Teacher* teacher, int nTeacher)	//��ʾ�ſν����������ļ�
{
	WriteDateForFile(teacher, nTeacher);
	Display(teacher, nTeacher);
}

int MenuSelect()//������˵�
{
	char c;//�˴���char�������int��ʡ3�ֽڿռ�;
	do {
		system("cls");
		printf("\t\t �q�������������������������������������r\n");
		printf("\t\t��              ��ʦ�ſ�ϵͳ            ��\n");
		printf("\t\t�t���������������������������������������s\n");
		printf("\t\t��������������������������������������������\n");
		printf("\t\t��     1.¼���ʦ��Ϣ                     ��\n");
		printf("\t\t��     2.¼��γ���Ϣ                     ��\n");
		printf("\t\t��     3.�ſ�                             ��\n");
		printf("\t\t��     4.��ʾ�ſν����������ļ�         ��\n");
		printf("\t\t��     0.�˳�����                         ��\n");
		printf("\t\t��������������������������������������������\n");
		printf("\t\t����ѡ��(0-4):");
		fflush(stdin);//������뻺��������Ϊgetchar�Ǵ����뻺������ȡ�ַ���ȷ�����뻺�����ɾ�;
		c = getchar();//��ȡ�ַ�;
	} while (c<'0' || c>'4');//ȷ������Ϸ�;

	return (c - '0');//�������ַ�תΪ��Ӧasscll��ֵ����;
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
			ArrangCourse(teacher, nTeacher, course, nCourse);	//�ſ�
			break;
		case 4:
			DiplayAndWriteDateForFile(teacher, nTeacher);
			break;
		case 0:
			cout<<"\nллʹ�ã��ټ�!\n";
			system("pause");
			exit(0);
		}
	}
	return 0;
}
