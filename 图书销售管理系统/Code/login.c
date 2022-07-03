#include"login.h"

//登录界面统筹函数
int Login(void)
{
	LoginMenuUI();					//输出主菜单
	//检查是否存在用户信息
	if (!ChackUser())
	{
		FirstUser();
	}
	while (1)
	{
		int iOrder = -1;				//用户指令
		GoToXY(L_Row - 1, 69);			//设置光标输入点
		scanf("%d", &iOrder);
		switch (iOrder)
		{
		case 0:		//0.退出系统
			LoginMenuUI();
			QuitUI(L_Row + 1);
			return 0;
			break;
		case 1:		//1.用户登录
			LoginUI();
			GoToXY(L_Row + 1, 63);		//跳到登录名后面准备输入登录名
			scanf("%s", g_user.name);
			GoToXY(L_Row+1+1, 63);
			scanf("%s", g_user.key);
			Encryption(g_user.key);		//加密密码
			if (IsRight(&g_user))		//判断账号密码是否正确
			{
				LoginSuccessUI();		//登陆成功
				return 1;
			}
			else
			{
				LoginFailUI();
				GoToXY(L_Row-1, 70);
				putchar(' ');			//盖住原来字符
			}
			GoToXY(L_Row - 1, 70);
			break;
		default:		//输入指令错误，清空缓冲区
		{
			char c = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			LoginMenuUI();
			OrderWrongUI(L_Row+1);
		}
		}
	}
	return 0;
}

//登录菜单
void LoginMenuUI(void)
{
	system("cls");		//清空控制台，重新输入菜单
	//第二行输出
	GoToXY(2, 0);

	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*             欢迎使用本系统            *\n");
	printf("\t\t\t\t\t*      (相关操作请直接输入对应指令)     *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t* |            0: 退出系统            | *\n");
	printf("\t\t\t\t\t* |            1: 用户登录            | *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*           请输入指令(0/1):            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//检查是否存在用户信息
int ChackUser(void)
{
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("User.dat", "rb")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open User.dat!");
		return 0;
	}
	//检查是否到达文件末尾
	fgetc(pFile);
	if (feof(pFile))
	{
		return 0;
	}
	else
	{
		return 1;
	}
	fclose(pFile);
}

//写入初始账号密码
void FirstUser(void)
{
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("User.dat", "ab")) == NULL)
	{
		printf("Failure to open User.dat\n");
		return;
	}
	USER firstuser = { .name = "admin",.key = "123456",.mark = 1 };
	Encryption(firstuser.key);
	//写入文件
	fwrite(&firstuser, sizeof(USER), 1, pFile);
	//关闭文件
	fclose(pFile);
}

//用户登录界面
void LoginUI(void)
{
	LoginMenuUI();
	GoToXY(L_Row+1, 0);		//第10行位置开始输出
	printf("\t\t\t\t\t*           登录账号 :                  *\n");
	printf("\t\t\t\t\t*           登录密码 :                  *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//登录失败提示
void LoginFailUI(void)
{
	GoToXY(L_Row+3+1, 0);
	printf("\t\t\t\t\t*      登录失败，请重新输入指令!!!      *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//登录成功提示
void LoginSuccessUI(void)
{
	GoToXY(L_Row+3+1, 0);
	printf("\t\t\t\t\t*         登录成功，3 秒后跳转!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(L_Row+3+1, 60, 1000, 3);
}

//判断用户名与密码是否正确
int IsRight(USER* user)
{
	if (NULL == user)
	{
		GoToXY(0, 0);
		printf("Wrong pointer to user");
		return 0;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("User.dat", "rb")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open User.dat\n");
		return 0;
	}
	//循环读文件
	USER us={0};
	while (fread(&us, sizeof(USER), 1, pFile) != 0)
	{
		if (strcmp(user->name, us.name) == 0 && strcmp(user->key, us.key) == 0)
		{
			user->mark = us.mark;
			fclose(pFile);
			return 1;
		}
	}
	fclose(pFile);
	return 0;
}

//退出系统
void QuitUI(int iRow)
{
	GoToXY(iRow, 0);		//第iRow行位置开始输出
	printf("\t\t\t\t\t*         感谢使用，3 秒后退出!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(iRow, 60, 1000, 3);
}