//登录界面头文件
#pragma once
#include"common.h"
#define L_Row 10		//登录菜单行数


//登录界面统筹函数
int Login(void);

//登录主菜单
void LoginMenuUI(void);

//检查是否存在用户信息
int ChackUser(void);

//写入初始账号密码
void FirstUser(void);

//用户登录界面
void LoginUI(void);
//登录失败提示
void LoginFailUI(void);
//登录成功提示
void LoginSuccessUI(void);

//判断用户名与密码是否正确
int IsRight(USER* user);

//退出系统
void QuitUI(int iRow);