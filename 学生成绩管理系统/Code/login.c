#include"login.h"


//��¼����ͳ�ﺯ��
int Login(void)
{
	LoginMenuUI();					//������˵�
	while (1)
	{
		int iOrder = -1;				//�û�ָ��
		GoToXY(L_Row - 1, 70);			//���ù�������
		scanf("%d", &iOrder);
		switch (iOrder)
		{
		case 0:		//0.�˳�ϵͳ
			LoginMenuUI();
			QuitUI(L_Row + 1);
			return 0;
			break;
		case 1:		//1.�û���¼
			LoginUI();
			GoToXY(L_Row + 1, 63);		//������¼������׼�������¼��
			scanf("%s", g_user.name);
			GoToXY(L_Row+1+1, 63);
			scanf("%s", g_user.key);
			if (IsRight(&g_user))		//�ж��˺������Ƿ���ȷ
			{
				LoginSuccessUI();		//��½�ɹ�
				return 1;
			}
			else
			{
				LoginFailUI();
				GoToXY(L_Row-1, 70);
				putchar(' ');			//��סԭ���ַ�
			}
			GoToXY(L_Row - 1, 70);
			break;

		case 2:		//2.�˺�ע��
			RegisterUI();
			GoToXY(L_Row + 1, 63);
			scanf("%s", g_user.name);
			GoToXY(L_Row+1+1, 63);
			scanf("%s", g_user.key);
			if (0 == IsUserExist(&g_user))		//������ ������ļ� ��ʵע��ɹ�
			{
				SaveUser(&g_user);
				RegisterSuccessUI();
			}
			else		//���� ��ʵע��ʧ��
			{
				RegisterFailUI();
			}
			GoToXY(L_Row - 1, 70);
			break;
		case 3:		//3.�ο͵�¼
			VisterLoginUI();
			strcpy(g_user.name, "�ο�");
			return 1;
			break;
		default:		//����ָ�������ջ�����
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

//��¼�˵�
void LoginMenuUI(void)
{
	system("cls");		//��տ���̨����������˵�
	//�ڶ������
	GoToXY(2, 0);

	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*             ��ӭʹ�ñ�ϵͳ            *\n");
	printf("\t\t\t\t\t*      (��ز�����ֱ�������Ӧָ��)     *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t* |            0: �˳�ϵͳ            | *\n");
	printf("\t\t\t\t\t* |            1: �û���¼            | *\n");
	printf("\t\t\t\t\t* |            2: �˺�ע��            | *\n");
	printf("\t\t\t\t\t* |            3: �ο͵�¼            | *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*        ������ָ��(0/1/2/3):           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�ο͵�¼
void VisterLoginUI(void)
{
	LoginMenuUI();
	GoToXY(L_Row+1, 0);
	printf("\t\t\t\t\t*        3 ������ο���ݵ�½!!!      *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(L_Row+1, 49, 1000, 3);
}

//�û���¼����
void LoginUI(void)
{
	LoginMenuUI();
	GoToXY(L_Row+1, 0);		//��10��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*           ��¼�˺� :                  *\n");
	printf("\t\t\t\t\t*           ��¼���� :                  *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//��¼ʧ����ʾ
void LoginFailUI(void)
{
	GoToXY(L_Row+3+1, 0);
	printf("\t\t\t\t\t*      ��¼ʧ�ܣ�����������ָ��!!!      *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//��¼�ɹ���ʾ
void LoginSuccessUI(void)
{
	GoToXY(L_Row+3+1, 0);
	printf("\t\t\t\t\t*         ��¼�ɹ���3 �����ת!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(L_Row+3+1, 60, 1000, 3);
}

//�û�ע�����
void RegisterUI(void)
{
	LoginMenuUI();
	GoToXY(L_Row + 1, 0);		//��10��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*           ע���˺� :                  *\n");
	printf("\t\t\t\t\t*           ע������ :                  *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//ע��ʧ����ʾ
void RegisterFailUI(void)
{
	GoToXY(L_Row+3+1 , 0);
	printf("\t\t\t\t\t*         ע��ʧ�ܣ��û��Ѵ���!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//ע��ɹ���ʾ
void RegisterSuccessUI(void)
{
	GoToXY(L_Row+3+1, 0);
	printf("\t\t\t\t\t*          ע��ɹ������¼!!!          *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//ע��󣬽��˺�����洢���ļ�
void SaveUser(USER* user)
{
	if (NULL == user)
	{
		printf("Wrong pointer to user");
		return;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("User.dat", "ab")) == NULL)
	{
		printf("Failure to open User.dat\n");
		return;
	}
	//д���ļ�
	fwrite(user, sizeof(USER), 1, pFile);
	//�ر��ļ�
	fclose(pFile);
}

//�ж��û����������Ƿ���ȷ
int IsRight(USER* user)
{
	if (NULL == user)
	{
		GoToXY(0, 0);
		printf("Wrong pointer to user");
		return 0;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("User.dat", "rb")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open User.dat\n");
		return 0;
	}
	//ѭ�����ļ�
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

//�ж��û����Ƿ���ڣ���¼��Ҫ��ע����Ҫ��
int IsUserExist(struct User* user)
{
	if (NULL == user)
	{
		GoToXY(0, 0);
		printf("Wrong pointer to user");
		return 0;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("User.dat", "rb")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open User.dat\n");
		return 0;
	}
	//ѭ�����ļ�
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

//�˳�ϵͳ
void QuitUI(int iRow)
{
	GoToXY(iRow, 0);		//��iRow��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*         ��лʹ�ã�3 ����˳�!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(iRow, 60, 1000, 3);
}