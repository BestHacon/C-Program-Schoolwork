//����ͷ�ļ�
#pragma once		
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>

//���������ļ�
void CreatFiles(void);

//�洢�û��˺�����
typedef struct User
{
	char name[15];		//�˺�
	char key[15];		//����
}USER;
//��ȫ�ֱ�����¼��ǰ��¼���û�
USER g_user;

//���ÿ���̨���λ��
void GoToXY(short iRow, short iColumn);

//����ʱ����
void CountDown(short iRow, short iColumn, int iTime, int iStart);

//ָ��������ʾ���棬�ӵ�iRow�п�ʼ��ӡ
void OrderWrongUI(int iRow);
