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
	int _WorkTimeIn;		//������
	int _WorkTimeNotIn;		//���ڲ���
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

	Workers& operator = (const Workers& workers)	//��ֵ���������
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
		cout << "Ա���ţ�" << _ID << endl;
		cout << "������" << _Name << endl;
		cout << "ְλ��";
		switch (_Job)
		{
		case 1:
			cout << "����" << endl;
			break;
		case 2:
			cout << "��ְ������Ա" << endl;
			break;
		case 3:
			cout << "���۾���" << endl;
			break;
		case 4:
			cout << "��ְ������Ա" << endl;
			break;
		}
		system("pause");
	}

	friend void DisplayWorkers(Workers* workers, int nWorkers);	//��ʾԱ��������Ϣ
	
	friend int SearchWorkers(Workers* workers, int nWorkers);	//����Ա����Ϣ
	
	friend void Revise(Workers* workers, int nWorkers);		//�޸�

	friend void AddAttendance(Workers* workers, int nWorkers);	//���ӿ���

	friend int SearchAttendance(Workers* workers, int nWorkers);	//��ѯ����

	friend void ReviseAttendance(Workers* workers, int nWorkers);	//�޸Ŀ���

	friend void DeleteAttendance(Workers* workers, int nWorkers);	//ɾ������

	friend void DisplayAttendance(Workers* workers, int nWorkers);	//��ʾ������Ϣ

	friend void AddMoveInformation(Workers* workers, int nWorkers, Move* move, int* nMove);

	friend void DisplayMoveInformation(Move* move, int nMove);

	friend void WriteDateForFileWorkers(Workers* workers, int nWorkers);

};

void printfJob(int job)
{
	if (job == 1)
	{
		cout << "����    " ;
	}
	else if (job == 2)
	{
		cout << "��ְ������Ա     ";
	}
	else if (job == 3)
	{
		cout << "���۾���     ";
	}
	else if (job == 4)
	{
		cout << "��ְ����Ա     ";
	}
}

//void DisplayOrReviseMoney(int* FinalMoney, int* OneTimeMoney)	//�鿴�����޸Ĺ���
//{
//	char flag = 'n';
//	system("cls");
//	cout << "��ǰ�����¹̶�����Ϊ��" << *FinalMoney << "(Ԫ)" << endl;
//	cout << "��ǰ��ְ��Աÿ��(8Сʱ)����Ϊ��" << *OneTimeMoney << "(Ԫ)" << endl;
//	cout << "�Ƿ��޸ģ���<y/n>:";
//	cin >> flag;
//	if (flag != 'y'&&flag != 'Y')
//	{
//		system("pause");
//		return;
//	}
//	else
//	{
//		cout << "�������趨�����¹̶����ʣ�";
//		cin >> *FinalMoney;
//		cout << "�������趨��ְ��Աÿ��(8Сʱ)����";
//		cin >> *OneTimeMoney;
//		cout << "�޸ĳɹ�����" << endl;
//		system("pause");
//	}
//}

void AddWorkers(Workers* workers, int* nWorkers, int* nID, int FinalMoney,int OneTimeMoney)		//���Ա����Ϣ
{
	system("cls");
	char flag = 'y';
	char Name[15];
	int Job;

	while (flag != 'n' && flag != 'N')//����β����N��nʱ�����������
	{
		cout << "Ա������ϵͳ�Զ����ɣ�����" << endl;
		cout << "��������Ҫ��ӵ�Ա������:";
		cin >> Name;
		cout << "�������Ա����ְλ\n(����:1 ��ְ������Ա:2 ���۾���:3 ��ְ����Ա:4):";
		cin >> Job;

		workers[*nWorkers].SetWorkers(*nID + 1, Name, Job, OneTimeMoney ,FinalMoney);
		(*nWorkers)++;
		(*nID)++;

		cout << "�Ƿ�������?(y/n):" ;
		cin >> flag;
		system("cls");
	}
	WriteDateForFileWorkers(workers, *nWorkers);
}

void DisplayWorkers(Workers* workers, int nWorkers)		//��ʾԱ����Ϣ
{
	system("cls");

	cout << "Ա����   ����   ְλ" << endl;
	for (int i = 0; i < nWorkers; ++i)
	{
		cout << workers[i]._ID << "     " << workers[i]._Name << "    ";
		printfJob(workers[i]._Job);
		cout << endl;
	}
	system("pause");
}

int SearchWorkers(Workers* workers, int nWorkers)	//����Ա����Ϣ
{
	int Index = 0;
	int ID;
	char Name[10];
	char c;
	do {
		system("cls");
		cout << "��ѡ��" << endl;
		cout << "1.����Ա����" << endl;
		cout << "2.����Ա������" << endl;
		fflush(stdin);
		c = getchar();
	} while (c > '2' || c < '1');

	switch (c)
	{
	case '1':
		system("cls");
		{
			cout << "����������Ҫ��Ա���ţ�";
			cin >> ID;
			for (; Index < nWorkers; ++Index)
			{
				if (workers[Index]._ID == ID)
				{
					workers[Index].printer();
					return Index;
				}
			}
			cout << "δ�ҵ���Ա���������Ϣ����" << endl;
			system("pause");
			return -1;
		}

	case '2':
		system("cls");
		{
			cout << "����������Ҫ��Ա��������";
			cin >> Name;

			for (; Index < nWorkers; ++Index)
			{
				if (strcmp(Name, workers[Index]._Name) == 0)
				{
					workers[Index].printer();
					return Index;
				}
			}
			cout << "δ�ҵ���Ա���������Ϣ����" << endl;
			system("pause");
			return -1;
		}
	}

}

void Revise(Workers* workers, int nWorkers)	//�޸�Ա����Ϣ
{
	int Index = SearchWorkers(workers, nWorkers);
	if (Index == -1)
	{
		return;
	}

	char Name[15];
	int Job;
	cout << "Ա������ϵͳ���ɣ��޷��޸ģ�";
	cout << "�������޸ĺ��������";
	cin >> Name;
	cout << "�������޸ĺ��ְλ\n(����:1 ��ְ������Ա:2 ���۾���:3 ��ְ����Ա:4):";
	cin >> Job;

	workers[Index].SetWorkers(workers[Index]._ID, Name, Job, workers[Index]._OneTimeMoney,
		workers[Index]._FinalMoney, workers[Index]._WorkTimeIn,workers[Index]._WorkTimeNotIn);
	
	WriteDateForFileWorkers(workers, nWorkers);
	cout << "��Ϣ�޸ĳɹ���" << endl;
	system("pause");

}

void Delete(Workers* workers, int* nWorkers)		//ɾ��Ա����Ϣ
{
	int Index = SearchWorkers(workers, *nWorkers);
	if (Index == -1)
	{
		return;
	}
	char c;
	cout << "�Ƿ�ɾ������<y/n>��";
	cin >> c;
	if (c == 'n' || c == 'N')
	{
		cout << "ɾ����ȡ������" << endl;
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
		cout << "ɾ���ɹ���" << endl;
		system("pause");
	}
}

void AddAttendance(Workers* workers, int nWorkers)
{
	system("cls");
	char flag;
	cout << "\t\t\tԱ������" << endl;
	for (int i = 0; i < nWorkers; ++i)
	{
		cout << "��ǰ��" << workers[i]._ID << " �� " << workers[i]._Name << " ���п���" << endl;
		cout << "�Ƿ�ȱ�ڣ���<y/n>:";
		
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
	cout << "�������!!" << endl;
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
		cout << "���ڴ���Ϊ��" << workers[Index]._WorkTimeIn << endl;
		cout << "ȱ�ڴ���Ϊ��" << workers[Index]._WorkTimeNotIn << endl;
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
	
		cout << "�������޸ĺ�ĵ��ڴ�����";
		cin >> workers[Index]._WorkTimeIn;
		cout << "�������޸ĺ��ȱ�ڴ�����";
		cin >> workers[Index]._WorkTimeNotIn;

		WriteDateForFileWorkers(workers, nWorkers);
		cout << "������Ϣ�޸���ϣ���" << endl;
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
		cout << "�Ƿ�ɾ�����˵Ŀ�����Ϣ(�˲����Ὣ���ڣ�ȱ�ڴ���ȫ����0)<y/n>:";
		cin >> flag;
		if (flag == 'n' || flag == 'N')
		{
			cout << "ɾ����ȡ������" << endl;
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
	cout << "������Ϣɾ���ɹ�����" << endl;
	system("pause");
}

void DisplayAttendance(Workers* workers, int nWorkers)
{
	system("cls");
	cout << "Ա����   ����   ְλ   ����   ȱ��" << endl;
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
	cout << "������������ְλ\n(����:1 ��ְ������Ա:2 ���۾���:3 ��ְ����Ա:4):";
	cin >> NowJob;

	move[*nMove].SetMove(workers[Index]._ID, workers[Index]._Name, workers[Index]._Job, NowJob);
	(*nMove)++;
	workers[Index].SetWorkers(workers[Index]._ID, workers[Index]._Name, NowJob,workers[Index]._OneTimeMoney,
		workers[Index]._FinalMoney, workers[Index]._WorkTimeIn, workers[Index]._WorkTimeNotIn);

	WriteDateForFileMoveInformation(move, *nMove);
	cout << "��������ɣ���" << endl;
	system("pause");
}

void DisplayMoveInformation(Move* move, int nMove)
{
	if (nMove == 0)
	{
		cout << "�������Ϣ����\n";
		system("pause");
		return;
	}
	system("cls");
	cout << "���  Ա�����   ����   ����ǰְλ  ������ְλ" << endl;
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
		cout << "�������Ϣ����\n";
		system("pause");
		return;
	}
	DisplayMoveInformation(move, *nMove);
	cout << "��������Ҫɾ���ĵ�����Ϣ��ţ�";
	cin >> Index;
	assert(Index <= *nMove );

	for (int i = Index - 1; i < *nMove - 1; ++i)
	{
		move[i] = move[i + 1];
	}
	(*nMove)--;

	WriteDateForFileMoveInformation(move, *nMove);
	cout << "ɾ���ɹ���!" << endl;
	system("pause");
}

void LoadDateFromFile(Workers* workers, int* nWorkers, Move* move, int* nMove ,int* nID)
{
	FILE *fp1, *fp2;
	if (NULL == (fp1 = fopen("Workers.txt", "r")))//����ļ���ʧ�ܣ������ڣ�
	{
		//�����ļ�����������
		fp1 = fopen("Workers.txt", "a");
		fclose(fp1);
		cout << "��һ��ʹ��ϵͳ����Ϊ�������ļ�������ݣ�" << endl;
		cout << "����¼�벿��Ա����Ϣ��������ļ����ݳ�ʼ������" << endl;
		system("pause");
		AddWorkers(workers, nWorkers, nID, 6000, 150);
	}
	else
	{
		char Name[15];
		int ID, Job, WorkTimeIn, WorkTimeNotIn, OneTimeMoney, FinalMoney;
		char ch = fgetc(fp1);

		while (ch != '\n')//����һ����Ч�������ַ�����
		{
			ch = fgetc(fp1);
		}

		while (ch = fgetc(fp1))
		{
			if (ch == EOF)//�������ļ���βʱ��break,EOFΪ�ļ���β��־
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

	if (NULL == (fp2 = fopen("MoveInformation.txt", "r")))//����ļ���ʧ�ܣ������ڣ�
	{
		fp1 = fopen("MoveInformation.txt", "a");
		return;
	}
	else
	{
		char Name[15];
		int ID, LastJob, NowJob;
		char ch = fgetc(fp2);

		while (ch != '\n')//����һ����Ч�������ַ�����
		{
			ch = fgetc(fp2);
		}

		while (ch = fgetc(fp2))
		{
			if (ch == EOF)//�������ļ���βʱ��break,EOFΪ�ļ���β��־
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
	fprintf(fp, "Ա����   ����    ְλ   ����   ȱ��   �칤��   �¹���\n\n");
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
	fprintf(fp, "Ա����   ����   ����ǰְλ  ������ְλ\n\n");
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
		cout << "\t\t �q�����������������������������������������������r\n";
		cout << "\t\t��                ��˾Ա������ϵͳ              ��\n";
		cout << "\t\t�t�����������������������������������������������s\n";
		cout << "\t\t   ����������������������������������������������\n";
		cout << "\t\t   ��           1. Ա��������Ϣ����            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           2. Ա��������Ϣ����            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           3. Ա��������Ϣ����            ��\n";
		/*cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           4. �鿴�����þ���̶��¹���    ��\n";
		cout << "\t\t   ��              ����ְԱ��ÿ��(8Сʱ)����   ��\n";*/
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           0. �˳�ϵͳ                    ��\n";
		cout << "\t\t   ����������������������������������������������\n";
		cout << "\t\t����ѡ��(0-4):";
		cin >> i;
	} while (i < 0 || i>3);//ȷ������Ϸ�;

	return i;
}

int menu_select1()
{
	int i;
	do {
		system("cls");
		cout << "\t\t �q�����������������������������������������������r\n";
		cout << "\t\t��                 Ա��������Ϣ����             ��\n";
		cout << "\t\t�t�����������������������������������������������s\n";
		cout << "\t\t   ����������������������������������������������\n";
		cout << "\t\t   ��           1. ���Ա��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           2. �޸�Ա��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           3. ��ѯԱ��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           4. ɾ��Ա��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           5. ��ʾԱ��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           0. ������һ�˵�                ��\n";
		cout << "\t\t   ����������������������������������������������\n";
		cout << "\t\t����ѡ��(0-5):";
		cin >> i;
	} while (i < 0 || i>5);//ȷ������Ϸ�;

	return i;
}

int menu_select2()
{
	int i;
	do {
		system("cls");
		cout << "\t\t �q�����������������������������������������������r\n";
		cout << "\t\t��                 Ա��������Ϣ����             ��\n";
		cout << "\t\t�t�����������������������������������������������s\n";
		cout << "\t\t   ����������������������������������������������\n";
		cout << "\t\t   ��           1. ���Ա��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           2. �޸�Ա��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           3. ��ѯԱ��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           4. ɾ��Ա��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           5. ��ʾԱ��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           0. ������һ�˵�                ��\n";
		cout << "\t\t   ����������������������������������������������\n";
		cout << "\t\t����ѡ��(0-5):";
		cin >> i;
	} while (i < 0 || i>5);//ȷ������Ϸ�;

	return i;
}

int menu_select3()
{
	int i;
	do {
		system("cls");
		cout << "\t\t �q�����������������������������������������������r\n";
		cout << "\t\t��                 Ա��������Ϣ����             ��\n";
		cout << "\t\t�t�����������������������������������������������s\n";
		cout << "\t\t   ����������������������������������������������\n";
		cout << "\t\t   ��           1. ���Ա��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           2. �鿴Ա��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           3. ɾ��Ա��������Ϣ            ��\n";
		cout << "\t\t   ��                                          ��\n";
		cout << "\t\t   ��           0. ������һ�˵�                ��\n";
		cout << "\t\t   ����������������������������������������������\n";
		cout << "\t\t����ѡ��(0-3):";
		cin >> i;
	} while (i < 0 || i>3);//ȷ������Ϸ�;

	return i;
}

int main()
{
	Workers workers[15];
	Move move[15];
	int FinalMoney = 6000;	//�¹̶�����
	int OneTimeMoney = 150;	//��ְԱ��һ��(8��Сʱ)�Ĺ���
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
			cout << "\n\t\tллʹ�ã��ټ�!\n";
			system("pause");
			exit(0);

		}
	}

	return 0;
}