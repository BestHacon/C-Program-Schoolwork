//公共头文件
#pragma once		
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>

//创建储存文件
void CreatFiles(void);

//存储用户账号密码
typedef struct User
{
	char name[15];		//账号
	char key[15];		//密码
}USER;
//用全局变量记录当前登录的用户
USER g_user;

//设置控制台光标位置
void GoToXY(short iRow, short iColumn);

//倒计时函数
void CountDown(short iRow, short iColumn, int iTime, int iStart);

//指令有误提示界面，从第iRow行开始打印
void OrderWrongUI(int iRow);
