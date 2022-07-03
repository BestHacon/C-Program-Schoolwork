#include"common.h"



//创建储存文件
void CreatFiles(void)
{
	//将账户密码用二进制文件储存，数据文件都以dat为文件名后缀，提高安全性
	FILE* pf1=fopen("User.dat", "ab");
	FILE* pf2=fopen("member.dat", "a");
	FILE* pf3=fopen("book.dat", "a");
	FILE* pf4 = fopen("record.dat", "a");
	fclose(pf1);
	fclose(pf2);
	fclose(pf3);
	fclose(pf4);
	//将储存账户密码的文件设置系统属性隐藏，进一步提高安全性
	SetFileAttributes(_T("User.dat"), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
}

//设置控制台光标位置
void GoToXY(short iRow, short iColumn)
{
	COORD cd = { iColumn,iRow };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd); //句柄  ID
}

//倒计时函数
void CountDown(short iRow, short iColumn, int iTime, int iStart)
{
	for (int i = iStart; i >= 0; i--)
	{
		GoToXY(iRow, iColumn);
		printf("%d", i);
		Sleep(iTime);
	}
}

//字符串加密
void Encryption(char* secret)
{
	for (int i = 0; secret[i] != '\0'; i++)
	{
		secret[i] = ~secret[i];
	}
}

//指令有误提示界面
void OrderWrongUI(int iRow)
{
	GoToXY(iRow, 0);		//第iRow行位置开始输出
	printf("\t\t\t\t\t*      指令输入错误，请重新输入!!!      *\n");
	printf("\t\t\t\t\t*****************************************\n");
}