#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdlib.h>
#include<assert.h>
using namespace std;

class Player
{
private:
	int _Number;//参赛号
	char _Name[10];//姓名
	int _nScore;//评委评分的个数
	double _Score[20];//评委评分
	double _MaxScore;//最高分
	double _MinScore;//最低分
	double _SumScore;//累积分
	double _LastScore;//最后得分//去掉最高分最低分后的平均分


public:
	//Player(int Number,char* Name,double* Score,int nScore)//构造函数
	//{
	//	_Number = Number;
	//	strcpy(_Name, Name);
	//	for (int i = 0; i < nScore; ++i)
	//	{
	//		_Score[i] = Score[i];
	//	}
	//	_nScore = nScore;
	//}

	Player& operator = (const Player& player)//复值运算符重载
	{
		if (this != &player)
		{
			_Number = player._Number;
			strcpy(_Name, player._Name);
			_nScore = player._nScore;
			for (int i = 0; i < 10; ++i)
			{
				_Score[i] = player._Score[i];
			}
			_MaxScore = player._MaxScore;
			_MinScore = player._MinScore;
			_SumScore = player._SumScore;
			_LastScore = player._LastScore;
		}

		return *this;
	}

	void AddPlayerScore(int Number, char* Name, double* Score, int nScore)//添加数据到player对象
	{
		_Number = Number;
		strcpy(_Name, Name);
		for (int i = 0; i < nScore; ++i)
		{
			_Score[i] = Score[i];
		}
		_nScore = nScore;
	}

	double FindSecondMinScore() //找到第二低分
	{
		int i = 0;
		int flag = 0;
		double SecondMinScore = _Score[0];
		if (SecondMinScore == _MinScore)
		{
			SecondMinScore = _Score[1];
			flag = 1;
		}
		for (i = flag + 1; i < _nScore; ++i)
		{
			if (flag == 0)
			{
				if (_Score[i] < SecondMinScore && _Score[i] == _MinScore)
				{
					flag = 1;
				}
				else if (_Score[i] < SecondMinScore)
				{
					SecondMinScore = _Score[i];
				}
			}
			else
			{
				if (_Score[i] < SecondMinScore && _Score[i] == _MinScore)
				{
					SecondMinScore = _Score[i];
					break;
				}
				else if (_Score[i] < SecondMinScore)
				{
					SecondMinScore = _Score[i];
				}
			}
		}
		return SecondMinScore;
	}

	double FindSecondMaxScore()//找到第二高分
	{
		int i = 0;
		int flag = 0;	//定义flag标记判断是否第高分与最高分相等
		double SecondMaxScore = _Score[0];
		if (SecondMaxScore == _MaxScore)	//如果第一个分数等于最高分
		{
			SecondMaxScore = _Score[1];		//把第二个分数给第二高分
			flag = 1;		//把flag改成1，就是说最高分已经出现过一次了，后面如果遇到跟最高分相等的肯定就是第二高分
		}
	
		for (i = flag + 1; i < _nScore; ++i)//然后从flag+1开始比较，就是在flag为0或1时,分别是第二个分数和第三个分数跟SecondMaxScore比较
		{
			if (flag == 0)//flag等于0就说明比较到现在还没遇到最高分
			{
				if (_Score[i] > SecondMaxScore && _Score[i] == _MaxScore)//如果这会遇到最高分了把flag改成1
				{
					flag = 1;
				}
				else if (_Score[i] > SecondMaxScore)//如果没有到，但是当前的分数比较大，更新SecondMaxScore的值
				{
					SecondMaxScore = _Score[i];
				}	
			}
			else
			{
				//flag为1时候，就是最高分已经出现过一次了;
				if (_Score[i] > SecondMaxScore && _Score[i] == _MaxScore)//如果当前的值等于最高分，那么他就是第二高分
				{
					SecondMaxScore = _Score[i];//更新SecondMaxScore然后break；
					break;
				}
				else if (_Score[i] > SecondMaxScore)
				{
					SecondMaxScore = _Score[i];
				}
			}
		}
		return SecondMaxScore;
	}

	friend void CalculateMaxScore(Player* player, int m);//计算最大值n为评委个数，m为选手个数

	friend void CalculateMinScore(Player* player, int m);//计算最小值n为评委个数，m为选手个数
	
	friend void CalculateSumAndLastScore(Player* player, int m);//计算累积分和最后得分，n为评委个数，m为选手个数
	
	friend void DisplayPlayerScore(Player* player, int m);//打印所有选手成绩

	friend void WriteDateForFile(Player* player, int nplayer, FILE* pOut1);//写入文件f2.txt

	friend void SortDate(Player* player, int nplayer);//排序

};

void CalculateMaxScore(Player* player, int m)//计算最大值n为评委个数，m为选手个数
{
	for (int j = 0; j < m; ++j)
	{
		double Max = player[j]._Score[0];

		for (int i = 1; i < player[j]._nScore; ++i)
		{
			if (player[j]._Score[i] > Max)
			{
				Max = player[j]._Score[i];
			}
		}

		player[j]._MaxScore = Max;
	}
}

void CalculateMinScore(Player* player,  int m)//计算最小值n为评委个数，m为选手个数
{
	for (int j = 0; j < m; ++j)
	{
		double Min = player[j]._Score[0];

		for (int i = 1; i < player[j]._nScore; ++i)
		{
			if (player[j]._Score[i] < Min)
			{
				Min = player[j]._Score[i];
			}
		}

		player[j]._MinScore = Min;
	}
}

void CalculateSumAndLastScore(Player* player, int m)//计算累积分和最后得分，n为评委个数，m为选手个数
{
	for (int j = 0; j < m; ++j)
	{
		double Sum = 0;

		for (int i = 0; i < player[j]._nScore; ++i)
		{
			Sum += player[j]._Score[i];
		}

		if (player[j]._nScore < 9)
		{
			Sum = Sum - player[j]._MaxScore - player[j]._MinScore;
			player[j]._SumScore = Sum;
			player[j]._LastScore = player[j]._SumScore / (player[j]._nScore - 2);
		}
		else
		{
			Sum = Sum - player[j]._MaxScore - player[j]._MinScore - player[j].FindSecondMaxScore() - player[j].FindSecondMinScore();
			player[j]._SumScore = Sum;
			player[j]._LastScore = player[j]._SumScore / (player[j]._nScore - 4);
		}
		
	}
}

void DisplayPlayerScore(Player* player, int m)
{
	system("cls");
	cout << "参赛号 姓 名   最高分  最低分  累积分  最后得分 " << endl;
	for (int i = 0; i < m; ++i)
	{
		cout << player[i]._Number << "      "
			<< player[i]._Name << "\t"
			<< player[i]._MaxScore << "\t"
			<< player[i]._MinScore << "\t"
			<< player[i]._SumScore << "\t"
			<< player[i]._LastScore << endl;
	}
	system("pause");
}

void LoadDateFromFile(Player* player,FILE* pIn,int* nplayer)
{
	char ch = fgetc(pIn);
	int Number, nScore;
	char Name[10];
	double Score[20];

	while (ch = fgetc(pIn))
	{
		ungetc(ch, pIn);
		fscanf(pIn, "%d%s", &Number, Name);
		ch = fgetc(pIn);
		if (ch == EOF)//当读到文件结尾时候break,EOF为文件结尾标志
		{
			break;
		}
		
		nScore = 0;
		while (ch = fgetc(pIn))
		{
			if (ch == '\n'||ch == EOF)
			{
				break;
			}
			fscanf(pIn, "%lf", &Score[nScore]);
			nScore++;
		}

		player[*nplayer].AddPlayerScore(Number, Name, Score, 7);
		(*nplayer)++;
	}

}

void WriteDateForFile(Player* player, int nplayer, FILE* pOut1)//把数据写入到f2.txt
{
	fprintf(pOut1, "参赛号 姓 名     最高分         最低分          累积分         最后得分 \n");
	for (int i = 0; i < nplayer; ++i)
	{
		fprintf(pOut1, "%d      %s\t%lf\t%lf\t%lf\t%lf\n",
			player[i]._Number, player[i]._Name, player[i]._MaxScore,
			player[i]._MinScore, player[i]._SumScore, player[i]._LastScore);
	}
}

void AddDate(Player* player, int* nplayer)//新增选手成绩
{
	system("cls");
	int Number, nScore;
	char Name[10];
	double Score[20];

	cout << "请输入参与评分的评委个数：";
	cin >> nScore;
	while(nScore < 3)
	{
		cout << "参与评分的评委数必须大于3，请重新输入！" << endl;
		cin >> nScore;
	}
	cout << "请输入新选手的参赛号:";
	cin >> Number;
	cout << "请输入该选手的姓名：";
	cin >> Name;
	for (int i = 0; i < nScore; ++i)
	{
		cout << "请输入第" << i + 1 << "位评委对该选手的评分：";
		cin >> Score[i];
	}
	
	player[*nplayer].AddPlayerScore(Number, Name, Score, nScore);//将新的数据存到player数组中
	(*nplayer)++;

	cout << "新选手成绩添加成功" << endl;
	system("pause");
}

void SortDate(Player* player, int nplayer)
{
	Player temp;
	for (int i = 0; i < nplayer - 1; i++)//冒泡排序
	{
		for (int j = 0; j < nplayer - 1 - i; j++)// j开始等于0，
		{
			if (player[j]._LastScore == player[j + 1]._LastScore)//相等时判断第二高分
			{
				double Score1 = player[j].FindSecondMaxScore();
				double Score2 = player[j + 1].FindSecondMaxScore();

				if (Score1 < Score2)
				{
					temp = player[j];
					player[j] = player[j + 1];
					player[j + 1] = temp;
					break;
				}
			}

			if (player[j]._LastScore < player[j + 1]._LastScore)
			{
				temp = player[j];
				player[j] = player[j + 1];
				player[j + 1] = temp;
			}
			
		}
	}
}

void DisplayTopKAndWritrForFile(Player* player, int nplayer, FILE* pOut2)//排序显示前k名并写到文件f3.txt
{
	system("cls");
	int k;
	SortDate(player, nplayer);//排序
	cout << "当前有" << nplayer << "名选手的成绩" << endl;
	cout << "即将为你显示前K名选手成绩" << endl;
	cout << "请输入K的值：";
	cin >> k;
	assert(k <= nplayer);//断言 k小于当前选手人数，如果输入的K大于当前选手人数直接报错

	DisplayPlayerScore(player, k);//显示前K名成绩
	WriteDateForFile(player, k, pOut2);//将前K名成绩写入到f3.txt;
}

int MenuSelect()//主界面菜单
{
	char c;//此处用char类型相比int节省3字节空间;
	do {
		system("cls");
		printf("\t\t ╭—————————■□■□—————╮\n");
		printf("\t\t│              大赛评分系统            │\n");
		printf("\t\t╰—————■□■□——————————╯\n");
		printf("\t\t┌————————————————————┐\n");
		printf("\t\t│     1.将文件中读取到的数据显示输出     │\n");
		printf("\t\t│     2.新增数据                         │\n");
		printf("\t\t│     3.将前k名成绩输出                  │\n");
		printf("\t\t│     0.退出程序                         │\n");
		printf("\t\t└————————————————————┘\n");
		printf("\t\t请您选择(0-3):");
		fflush(stdin);//清空输入缓冲区，因为getchar是从输入缓冲区获取字符，确保输入缓冲区干净;
		c = getchar();//获取字符;
	} while (c<'0' || c>'3');//确保输入合法;

	return (c - '0');//将数字字符转为对应asscll码值返回;
}

int main()
{
	int nplayer = 0;
	Player player[10];
	const char* INPUTA = "f1.txt";//要打开读取的文件
	const char* OUTPUT1 = "f2.txt";
	const char* OUTPUT2 = "f3.txt";

	FILE  *pIn = fopen(INPUTA, "r");//用读的方式打开文件
	assert(pIn != NULL);
	FILE *pOut1 = fopen(OUTPUT1, "w");
	assert(pOut1 != NULL);
	FILE *pOut2 = fopen(OUTPUT2, "w");
	assert(pOut2 != NULL);

	LoadDateFromFile(player, pIn, &nplayer);//从文件中加载数据
	CalculateMaxScore(player, nplayer);//计算最高分
	CalculateMinScore(player, nplayer);//计算最低分
	CalculateSumAndLastScore(player, nplayer);//计算总积分和最后得分

	while (1)
	{
		switch (MenuSelect())
		{
		case 1:
			CalculateMaxScore(player, nplayer);//计算最高分
			CalculateMinScore(player, nplayer);//计算最低分
			CalculateSumAndLastScore(player, nplayer);//计算总积分和最后得分
			DisplayPlayerScore(player, nplayer);//显示
			WriteDateForFile(player, nplayer, pOut1);//写入文件
			break;
		case 2:
			AddDate(player, &nplayer);//新增数据
			break;
		case 3:
			DisplayTopKAndWritrForFile(player, nplayer, pOut2);
			break;

		case 0:
			fclose(pOut1);
			fclose(pOut2);
			fclose(pIn);
			printf("\n\t\t谢谢使用，再见!\n");
			printf("\n\t\t");
			system("pause");
			exit(0);
		}
	}

}