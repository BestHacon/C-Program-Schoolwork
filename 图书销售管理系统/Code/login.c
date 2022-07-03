#include"login.h"

//��¼����ͳ�ﺯ��
int Login(void)
{
	LoginMenuUI();					//������˵�
	//����Ƿ�����û���Ϣ
	if (!ChackUser())
	{
		FirstUser();
	}
	while (1)
	{
		int iOrder = -1;				//�û�ָ��
		GoToXY(L_Row - 1, 69);			//���ù�������
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
			Encryption(g_user.key);		//��������
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
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*           ������ָ��(0/1):            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//����Ƿ�����û���Ϣ
int ChackUser(void)
{
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("User.dat", "rb")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open User.dat!");
		return 0;
	}
	//����Ƿ񵽴��ļ�ĩβ
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

//д���ʼ�˺�����
void FirstUser(void)
{
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("User.dat", "ab")) == NULL)
	{
		printf("Failure to open User.dat\n");
		return;
	}
	USER firstuser = { .name = "admin",.key = "123456",.mark = 1 };
	Encryption(firstuser.key);
	//д���ļ�
	fwrite(&firstuser, sizeof(USER), 1, pFile);
	//�ر��ļ�
	fclose(pFile);
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
			user->mark = us.mark;
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