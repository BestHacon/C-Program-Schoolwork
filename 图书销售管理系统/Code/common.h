//����ͷ�ļ�
#pragma once	
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<tchar.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>

//���������ļ�
void CreatFiles(void);

//�洢�û��˺�����
typedef struct User
{
	char name[30];		//�˺�
	char key[30];		//����
	int mark;
}USER;
//��ȫ�ֱ�����¼��ǰ��¼���û�
USER g_user;

//���ÿ���̨���λ��
void GoToXY(short iRow, short iColumn);

//����ʱ����
void CountDown(short iRow, short iColumn, int iTime, int iStart);

//�ַ�������
void Encryption(char* secret);

//ָ��������ʾ���棬�ӵ�iRow�п�ʼ��ӡ
void OrderWrongUI(int iRow);
