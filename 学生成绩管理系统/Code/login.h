//登录界面头文件
#pragma once
#include"common.h"
#define L_Row 12		//登录菜单行数


//登录界面统筹函数
int Login(void);

//登录主菜单
void LoginMenuUI(void);

//游客登录
void VisterLoginUI(void);

//用户登录界面
void LoginUI(void);
//登录失败提示
void LoginFailUI(void);
//登录成功提示
void LoginSuccessUI(void);

//用户注册界面
void RegisterUI(void);
//注册失败提示
void RegisterFailUI(void);
//注册成功提示
void RegisterSuccessUI(void);

//注册后，将账号密码存储进文件
void SaveUser(USER* user);

//判断用户名与密码是否正确
int IsRight(USER* user);
//判断用户名是否存在（登录需要，注册需要）
int IsUserExist(struct User* user);

//退出系统
void QuitUI(int iRow);