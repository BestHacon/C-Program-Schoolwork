#include"common.h"

//���������ļ�
void CreatFiles(void)
{
	//���˻������ö������ļ����棬��߰�ȫ��
	FILE* pf1=fopen("User.dat", "ab");
	FILE* pf2=fopen("student.dat", "a");
	FILE* pf3=fopen("subject.dat", "a");
	fclose(pf1);
	fclose(pf2);
	fclose(pf3);
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

//ָ��������ʾ����
void OrderWrongUI(int iRow)
{
	GoToXY(iRow, 0);		//��iRow��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*      ָ�������������������!!!      *\n");
	printf("\t\t\t\t\t*****************************************\n");
}