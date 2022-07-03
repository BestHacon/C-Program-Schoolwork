#include"common.h"

int Login(void);
void Manege(void);
void CreatFiles(void);

int main(void)
{
	//创建必要的储存文件
	CreatFiles();
	while (1)
	{
		if (Login())	//登录界面统筹函数
		{
			Manege();	//管理界面统筹函数
		}
		else
			break;
	}
	return 0;
}

