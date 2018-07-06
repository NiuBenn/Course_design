#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdlib.h>
#include<assert.h>
using namespace std;

class Team
{
	char _TeamName[15];	//队名
	int _AllNumber;		//总场数
	int _WinNumber;		//赢场数
	int _TieNumber;		//平局数
	int _LoseNumber;	//负场数
	int _GoalBall;		//进球数
	int _MissedBall;	//失球数
	int _Score;			//积分

public:
	Team(char* TeamName,int AllNumber = 0,int WinNumber = 0,
		int TieNumber = 0,int LoseNumber = 0,int GoalBall = 0,
		int MissedBall = 0,int Score = 0)//构造函数
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

	Team& operator = (const Team& team)//赋值运算符重载
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

	friend void CalculateScore(Team& team1, Team& team2, int Num1, int Num2);//计算积分

	friend int FindTeam(Team* team, int Num, char * TeamName);	//找到队伍，返回它在数组中的下标
	
	friend void TeamSort(Team* team, int num);//队伍积分排序

	friend void DisplayTeamScore(Team* team, int num);//显示比赛积分榜
	
};

void CalculateScore(Team& team1, Team& team2, int Num1, int Num2)//计算积分，num1，num2分别为两队进球数
{
	team1._AllNumber++;//两队总场数++
	team2._AllNumber++;
	team1._GoalBall += Num1;//进球数+
	team2._GoalBall += Num2;
	team1._MissedBall += Num2;//失球数+
	team2._MissedBall += Num1;
	if (Num1 == Num2)//平局
	{
		team1._TieNumber++;//平局++
		team2._TieNumber++;
	}
	else if (Num1 > Num2)//队伍1胜，队伍2负
	{
		team1._WinNumber++;
		team2._LoseNumber++;
	}
	else
	{
		team1._LoseNumber++;//队伍2负
		team2._WinNumber++;//队伍1胜
	}

	team1._Score = team1._WinNumber * 3 + team1._TieNumber;//计算积分：胜场数*3 + 平局数*1
	team2._Score = team2._WinNumber * 3 + team2._TieNumber;
}

int FindTeam(Team* team, int Num, char * TeamName)	//找到队伍，返回他在数组中的下标
{
	for (int i = 0; i < Num; ++i)
	{
		if (strcmp(TeamName, team[i]._TeamName) == 0)//strcmp比较两个字符串，如果相同
		{
			return i;
		}
	}
	return -1;
}

void TeamSort(Team* team, int num)//积分排序
{
	Team temp(team[0]);
	for (int i = 0; i < num - 1; i++)//冒泡排序
	{
		for (int j = 0; j < num - 1; j++)// j开始等于0，
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

void DisplayTeamScore(Team* team, int num)//显示比赛积分榜
{
	TeamSort(team, num);//排序
	cout << "赛      胜      平      负    得球    失球    积分    国家或地区" << endl;
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

void AddMatch(Team* team, int Num)//添加新的比赛信息
{
	system("cls");
	char TeamName1[15];
	char TeamName2[15];
	int score1, score2, TeamIndex1, TeamIndex2;//分别放两队的进球数和在数组中的下标
	cout << "请输入第一个队队名:";
	cin >> TeamName1;
	cout << "请输入第二个队队名:";
	cin >> TeamName2;
	cout << "请输入第一队的进球数";
	cin >> score1;
	cout << "请输入第二队的进球数";
	cin >> score2;

	TeamIndex1 = FindTeam(team, 6, TeamName1);//找到TeamName1,TeamName2在数组中的下标
	TeamIndex2 = FindTeam(team, 6, TeamName2);

	CalculateScore(team[TeamIndex1], team[TeamIndex2], score1, score2);//计算积分

	cout << "新的比赛结果已成功添加" << endl;
	system("pause");
	//WriteDateForFile();//将新增的数据写入到文件中
}

int MenuSelect()//主界面菜单
{
	char c;//此处用char类型相比int节省3字节空间;
	do {
		system("cls");
		printf("\t\t ╭————————■□■□——————————╮\n");
		printf("\t\t│         2016欧洲杯预选赛积分管理系统       │\n");
		printf("\t\t╰—————■□■□—————————————╯\n");
		printf("\t\t   ┌————————————————————┐\n");
		printf("\t\t   │     1.显示积分榜          2. 新增比赛  │\n");
		printf("\t\t   │                                        │\n");
		printf("\t\t   │     3.按行读取并显示      0.退出系统   │\n");
		printf("\t\t   └————————————————————┘\n");
		printf("\t\t请您选择(0-3):");
		fflush(stdin);//清空输入缓冲区，因为getchar是从输入缓冲区获取字符，确保输入缓冲区干净;
		c = getchar();//获取字符;
	} while (c<'0' || c>'3');//确保输入合法;

	return (c - '0');//将数字字符转为对应asscll码值返回;
}

void LoadDateFromFile(Team* team, int num, FILE *pIn)//从文件读取数据
{
	char ch = fgetc(pIn);
	char TeamName1[15];
	char TeamName2[15];
	int score1, score2, TeamIndex1, TeamIndex2;//分别放两个队伍的进球数和在数组中的下标
	while (ch != '\n')//将第一行无效的数据字符读完
	{
		ch = fgetc(pIn);
	}

	while (ch = fgetc(pIn))
	{
		if (ch == EOF)//当读到文件结尾时候break,EOF为文件结尾标志
		{
			break;
		}

		fscanf(pIn, "%s%s%d%d", TeamName1, TeamName2, &score1, &score2);//按行读取，每次读一行
		TeamIndex1 = FindTeam(team, 6, TeamName1);//通过队名找到该队伍在数组中的下标
		TeamIndex2 = FindTeam(team, 6, TeamName2);
		CalculateScore(team[TeamIndex1], team[TeamIndex2], score1, score2);//计算积分
	}

}

void LoadDateFromFileAndDIsplay(const char* INPUTA)		//按行读取并显示
{
	FILE  *pIn = fopen(INPUTA, "r");//用读的方式打开文件
	assert(pIn != NULL);
	char ch = fgetc(pIn);
	Team team[6] = { "冰岛", "捷克","荷兰","土耳其","拉脱维亚","哈萨克斯坦" };
	char TeamName1[15];
	char TeamName2[15];
	int score1, score2, TeamIndex1, TeamIndex2;//分别放两个队伍的进球数和在数组中的下标
	while (ch != '\n')//将第一行无效的数据字符读完
	{
		ch = fgetc(pIn);
	}

	while (ch = fgetc(pIn))
	{
		if (ch == EOF)//当读到文件结尾时候break,EOF为文件结尾标志
		{
			break;
		}

		fscanf(pIn, "%s%s%d%d", TeamName1, TeamName2, &score1, &score2);//按行读取，每次读一行
		TeamIndex1 = FindTeam(team, 6, TeamName1);//通过队名找到该队伍在数组中的下标
		TeamIndex2 = FindTeam(team, 6, TeamName2);
		CalculateScore(team[TeamIndex1], team[TeamIndex2], score1, score2);//计算积分

		system("cls");	//除清屏幕
		cout << "当前比赛:" << TeamName1 << "  VS  " << TeamName2 << "   " << score1 << ":" << score2 << endl << endl;
		DisplayTeamScore(team, 6);//显示
		
	}
	fclose(pIn);	//关闭文件
}

int main()
{
	Team team[6] = { "冰岛", "捷克","荷兰","土耳其","拉脱维亚","哈萨克斯坦" };
	const char* INPUTA = "TeamScore.txt";//要打开读取的文件
	FILE  *pIn = fopen(INPUTA, "r");//用读的方式打开文件
	assert(pIn != NULL);

	LoadDateFromFile(team,6,pIn);//从文件中加载数据
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
			printf("\n\t\t谢谢使用，再见!\n");
			printf("\n\t\t");
			system("pause");
			exit(0);
		}
	}

	return 0;
}