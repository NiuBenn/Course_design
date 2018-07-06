#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct StudentNode  //定义学生
{
	char _num[15];//学号   
	char _name[15]; //姓名
	int _English;//英语成绩
	int _Math;//数学成绩

	struct StudentNode* _Next; //指向下个结点

}StudentNode;

void Load();//学籍管理系统初始化

void LoadDataFromFile();//从文件中加载数据

void WriteDataToFile();//给文件写入数据

int MenuSelect();//主界面功能选择菜单

StudentNode* BuyStudentNode(char* num,char* name,int English,int Math);//创建新节点

void DisplayStuData();//显示数据

void AddDate();//添加学生成绩

StudentNode* QueryStuData();//查询学生成绩,返回该学生信息结点的指针，没找到返回空指针;

int ReviseStuData();//修改成绩，修改成功返回0，失败返回1;

void DeleteStuData();//删除学生成绩信息






