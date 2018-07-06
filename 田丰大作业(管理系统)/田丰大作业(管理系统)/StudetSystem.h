#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct StudentNode  //����ѧ��
{
	char _num[15];//ѧ��   
	char _name[15]; //����
	int _English;//Ӣ��ɼ�
	int _Math;//��ѧ�ɼ�

	struct StudentNode* _Next; //ָ���¸����

}StudentNode;

void Load();//ѧ������ϵͳ��ʼ��

void LoadDataFromFile();//���ļ��м�������

void WriteDataToFile();//���ļ�д������

int MenuSelect();//�����湦��ѡ��˵�

StudentNode* BuyStudentNode(char* num,char* name,int English,int Math);//�����½ڵ�

void DisplayStuData();//��ʾ����

void AddDate();//���ѧ���ɼ�

StudentNode* QueryStuData();//��ѯѧ���ɼ�,���ظ�ѧ����Ϣ����ָ�룬û�ҵ����ؿ�ָ��;

int ReviseStuData();//�޸ĳɼ����޸ĳɹ�����0��ʧ�ܷ���1;

void DeleteStuData();//ɾ��ѧ���ɼ���Ϣ






