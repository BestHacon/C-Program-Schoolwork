#include"login.h"


//登录界面统筹函数
int Login(void)
{
	LoginMenuUI();					//输出主菜单
	while (1)
	{
		int iOrder = -1;				//用户指令
		GoToXY(L_Row - 1, 70);			//设置光标输入点
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

		case 2:		//2.账号注册
			RegisterUI();
			GoToXY(L_Row + 1, 63);
			scanf("%s", g_user.name);
			GoToXY(L_Row+1+1, 63);
			scanf("%s", g_user.key);
			if (0 == IsUserExist(&g_user))		//不存在 保存进文件 现实注册成功
			{
				SaveUser(&g_user);
				RegisterSuccessUI();
			}
			else		//存在 现实注册失败
			{
				RegisterFailUI();
			}
			GoToXY(L_Row - 1, 70);
			break;
		case 3:		//3.游客登录
			VisterLoginUI();
			strcpy(g_user.name, "游客");
			return 1;
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
	printf("\t\t\t\t\t* |            2: 账号注册            | *\n");
	printf("\t\t\t\t\t* |            3: 游客登录            | *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*        请输入指令(0/1/2/3):           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//游客登录
void VisterLoginUI(void)
{
	LoginMenuUI();
	GoToXY(L_Row+1, 0);
	printf("\t\t\t\t\t*        3 秒后将以游客身份登陆!!!      *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(L_Row+1, 49, 1000, 3);
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

//用户注册界面
void RegisterUI(void)
{
	LoginMenuUI();
	GoToXY(L_Row + 1, 0);		//第10行位置开始输出
	printf("\t\t\t\t\t*           注册账号 :                  *\n");
	printf("\t\t\t\t\t*           注册密码 :                  *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//注册失败提示
void RegisterFailUI(void)
{
	GoToXY(L_Row+3+1 , 0);
	printf("\t\t\t\t\t*         注册失败，用户已存在!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//注册成功提示
void RegisterSuccessUI(void)
{
	GoToXY(L_Row+3+1, 0);
	printf("\t\t\t\t\t*          注册成功，请登录!!!          *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//注册后，将账号密码存储进文件
void SaveUser(USER* user)
{
	if (NULL == user)
	{
		printf("Wrong pointer to user");
		return;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("User.dat", "ab")) == NULL)
	{
		printf("Failure to open User.dat\n");
		return;
	}
	//写入文件
	fwrite(user, sizeof(USER), 1, pFile);
	//关闭文件
	fclose(pFile);
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
			fclose(pFile);
			return 1;
		}
	}
	fclose(pFile);
	return 0;
}

//判断用户名是否存在（登录需要，注册需要）
int IsUserExist(struct User* user)
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
	USER us = { 0 };
	while (fread(&us, sizeof(USER), 1, pFile) != 0)
	{
		if (strcmp(user->name, us.name) == 0)
		{
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