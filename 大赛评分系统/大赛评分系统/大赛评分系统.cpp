#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdlib.h>
#include<assert.h>
using namespace std;

class Player
{
private:
	int _Number;//������
	char _Name[10];//����
	int _nScore;//��ί���ֵĸ���
	double _Score[20];//��ί����
	double _MaxScore;//��߷�
	double _MinScore;//��ͷ�
	double _SumScore;//�ۻ���
	double _LastScore;//���÷�//ȥ����߷���ͷֺ��ƽ����


public:
	//Player(int Number,char* Name,double* Score,int nScore)//���캯��
	//{
	//	_Number = Number;
	//	strcpy(_Name, Name);
	//	for (int i = 0; i < nScore; ++i)
	//	{
	//		_Score[i] = Score[i];
	//	}
	//	_nScore = nScore;
	//}

	Player& operator = (const Player& player)//��ֵ���������
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

	void AddPlayerScore(int Number, char* Name, double* Score, int nScore)//������ݵ�player����
	{
		_Number = Number;
		strcpy(_Name, Name);
		for (int i = 0; i < nScore; ++i)
		{
			_Score[i] = Score[i];
		}
		_nScore = nScore;
	}

	double FindSecondMinScore() //�ҵ��ڶ��ͷ�
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

	double FindSecondMaxScore()//�ҵ��ڶ��߷�
	{
		int i = 0;
		int flag = 0;	//����flag����ж��Ƿ�ڸ߷�����߷����
		double SecondMaxScore = _Score[0];
		if (SecondMaxScore == _MaxScore)	//�����һ������������߷�
		{
			SecondMaxScore = _Score[1];		//�ѵڶ����������ڶ��߷�
			flag = 1;		//��flag�ĳ�1������˵��߷��Ѿ����ֹ�һ���ˣ����������������߷���ȵĿ϶����ǵڶ��߷�
		}
	
		for (i = flag + 1; i < _nScore; ++i)//Ȼ���flag+1��ʼ�Ƚϣ�������flagΪ0��1ʱ,�ֱ��ǵڶ��������͵�����������SecondMaxScore�Ƚ�
		{
			if (flag == 0)//flag����0��˵���Ƚϵ����ڻ�û������߷�
			{
				if (_Score[i] > SecondMaxScore && _Score[i] == _MaxScore)//������������߷��˰�flag�ĳ�1
				{
					flag = 1;
				}
				else if (_Score[i] > SecondMaxScore)//���û�е������ǵ�ǰ�ķ����Ƚϴ󣬸���SecondMaxScore��ֵ
				{
					SecondMaxScore = _Score[i];
				}	
			}
			else
			{
				//flagΪ1ʱ�򣬾�����߷��Ѿ����ֹ�һ����;
				if (_Score[i] > SecondMaxScore && _Score[i] == _MaxScore)//�����ǰ��ֵ������߷֣���ô�����ǵڶ��߷�
				{
					SecondMaxScore = _Score[i];//����SecondMaxScoreȻ��break��
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

	friend void CalculateMaxScore(Player* player, int m);//�������ֵnΪ��ί������mΪѡ�ָ���

	friend void CalculateMinScore(Player* player, int m);//������СֵnΪ��ί������mΪѡ�ָ���
	
	friend void CalculateSumAndLastScore(Player* player, int m);//�����ۻ��ֺ����÷֣�nΪ��ί������mΪѡ�ָ���
	
	friend void DisplayPlayerScore(Player* player, int m);//��ӡ����ѡ�ֳɼ�

	friend void WriteDateForFile(Player* player, int nplayer, FILE* pOut1);//д���ļ�f2.txt

	friend void SortDate(Player* player, int nplayer);//����

};

void CalculateMaxScore(Player* player, int m)//�������ֵnΪ��ί������mΪѡ�ָ���
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

void CalculateMinScore(Player* player,  int m)//������СֵnΪ��ί������mΪѡ�ָ���
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

void CalculateSumAndLastScore(Player* player, int m)//�����ۻ��ֺ����÷֣�nΪ��ί������mΪѡ�ָ���
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
	cout << "������ �� ��   ��߷�  ��ͷ�  �ۻ���  ���÷� " << endl;
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
		if (ch == EOF)//�������ļ���βʱ��break,EOFΪ�ļ���β��־
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

void WriteDateForFile(Player* player, int nplayer, FILE* pOut1)//������д�뵽f2.txt
{
	fprintf(pOut1, "������ �� ��     ��߷�         ��ͷ�          �ۻ���         ���÷� \n");
	for (int i = 0; i < nplayer; ++i)
	{
		fprintf(pOut1, "%d      %s\t%lf\t%lf\t%lf\t%lf\n",
			player[i]._Number, player[i]._Name, player[i]._MaxScore,
			player[i]._MinScore, player[i]._SumScore, player[i]._LastScore);
	}
}

void AddDate(Player* player, int* nplayer)//����ѡ�ֳɼ�
{
	system("cls");
	int Number, nScore;
	char Name[10];
	double Score[20];

	cout << "������������ֵ���ί������";
	cin >> nScore;
	while(nScore < 3)
	{
		cout << "�������ֵ���ί���������3�����������룡" << endl;
		cin >> nScore;
	}
	cout << "��������ѡ�ֵĲ�����:";
	cin >> Number;
	cout << "�������ѡ�ֵ�������";
	cin >> Name;
	for (int i = 0; i < nScore; ++i)
	{
		cout << "�������" << i + 1 << "λ��ί�Ը�ѡ�ֵ����֣�";
		cin >> Score[i];
	}
	
	player[*nplayer].AddPlayerScore(Number, Name, Score, nScore);//���µ����ݴ浽player������
	(*nplayer)++;

	cout << "��ѡ�ֳɼ���ӳɹ�" << endl;
	system("pause");
}

void SortDate(Player* player, int nplayer)
{
	Player temp;
	for (int i = 0; i < nplayer - 1; i++)//ð������
	{
		for (int j = 0; j < nplayer - 1 - i; j++)// j��ʼ����0��
		{
			if (player[j]._LastScore == player[j + 1]._LastScore)//���ʱ�жϵڶ��߷�
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

void DisplayTopKAndWritrForFile(Player* player, int nplayer, FILE* pOut2)//������ʾǰk����д���ļ�f3.txt
{
	system("cls");
	int k;
	SortDate(player, nplayer);//����
	cout << "��ǰ��" << nplayer << "��ѡ�ֵĳɼ�" << endl;
	cout << "����Ϊ����ʾǰK��ѡ�ֳɼ�" << endl;
	cout << "������K��ֵ��";
	cin >> k;
	assert(k <= nplayer);//���� kС�ڵ�ǰѡ����������������K���ڵ�ǰѡ������ֱ�ӱ���

	DisplayPlayerScore(player, k);//��ʾǰK���ɼ�
	WriteDateForFile(player, k, pOut2);//��ǰK���ɼ�д�뵽f3.txt;
}

int MenuSelect()//������˵�
{
	char c;//�˴���char�������int��ʡ3�ֽڿռ�;
	do {
		system("cls");
		printf("\t\t �q�������������������������������������r\n");
		printf("\t\t��              ��������ϵͳ            ��\n");
		printf("\t\t�t���������������������������������������s\n");
		printf("\t\t��������������������������������������������\n");
		printf("\t\t��     1.���ļ��ж�ȡ����������ʾ���     ��\n");
		printf("\t\t��     2.��������                         ��\n");
		printf("\t\t��     3.��ǰk���ɼ����                  ��\n");
		printf("\t\t��     0.�˳�����                         ��\n");
		printf("\t\t��������������������������������������������\n");
		printf("\t\t����ѡ��(0-3):");
		fflush(stdin);//������뻺��������Ϊgetchar�Ǵ����뻺������ȡ�ַ���ȷ�����뻺�����ɾ�;
		c = getchar();//��ȡ�ַ�;
	} while (c<'0' || c>'3');//ȷ������Ϸ�;

	return (c - '0');//�������ַ�תΪ��Ӧasscll��ֵ����;
}

int main()
{
	int nplayer = 0;
	Player player[10];
	const char* INPUTA = "f1.txt";//Ҫ�򿪶�ȡ���ļ�
	const char* OUTPUT1 = "f2.txt";
	const char* OUTPUT2 = "f3.txt";

	FILE  *pIn = fopen(INPUTA, "r");//�ö��ķ�ʽ���ļ�
	assert(pIn != NULL);
	FILE *pOut1 = fopen(OUTPUT1, "w");
	assert(pOut1 != NULL);
	FILE *pOut2 = fopen(OUTPUT2, "w");
	assert(pOut2 != NULL);

	LoadDateFromFile(player, pIn, &nplayer);//���ļ��м�������
	CalculateMaxScore(player, nplayer);//������߷�
	CalculateMinScore(player, nplayer);//������ͷ�
	CalculateSumAndLastScore(player, nplayer);//�����ܻ��ֺ����÷�

	while (1)
	{
		switch (MenuSelect())
		{
		case 1:
			CalculateMaxScore(player, nplayer);//������߷�
			CalculateMinScore(player, nplayer);//������ͷ�
			CalculateSumAndLastScore(player, nplayer);//�����ܻ��ֺ����÷�
			DisplayPlayerScore(player, nplayer);//��ʾ
			WriteDateForFile(player, nplayer, pOut1);//д���ļ�
			break;
		case 2:
			AddDate(player, &nplayer);//��������
			break;
		case 3:
			DisplayTopKAndWritrForFile(player, nplayer, pOut2);
			break;

		case 0:
			fclose(pOut1);
			fclose(pOut2);
			fclose(pIn);
			printf("\n\t\tллʹ�ã��ټ�!\n");
			printf("\n\t\t");
			system("pause");
			exit(0);
		}
	}

}