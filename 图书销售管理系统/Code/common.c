#include"common.h"



//���������ļ�
void CreatFiles(void)
{
	//���˻������ö������ļ����棬�����ļ�����datΪ�ļ�����׺����߰�ȫ��
	FILE* pf1=fopen("User.dat", "ab");
	FILE* pf2=fopen("member.dat", "a");
	FILE* pf3=fopen("book.dat", "a");
	FILE* pf4 = fopen("record.dat", "a");
	fclose(pf1);
	fclose(pf2);
	fclose(pf3);
	fclose(pf4);
	//�������˻�������ļ�����ϵͳ�������أ���һ����߰�ȫ��
	SetFileAttributes(_T("User.dat"), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
}

//���ÿ���̨���λ��
void GoToXY(short iRow, short iColumn)
{
	COORD cd = { iColumn,iRow };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd); //���  ID
}

//����ʱ����
void CountDown(short iRow, short iColumn, int iTime, int iStart)
{
	for (int i = iStart; i >= 0; i--)
	{
		GoToXY(iRow, iColumn);
		printf("%d", i);
		Sleep(iTime);
	}
}

//�ַ�������
void Encryption(char* secret)
{
	for (int i = 0; secret[i] != '\0'; i++)
	{
		secret[i] = ~secret[i];
	}
}

//ָ��������ʾ����
void OrderWrongUI(int iRow)
{
	GoToXY(iRow, 0);		//��iRow��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*      ָ�������������������!!!      *\n");
	printf("\t\t\t\t\t*****************************************\n");
}