#include"common.h"

int Login(void);
void Manege(void);
void CreatFiles(void);

int main(void)
{
	//������Ҫ�Ĵ����ļ�
	CreatFiles();
	while (1)
	{
		if (Login())	//��¼����ͳ�ﺯ��
		{
			Manege();	//�������ͳ�ﺯ��
		}
		else
			break;
	}
	return 0;
}

