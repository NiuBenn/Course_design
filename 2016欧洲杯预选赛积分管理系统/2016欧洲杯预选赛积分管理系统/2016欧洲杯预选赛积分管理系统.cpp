#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdlib.h>
#include<assert.h>
using namespace std;

class Team
{
	char _TeamName[15];	//����
	int _AllNumber;		//�ܳ���
	int _WinNumber;		//Ӯ����
	int _TieNumber;		//ƽ����
	int _LoseNumber;	//������
	int _GoalBall;		//������
	int _MissedBall;	//ʧ����
	int _Score;			//����

public:
	Team(char* TeamName,int AllNumber = 0,int WinNumber = 0,
		int TieNumber = 0,int LoseNumber = 0,int GoalBall = 0,
		int MissedBall = 0,int Score = 0)//���캯��
	{
		strcpy(_TeamName, TeamName);
		_AllNumber = 0;
		_WinNumber = 0;
		_TieNumber = 0;
		_LoseNumber = 0;
		_GoalBall = 0;
		_MissedBall = 0;
		_Score = 0;
	}

	Team& operator = (const Team& team)//��ֵ���������
	{
		if (this != &team)
		{
			strcpy(_TeamName, team._TeamName);
			_AllNumber = team._AllNumber;
			_WinNumber = team._WinNumber;
			_TieNumber = team._TieNumber;
			_LoseNumber = team._LoseNumber;
			_GoalBall = team._GoalBall;
			_MissedBall = team._MissedBall;
			_Score = team._Score;
		}

		return *this;
	}

	friend void CalculateScore(Team& team1, Team& team2, int Num1, int Num2);//�������

	friend int FindTeam(Team* team, int Num, char * TeamName);	//�ҵ����飬�������������е��±�
	
	friend void TeamSort(Team* team, int num);//�����������

	friend void DisplayTeamScore(Team* team, int num);//��ʾ�������ְ�
	
};

void CalculateScore(Team& team1, Team& team2, int Num1, int Num2)//������֣�num1��num2�ֱ�Ϊ���ӽ�����
{
	team1._AllNumber++;//�����ܳ���++
	team2._AllNumber++;
	team1._GoalBall += Num1;//������+
	team2._GoalBall += Num2;
	team1._MissedBall += Num2;//ʧ����+
	team2._MissedBall += Num1;
	if (Num1 == Num2)//ƽ��
	{
		team1._TieNumber++;//ƽ��++
		team2._TieNumber++;
	}
	else if (Num1 > Num2)//����1ʤ������2��
	{
		team1._WinNumber++;
		team2._LoseNumber++;
	}
	else
	{
		team1._LoseNumber++;//����2��
		team2._WinNumber++;//����1ʤ
	}

	team1._Score = team1._WinNumber * 3 + team1._TieNumber;//������֣�ʤ����*3 + ƽ����*1
	team2._Score = team2._WinNumber * 3 + team2._TieNumber;
}

int FindTeam(Team* team, int Num, char * TeamName)	//�ҵ����飬�������������е��±�
{
	for (int i = 0; i < Num; ++i)
	{
		if (strcmp(TeamName, team[i]._TeamName) == 0)//strcmp�Ƚ������ַ����������ͬ
		{
			return i;
		}
	}
	return -1;
}

void TeamSort(Team* team, int num)//��������
{
	Team temp(team[0]);
	for (int i = 0; i < num - 1; i++)//ð������
	{
		for (int j = 0; j < num - 1; j++)// j��ʼ����0��
		{
			if (team[j]._Score < team[j + 1]._Score)
			{
				temp = team[j];
				team[j] = team[j + 1];
				team[j + 1] = temp;
			}
		}
	}
}

void DisplayTeamScore(Team* team, int num)//��ʾ�������ְ�
{
	TeamSort(team, num);//����
	cout << "��      ʤ      ƽ      ��    ����    ʧ��    ����    ���һ����" << endl;
	cout << "------------------------------------------------------------------" << endl;
	for (int i = 0; i < num; ++i)
	{
		cout << team[i]._AllNumber << "\t" <<
			team[i]._WinNumber << "\t" <<
			team[i]._TieNumber << "\t" <<
			team[i]._LoseNumber << "\t" <<
			team[i]._GoalBall << "\t" <<
			team[i]._MissedBall << "\t" <<
			team[i]._Score << "\t" <<
			team[i]._TeamName << endl;
	}
	system("pause");
}

void AddMatch(Team* team, int Num)//����µı�����Ϣ
{
	system("cls");
	char TeamName1[15];
	char TeamName2[15];
	int score1, score2, TeamIndex1, TeamIndex2;//�ֱ�����ӵĽ��������������е��±�
	cout << "�������һ���Ӷ���:";
	cin >> TeamName1;
	cout << "������ڶ����Ӷ���:";
	cin >> TeamName2;
	cout << "�������һ�ӵĽ�����";
	cin >> score1;
	cout << "������ڶ��ӵĽ�����";
	cin >> score2;

	TeamIndex1 = FindTeam(team, 6, TeamName1);//�ҵ�TeamName1,TeamName2�������е��±�
	TeamIndex2 = FindTeam(team, 6, TeamName2);

	CalculateScore(team[TeamIndex1], team[TeamIndex2], score1, score2);//�������

	cout << "�µı�������ѳɹ����" << endl;
	system("pause");
	//WriteDateForFile();//������������д�뵽�ļ���
}

int MenuSelect()//������˵�
{
	char c;//�˴���char�������int��ʡ3�ֽڿռ�;
	do {
		system("cls");
		printf("\t\t �q���������������������������������������������r\n");
		printf("\t\t��         2016ŷ�ޱ�Ԥѡ�����ֹ���ϵͳ       ��\n");
		printf("\t\t�t���������������������������������������������s\n");
		printf("\t\t   ��������������������������������������������\n");
		printf("\t\t   ��     1.��ʾ���ְ�          2. ��������  ��\n");
		printf("\t\t   ��                                        ��\n");
		printf("\t\t   ��     3.���ж�ȡ����ʾ      0.�˳�ϵͳ   ��\n");
		printf("\t\t   ��������������������������������������������\n");
		printf("\t\t����ѡ��(0-3):");
		fflush(stdin);//������뻺��������Ϊgetchar�Ǵ����뻺������ȡ�ַ���ȷ�����뻺�����ɾ�;
		c = getchar();//��ȡ�ַ�;
	} while (c<'0' || c>'3');//ȷ������Ϸ�;

	return (c - '0');//�������ַ�תΪ��Ӧasscll��ֵ����;
}

void LoadDateFromFile(Team* team, int num, FILE *pIn)//���ļ���ȡ����
{
	char ch = fgetc(pIn);
	char TeamName1[15];
	char TeamName2[15];
	int score1, score2, TeamIndex1, TeamIndex2;//�ֱ����������Ľ��������������е��±�
	while (ch != '\n')//����һ����Ч�������ַ�����
	{
		ch = fgetc(pIn);
	}

	while (ch = fgetc(pIn))
	{
		if (ch == EOF)//�������ļ���βʱ��break,EOFΪ�ļ���β��־
		{
			break;
		}

		fscanf(pIn, "%s%s%d%d", TeamName1, TeamName2, &score1, &score2);//���ж�ȡ��ÿ�ζ�һ��
		TeamIndex1 = FindTeam(team, 6, TeamName1);//ͨ�������ҵ��ö����������е��±�
		TeamIndex2 = FindTeam(team, 6, TeamName2);
		CalculateScore(team[TeamIndex1], team[TeamIndex2], score1, score2);//�������
	}

}

void LoadDateFromFileAndDIsplay(const char* INPUTA)		//���ж�ȡ����ʾ
{
	FILE  *pIn = fopen(INPUTA, "r");//�ö��ķ�ʽ���ļ�
	assert(pIn != NULL);
	char ch = fgetc(pIn);
	Team team[6] = { "����", "�ݿ�","����","������","����ά��","������˹̹" };
	char TeamName1[15];
	char TeamName2[15];
	int score1, score2, TeamIndex1, TeamIndex2;//�ֱ����������Ľ��������������е��±�
	while (ch != '\n')//����һ����Ч�������ַ�����
	{
		ch = fgetc(pIn);
	}

	while (ch = fgetc(pIn))
	{
		if (ch == EOF)//�������ļ���βʱ��break,EOFΪ�ļ���β��־
		{
			break;
		}

		fscanf(pIn, "%s%s%d%d", TeamName1, TeamName2, &score1, &score2);//���ж�ȡ��ÿ�ζ�һ��
		TeamIndex1 = FindTeam(team, 6, TeamName1);//ͨ�������ҵ��ö����������е��±�
		TeamIndex2 = FindTeam(team, 6, TeamName2);
		CalculateScore(team[TeamIndex1], team[TeamIndex2], score1, score2);//�������

		system("cls");	//������Ļ
		cout << "��ǰ����:" << TeamName1 << "  VS  " << TeamName2 << "   " << score1 << ":" << score2 << endl << endl;
		DisplayTeamScore(team, 6);//��ʾ
		
	}
	fclose(pIn);	//�ر��ļ�
}

int main()
{
	Team team[6] = { "����", "�ݿ�","����","������","����ά��","������˹̹" };
	const char* INPUTA = "TeamScore.txt";//Ҫ�򿪶�ȡ���ļ�
	FILE  *pIn = fopen(INPUTA, "r");//�ö��ķ�ʽ���ļ�
	assert(pIn != NULL);

	LoadDateFromFile(team,6,pIn);//���ļ��м�������
	fclose(pIn);

	while (1)
	{
		switch (MenuSelect())
		{
		case 1:
			system("cls");
			DisplayTeamScore(team, 6);
			break;
		case 2:
			AddMatch(team, 6);
			break;
		case 3:
			LoadDateFromFileAndDIsplay(INPUTA);
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