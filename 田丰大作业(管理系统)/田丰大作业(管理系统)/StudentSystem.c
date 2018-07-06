#define _CRT_SECURE_NO_WARNINGS 1//���visual studio��scanf����ȫ����;
#include"StudetSystem.h"

char* filename = "D:/StudentData.dat";//Ҫ��ȡ�Լ�д����ļ�

StudentNode* Student;//����ͷָ��

void Load()//��ʼ��
{
	printf("\n\t\t\t   ѧ����Ϣ����ϵͳ\n\n");
	printf("\t\t\t     �汾�ţ�2.0\n");
	printf("\n\t\t\t    2018��6��18��\n");
	printf("\t\t\t      �����ˣ����\n");
	printf("\t\t\tϵͳ�����У����Ե�.....\n");

	LoadDataFromFile();//���ļ��м�������
	system("pause");//����
}

void LoadDataFromFile()//���ļ���������
{
	FILE *fp;//Fileָ��fp���ں����ļ�����
	StudentNode* NowStudent;//��ǰ���в����Ľ��ָ��
	int count = 0;//����ͳ�ƶ�ȡ���������д���

	if ( NULL ==(fp = fopen(filename, "r")))//����ļ���ʧ�ܣ������ڣ�
	{
		//�����ļ���return�˳��˲㺯��ջ��
		fp = fopen(filename, "a");
		fclose(fp);
		return;
	}

	Student = BuyStudentNode("","",0,0);//�Կ�num,��name������㣬
	NowStudent = Student;//���մ����Ľ��ָ�����ǰ���в����Ľ��ָ��
	while (!feof(fp))//whileѭ��,ֱ���ļ���βEOF
	{
		//���ļ���ȡStudentNode��С���ݸ���ǰ���в����Ľ��
		fread(NowStudent, sizeof(StudentNode), 1, fp);
		NowStudent->_Next = BuyStudentNode("", "", 0, 0);//�����½ڵ����ڵ�ǰ�ڵ��
		NowStudent = NowStudent->_Next;//��ǰ���ָ��ָ������ڵ�
		count++;//count++
	}

	//������ļ���ȡ��������Ϊ��ǰ����㣬�ᵼ�¶࿪����("", "", 0, 0)���
	//���Ժ������ɾ���࿪���
	NowStudent = Student;//����ͷָ�����ǰ���в����Ľ��ָ��
	while (strcmp(NowStudent->_Next->_num, ""))//whileѭ���ҵ�->_Nextѧ��Ϊ""�Ľ��
	{
		NowStudent = NowStudent->_Next;
	}

	free(NowStudent->_Next->_Next); //free���࿪��������� 
	NowStudent->_Next->_Next = NULL;
	free(NowStudent->_Next);
	NowStudent->_Next = NULL;

	if (count == 1)//countΪ1ʱ��ʾδ������Ч���ݣ�Ҳ����ͷ����Ƕ࿪����Ч���ݽ��
	{
		free(Student);//free��ͷ��ָ���ÿ�
		Student = NULL;
	}
	fclose(fp);//�ر��ļ�
}

void WriteDataToFile()
{
	FILE* fp;//FILEָ��
	StudentNode* tmp = Student;//tmpָ��ָ��ͷ

	if ((fp = fopen(filename, "w")) == NULL)//��wֻд��ʽ�򿪣�ʧ��return
	{
		printf("cannot open the files\n");
		system("pause");//����
		return;
	}

	while (tmp)//��ͷ�ڵ����ν������ڵ�д���ļ�
	{
		if (fwrite(tmp, sizeof(StudentNode), 1, fp) != 1)//ÿ��дStudentNode��С
			printf("file write error\n");
		tmp = tmp->_Next;//д�굱ǰ��㣬ָ��ָ��������
	}

	fclose(fp);//�ر��ļ�
}

int MenuSelect()//������˵�
{
	char c;//�˴���char�������int��ʡ3�ֽڿռ�;
	do {
		system("cls");
		printf("\t\t �q���������������������������������r\n");
		printf("\t\t��         ѧ���ɼ�����ϵͳ         ��\n");
		printf("\t\t�t�����������������������������������s\n");
		printf("\t\t   ��������������������������������\n");
		printf("\t\t   �� 1. ��ʾ�ɼ�    2. �����ɼ� ��\n");
		printf("\t\t   ��                            ��\n");
		printf("\t\t   �� 3. �ɼ���ѯ    4. �ɼ��޸� ��\n");
		printf("\t\t   ��                            ��\n");
		printf("\t\t   �� 5. ɾ���ɼ�    0.�˳�����  ��\n");
		printf("\t\t   ��������������������������������\n");
		printf("\t\t����ѡ��(0-5):");
		fflush(stdin);//������뻺��������Ϊgetchar�Ǵ����뻺������ȡ�ַ���ȷ�����뻺�����ɾ�;
		c = getchar();//��ȡ�ַ�;
	} while (c<'0' || c>'5');//ȷ������Ϸ�;

	return (c - '0');//�������ַ�תΪ��Ӧasscll��ֵ����;
}

StudentNode* BuyStudentNode(char* num, char* name, int English, int Math)//����ѧ�����
{
	StudentNode* tmp = (StudentNode*)malloc(sizeof(StudentNode));//malloc����ռ俪�ٽڵ�

	if (tmp != NULL)//�жϽ���Ƿ񿪱ٳɹ�
	{
		strcpy(tmp->_num, num);//��num�ַ����������¿����tmp��_num;
		strcpy(tmp->_name, name);//��name�ַ����������¿����tmp��_name;
		tmp->_English = English;
		tmp->_Math = Math;
		tmp->_Next = NULL;//English��math��ֵ�󷵻�tmpָ�룻

		return tmp;
	}

	printf("��㴴��ʧ�ܣ���");
	return NULL;//���mallocʧ�ܣ����ؿ�ָ��
}

void DisplayStuData()//��ʾ�ɼ�����
{
	StudentNode* tmp = Student;//tmpָ��ָ��ͷ���
	system("cls");//�����Ļ

	if (tmp == NULL)//ͷ���Ϊ��,������Ч���ݣ�return�˳��˲㺯��ջ��
	{
		printf("��ǰ��ѧ����سɼ�����,��������ݺ����ԣ���\n");
		system("pause");//����
		return;
	}

	printf("ѧ��\t     ����\t Ӣ��ɼ�   ��ѧ�ɼ�\n");

	while (tmp)//���δ�ӡ�����ڵ�����
	{
		printf("%s  %s  \t    %d \t    %d\n", tmp->_num, tmp->_name, tmp->_English, tmp->_Math);
		tmp = tmp->_Next;//ָ��������
	}

	system("pause");//����
}

void AddDate()
{
	char flag = 'y';//flag�����ж��Ƿ���Ҫ�������
	char num[15], name[15];
	int English, Math;
	StudentNode** ppHead = &Student;//ppHead����ָ��ָ��ͷ���ָ�����ڴ���ͷ���Ϊ�յ����
	StudentNode* tmp = *ppHead;//tmpָ��ָ��ͷ���
	StudentNode* newNode;//newNodeָ�����ڷ��¿����ĵ�ַ
	system("cls");//�����Ļ

	while (flag != 'n' && flag != 'N')//����β����N��nʱ�����������
	{
		printf("\t\t\t ----ѧ����¼���----\n");
		printf("��������Ҫ��ӵ�ѧ��ѧ�ţ�");
		scanf("%s", num);
		printf("��������Ҫ��ӵ�ѧ��������");
		scanf("%s", name);
		printf("��������Ҫ��ӵ�ѧ��Ӣ��ɼ���");
		scanf("%d", &English);
		printf("��������Ҫ��ӵ�ѧ����ѧ�ɼ���");
		scanf("%d", &Math);
		
		newNode = BuyStudentNode(num, name, English, Math);//����������ݿ����µĽڵ�
		
		if (NULL == *ppHead)//��ͷ���Ϊ�յ����,���¿����ֱ�Ӹ�ͷ��ͬʱ��tmp����ָ��ͷ���
		{
			*ppHead = newNode;
			(*ppHead)->_Next = NULL;
			tmp = *ppHead;
		}
		else
		{
			while (tmp->_Next)//��tmp����β�ڵ㣬�����µĽ��
			{
				tmp = tmp->_Next;
			}
			tmp->_Next = newNode;
			newNode->_Next = NULL;
		}
		
		printf("�Ƿ�������?(y/n)");
		scanf("\t%c", &flag);
		system("cls");
	}

	WriteDataToFile();//���������ݸĶ�д�뵽�ļ�
}

StudentNode* QueryStuData()//��������,�����ҵ�����ָ�룬û�ҵ����ؿ�
{
	StudentNode* tmp = Student;//tmpָ��ָ��ͷ���
	char num[15];
	system("cls");

	if (tmp == NULL)//��ͷΪ��
	{
		printf("��ǰ��ѧ����سɼ�����,��������ݺ����ԣ���\n");
		system("pause");
		return NULL;
	}

	printf("������������ѧ����ѧ�ţ�");
	scanf("%s", num);

	//��strcmp�Ƚ�num�ַ���ֱ���ҵ��������ݣ�������������ȫ���������ѭ��
	while ( tmp != NULL && strcmp(tmp->_num, num))
	{
		tmp = tmp->_Next;
	}

	if (tmp == NULL)//û�ҵ�ʱ���ؿ�ָ��
	{
		printf("δ��ѯ����ѧ����سɼ���Ϣ��");
		system("pause");
		return NULL;
	}
	else//�ҵ���������ݵ���Ļ
	{
		printf("ѧ��:%s\n����:%s\n1.Ӣ��ɼ�:%d\n2.��ѧ�ɼ�:%d\n",tmp->_num,tmp->_name,tmp->_English,tmp->_Math);
		system("pause");
		return tmp;//����tmpָ������������ֵ
	}
}

int ReviseStuData()//�޸�����
{
	StudentNode* Query = QueryStuData();//����QueryStuData������Ҫ�޸ĵĽ��
	char c;
	if (NULL == Query)
	{
		printf("ѧ���ɼ��޸�ʧ�ܣ�");
		system("pause");
		return 1;
	}
	
	printf("��������Ҫ�޸ĳɼ��Ŀ�Ŀ(1��2)��");
	do {
		fflush(stdin);//������뻺��������Ϊgetchar�Ǵ����뻺������ȡ�ַ���ȷ�����뻺�����ɾ�;
		c = getchar();//��ȡ�ַ�;
	} while (c<'1' || c>'2');//ȷ������Ϸ�;
	printf("������ÿ�Ŀ�µĳɼ���");

	switch (c)
	{
	case '1':
		scanf("%d", &(Query->_English));
		break;
	case '2':
		scanf("%d", &(Query->_Math));
		break;
	}

	WriteDataToFile();//���������ݸĶ�д�뵽�ļ�

	printf("�ɼ��޸ĳɹ���");
	system("pause");
	return 0;
}

void DeleteStuData()
{
	StudentNode* Delete,* tmp;
	tmp = Student;//tmpָ��ͷ���
	system("cls");

	if (NULL == tmp)//��ͷΪ��ʱ��return
	{
		printf("��ǰ��ѧ����سɼ�����,��������ݺ����ԣ���\n");
		system("pause");
		return;
	}

	Delete = QueryStuData();//��QueryStuData������Ҫɾ���Ľ��
	if (NULL == Delete)//û�ҵ�ʱreturn
	{
		printf("��˶����޸�ѧ����Ϣ�����ԣ�");
		system("pause");
		return;
	}
	else
	{
		if (Delete == tmp)//��Ҫɾ����Ϊͷ���ʱ����Studentָ�������㣬freeͷ���
		{
			Student = Student->_Next;
			free(tmp);
			tmp = NULL;
		}
		else
		{
			while (tmp->_Next != Delete)//whileѭ��ֱ��tmp��nextΪҪɾ���Ľ��
			{
				tmp = tmp->_Next;
			}
			tmp->_Next = tmp->_Next->_Next;//tmp��nextָ��ָ�����ĺ���
			free(Delete);//free��Ҫɾ���Ľ��
			Delete = NULL;
		}
	}

	WriteDataToFile();//���������ݸĶ�д�뵽�ļ�

	printf("ɾ���ɹ���");
	system("pause");
}

