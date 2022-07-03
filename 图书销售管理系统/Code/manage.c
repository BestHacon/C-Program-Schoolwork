#include"manage.h"

//�������ͳ�ﺯ��
void Manege(void)
{
	nowuser = g_user;
	ManageMenuUI();
	MNODE mhead;
	InitialMem(&mhead);
	MenReadfromFile(&mhead);
	BNODE bhead;
	InitialBook(&bhead);
	BookReadfromFile(&bhead);
	while (1)
	{
		MNODE mem;
		InitialMem(&mem);
		BNODE book;
		InitialBook(&book);
		int iOrder = -1;
		GoToXY(M_Row - 1, 64);
		scanf("%d", &iOrder);
		//��ͨ�û����ܸ����û���Ϣ
		if (0 == nowuser.mark && (iOrder == 6))
		{
			VisterNoticeUI();
		}
		else
		{
			switch (iOrder)
			{
			case 0:		//0.ע��������
				ManageMenuUI();
				CancelUI(M_Row + 1);
				FreeMem(&mhead);
				FreeBook(&bhead);
				return;
				break;
			case 1:		//1.��Ա����
			{
				MemManageUI();
				while (1)
				{
					int Order1 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order1);
					if (Order1 == 0)		//�������˵�
					{
						ManageMenuUI();
						break;
					}
					else if (Order1 == 1)	//��ʾ��Ա��Ϣ
					{
						if (!PrintAllMen(&mhead))
						{
							NonMem();
							GoToXY(M_Row + 3, 65);
							putchar(' ');
						}
					}
					else if (Order1 == 2)	//��ӻ�Ա
					{
						MemAddUI(&mem.data);
						MemAddToLinkEnd(&mhead, &mem.data);
						MemSaveInFile(&mhead);
						GoToXY(M_Row + 9 + 4 + 1, 0);
						MemSucceedToDoUI();
					}
					else if (Order1 == 3)	//�޸Ļ�Ա
					{
						MemSearchUI(&mem.data);
						if (MemSearch(&mhead, &mem.data))
						{
							MemCorrect(&mhead, &mem.data);
							MemManageUI();
							GoToXY(M_Row + 9 + 1, 0);
							MemSucceedToDoUI();
							MemSaveInFile(&mhead);
						}
						else
						{
							MemManageUI();
							GoToXY(M_Row + 9 + 1, 0);
							SearchFailUI();
						}
					}
					else if (Order1 == 4)	//ɾ����Ա
					{
						MemSearchUI(&mem.data);
						if (MemSearch(&mhead, &mem.data))
						{
							MemDelete(&mhead, &mem.data);
							MemManageUI();
							GoToXY(M_Row + 9 + 1, 0);
							MemSucceedToDoUI();
							MemSaveInFile(&mhead);
						}
						else
						{
							MemManageUI();
							GoToXY(M_Row + 9 + 1, 0);
							SearchFailUI();
						}
					}
					else
					{
						char c = 0;
						while ((c = getchar()) != '\n' && c != EOF);
						MemManageUI();
						OrderWrongUI(M_Row + 9 + 1);
					}
					InitialMem(&mem);
				}
				break;
			}
			case 2:		//2.�鼮����
			{
				BookManageUI();
				while (1)
				{
					int Order2 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order2);
					if (Order2 == 0)		//�������˵�
					{
						ManageMenuUI();
						break;
					}
					else if (Order2 == 1)	//�鿴��Ŀ
					{
						BookManageUI();
						SortByBookIDBubble(&bhead);
						GoToXY(M_Row + 9, 0);
						if (!PrintAllBook(&bhead))
						{
							NonBook();
							GoToXY(M_Row + 3, 65);
							putchar(' ');
						}
					}
					else if (Order2 == 2)	//�����Ŀ
					{
						BookAddUI(&book.data);
						BookAddToLinkEnd(&bhead, &book.data);
						BookSaveInFile(&bhead);
						GoToXY(M_Row + 9 + 6 + 1, 0);
						BookSucceedToDoUI();
					}
					else if (Order2 == 3)	//�޸���Ŀ
					{
						BookSearchUI(&book.data);
						if (BookSearch(&bhead, &book.data))
						{
							BookCorrect(&bhead, &book.data);
							BookManageUI();
							GoToXY(M_Row + 9 + 1, 0);
							BookSucceedToDoUI();
							BookSaveInFile(&bhead);
						}
						else
						{
							BookManageUI();
							GoToXY(M_Row + 9 + 1, 0);
							SearchFailUI();
						}
					}
					else if (Order2 == 4)	//ɾ����Ŀ
					{
						BookSearchUI(&book.data);
						if (BookSearch(&bhead, &book.data))
						{
							BookDelete(&bhead, &book.data);
							BookManageUI();
							GoToXY(M_Row + 9 + 1, 0);
							BookSucceedToDoUI();
							BookSaveInFile(&bhead);
						}
						else
						{
							BookManageUI();
							GoToXY(M_Row + 9 + 1, 0);
							SearchFailUI();
						}
					}
					else
					{
						char c = 0;
						while ((c = getchar()) != '\n' && c != EOF);
						BookManageUI();
						OrderWrongUI(M_Row + 9 + 1);
					}
				}
				break;
			}
			case 3:		//3.�������
			{
				ManageMenuUI();
				Shop(&bhead, &mhead, &book.data, &mem.data);
				MemSaveInFile(&mhead);
				BookSaveInFile(&bhead);
				FILE* pTemp;
				if ((pTemp = fopen("record.dat", "a")) == NULL)
				{
					exit(0);
				}
				fwrite(&buy, sizeof(buy), 1, pTemp);
				fclose(pTemp);
				break;
			}
			case 4:		//4.����ͳ��
			{
				ManageMenuUI();
				GoToXY(M_Row, 0);
				LookAllStatic();
				break;
			}
			case 5:		//5.���۲���
			{
				SellStrategyUI();
				while (1)
				{
					int Order5 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order5);
					if (Order5 == 0)		//�������˵�
					{
						ManageMenuUI();
						break;
					}
					else if (Order5 == 1)	//�鼮����
					{
						BookDisSearchUI(&book.data);
						if (BookSearch(&bhead, &book.data))
						{
							GoToXY(M_Row + 8 + 5, 0);
							BookDiscount();
							GoToXY(M_Row + 8 + 6, 70);
							scanf("%d", &tbook->bookdiscount);
							SellStrategyUI();
							GoToXY(M_Row + 8 + 1, 0);
							BookSucceedToDoUI();
							BookSaveInFile(&bhead);
						}
						else
						{
							SellStrategyUI();
							GoToXY(M_Row + 8 + 1, 0);
							SearchFailUI();
						}
					}
					else if (Order5 == 2)	//�ܼ�����
					{
						SellStrategyUI();
						GoToXY(M_Row + 8, 0);
						FullMinus();
						GoToXY(M_Row + 9, 57);
						scanf("%d", &discount[0]);
						GoToXY(M_Row + 9, 67);
						scanf("%d", &discount[1]);
						GoToXY(M_Row + 9 + 1 + 1, 0);
						BookSucceedToDoUI();

					}
					else if (Order5 == 3)	//�������
					{
						SellStrategyUI();
						CleanAllStrategy(&bhead);
						GoToXY(M_Row + 8 + 1, 0);
						BookSucceedToDoUI();
					}
					else
					{
						char c = 0;
						while ((c = getchar()) != '\n' && c != EOF);
						SellStrategyUI();
						OrderWrongUI(M_Row + 8 + 1);
					}
					BookSaveInFile(&bhead);
				}

				break;
			}
			case 6:		//6.�û�����
			{

				UserManageUI();
				while (1)
				{
					int Order6 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order6);
					if (Order6 == 0)		//�������˵�
					{
						ManageMenuUI();
						break;
					}
					else if (Order6 == 1)	//�鿴�����û�
					{
						LookAllUser();
					}
					else if (Order6 == 2)	//�����ͨ�û�
					{
						AddUser(&g_user, 0);
						if (0 == IsUserExist(&g_user))		//������ ������ļ� �û���ӳɹ�
						{
							GoToXY(M_Row + 8 + 3 + 1, 0);
							AddUserSuccess();
							SaveUser(&g_user);
						}
						else				//���� ��ʵ���ʧ��
						{
							GoToXY(M_Row + 8 + 3 + 1, 0);
							AddUserFail();
						}
					}
					else if (Order6 == 3)	//��Ӹ߼��û�
					{
						AddUser(&g_user, 1);
						if (0 == IsUserExist(&g_user))		//������ ������ļ� �û���ӳɹ�
						{
							GoToXY(M_Row + 8 + 3 + 1, 0);
							AddUserSuccess();
							SaveUser(&g_user);
						}
						else				//���� ��ʵ���ʧ��
						{
							GoToXY(M_Row + 8 + 3 + 1, 0);
							AddUserFail();
						}
					}
					//else if (Order6 == 4)
					//{
					//	DeleteUser(&g_user);
					//	if (IsUserExist(&g_user))
					//	{
					//		UserDelete(&g_user);
					//		ManageMenuUI();
					//		UserManageUI();
					//		GoToXY(M_Row + 9 + 1, 0);
					//		MemSucceedToDoUI();
					//	}
					//	else
					//	{
					//		ManageMenuUI();
					//		UserManageUI();
					//		SearchFailUI();
					//	}
					//}
					else
					{
						char c = 0;
						while ((c = getchar()) != '\n' && c != EOF);
						ManageMenuUI();
						UserManageUI();
						OrderWrongUI(M_Row + 8 + 1);
					}
				}
				break;
			}
			case 7:		//7.�������ݵ�EXCEL���
			{
				StaticToEXCELUI();
				while (1)
				{
					char str[30];
					int Order7 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order7);
					if (Order7 == 0)		//�������˵�
					{
						ManageMenuUI();
						break;
					}
					else if (Order7 == 1)	//����Ա���ݵ�����EXCEL
					{
						StaticToEXCELUI();
						GoToXY(M_Row + 9, 0);
						GetFileName();
						GoToXY(M_Row + 9, 65);
						scanf("%s", str);
						strcat(str, ".xls\0");
						MenToEXCEL(&mem,str);
						GoToXY(M_Row + 11, 0);
						SuccessToExcel();
					}
					else if (Order7 == 2)	//���鼮���ݵ�����EXCEL
					{
						StaticToEXCELUI();
						GoToXY(M_Row + 9, 0);
						GetFileName();
						GoToXY(M_Row + 9, 65);
						scanf("%s", str);
						strcat(str, ".xls\0");
						BookToEXCEL(&book,str);
						GoToXY(M_Row + 11, 0);
						SuccessToExcel();
					}
					else if (Order7 == 3)	//���������ݵ�����EXCEL
					{
						StaticToEXCELUI();
						GoToXY(M_Row + 9, 0);
						GetFileName();
						GoToXY(M_Row + 9, 65);
						scanf("%s", str);
						strcat(str, ".xls\0");
						RecordToEXCEL(str);
						GoToXY(M_Row + 11, 0);
						SuccessToExcel();
					}
					else
					{
						char c = 0;
						while ((c = getchar()) != '\n' && c != EOF);
						StaticToEXCELUI();
						OrderWrongUI(M_Row + 8 + 1);
					}
				}
				break;
			}
			default:
			{
				char c = 0;
				while ((c = getchar()) != '\n' && c != EOF);
				ManageMenuUI();
				OrderWrongUI(M_Row + 1);
			}
			}
		}
	}
}
//�������˵�
void ManageMenuUI(void)
{
	system("cls");
	GoToXY(2, 0);
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*         �� ӭ ʹ �� �� ϵ ͳ          *\n");
	printf("\t\t\t\t\t*                   ��                  *\n");
	GoToXY(4, 52);
	if (nowuser.mark == 1) printf("�߼��û�");
	else printf("��ͨ�û�");
	GoToXY(4, 62);
	printf(nowuser.name);		//�����ǰ�û��˺�
	GoToXY(5, 0);
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t* |             0.ע������            | *\n");
	printf("\t\t\t\t\t* |             1.��Ա����            | *\n");
	printf("\t\t\t\t\t* |             2.�鼮����            | *\n");
	printf("\t\t\t\t\t* |             3.�������            | *\n");
	printf("\t\t\t\t\t* |             4.����ͳ��            | *\n");
	printf("\t\t\t\t\t* |             5.���۲���            | *\n");
	printf("\t\t\t\t\t* |             6.�û�����            | *\n");
	printf("\t\t\t\t\t* |             7.���ݵ���            | *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*             ����ָ�                *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//��ͨ�û�������ʾ
void VisterNoticeUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*       ��ͨ�û����ܸ����û���Ϣ!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//����ʱ��
void Time(struct date* iTime)
{
	time_t t;
	struct tm* lt;
	time(&t);			//��ȡUnixʱ���
	lt = localtime(&t);	//תΪʱ��ṹ
	iTime->year = lt->tm_year + 1900;
	iTime->month = lt->tm_mon + 1;
	iTime->day = lt->tm_mday;
	iTime->hour = lt->tm_hour;
	iTime->min = lt->tm_min;
	iTime->sec = lt->tm_sec;
	return ;
}

//��Ա����˵�
void MemManageUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         ͼ�����ϵͳ>>��Ա����        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              ����ָ�               *\n");
	printf("\t\t\t\t\t*             0���������˵�             *\n");
	printf("\t\t\t\t\t*             1����ʾ��Ա               *\n");
	printf("\t\t\t\t\t*             2����ӻ�Ա               *\n");
	printf("\t\t\t\t\t*             3���޸Ļ�Ա               *\n");                                                                  
	printf("\t\t\t\t\t*             4��ɾ����Ա               *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//��ӡ���л�Ա��Ϣ
int PrintAllMen(MNODE* mhead)
{
	//�����Ϸ��Լ��
	if (NULL == mhead || 0 == mhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	MemManageUI();
	SortByMomIDBubble(mhead);
	GoToXY(M_Row+9, 0);
	//���������ʾͷ
	printf("\t\t\t\t    *************************************************\n");
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	printf("\t\t\t\t    * ��Ա��    ����     ����        �������       *\n");
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	//ѭ������
	MNODE* pTemp = mhead->pNext;
	while (pTemp != mhead)
	{
		printf("\t\t\t\t    * %-10llu%-9s%-6d %04d\\%02d\\%02d %02d:%02d:%02d *\n",pTemp->data.memID, pTemp->data.memname, pTemp->data.mempoint,
			pTemp->data.memdate.year, pTemp->data.memdate.month, pTemp->data.memdate.day, pTemp->data.memdate.hour, pTemp->data.memdate.min, pTemp->data.memdate.sec);
		pTemp = pTemp->pNext;
	}
	//���ݽ�β
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	printf("\t\t\t\t    *************************************************\n");
	return 1;
}

//��Ա��ѯ����
void MemSearchUI(MEMBER* mem)
{
	MemManageUI();
	GoToXY(M_Row + 9 + 1, 0);
	printf("\t\t\t\t\t*            ������������ʽ��           *\n");
	printf("\t\t\t\t\t*    1������Ա������   2������������    *\n");
	printf("\t\t\t\t\t*****************************************\n");
	while (1)
	{
		GoToXY(M_Row + 9 + 1, 69);
		int temp = -1;
		scanf("%d", &temp);
		if (1 == temp)
		{
			GoToXY(M_Row + 9 + 3 + 1, 0);
			printf("\t\t\t\t\t*           ������Ա�ţ�                *\n");
			printf("\t\t\t\t\t*****************************************\n");
			GoToXY(M_Row + 9 + 3 + 1, 64);
			scanf("%llu", &mem->memID);
			break;
		}
		else if (2 == temp)
		{
			GoToXY(M_Row + 9 + 3 + 1, 0);
			printf("\t\t\t\t\t*           ����������                  *\n");
			printf("\t\t\t\t\t*****************************************\n");
			GoToXY(M_Row + 9 + 3 + 1, 62);
			scanf("%s", mem->memname);
			break;
		}
		else
		{
			char c = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			MemManageUI();
			GoToXY(M_Row + 9 + 1, 0);
			printf("\t\t\t\t\t*            ������������ʽ��           *\n");
			printf("\t\t\t\t\t*    1������Ա������   2������������    *\n");
			printf("\t\t\t\t\t*****************************************\n");
			OrderWrongUI(M_Row + 9 + 3 + 1);
		}
	}
	return;
}

//��ѯʧ�ܽ���
void SearchFailUI(void)
{
	printf("\t\t\t\t\t*       ����ʧ�ܣ������ڸ���Ϣ!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�޻�Ա��Ϣ
void NonMem(void)
{
	GoToXY(M_Row + 9 + 1, 0);
	printf("\t\t\t\t\t*             �޻�Ա��Ϣ!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�����ɹ�����
void MemSucceedToDoUI(void)
{
	printf("\t\t\t\t\t*               �����ɹ�!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//��Ա��ӽ���
void MemAddUI(MEMBER*mem)
{
	//�����Ϸ��Լ��
	if (NULL == mem)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	MemManageUI();
	//�����Ա������Ϣ������ʾͷ
	printf("\t\t\t\t\t*           ��Ա��:                     *\n");
	printf("\t\t\t\t\t*            ����:                      *\n");
	printf("\t\t\t\t\t*            ���֣�                     *\n");
	printf("\t\t\t\t\t*****************************************\n");
	//¼���Ա������Ϣ
	GoToXY(M_Row +9+ 1, 60);
	scanf("%llu", &mem->memID);
	GoToXY(M_Row +9+ 2, 60);
	scanf("%s", mem->memname);
	GoToXY(M_Row +9+ 3, 60);
	scanf("%d", &mem->mempoint);
	Time(&mem->memdate);
}

//��Ա�����β���
int MemAddToLinkEnd(MNODE* mhead, MEMBER* mem)
{
	//�����Ϸ��Լ��
	if (NULL == mhead || NULL == mem)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//����ڵ��ڴ�
	MNODE* pTemp = (MNODE*)malloc(sizeof(MNODE));
	if (NULL == pTemp)
	{
		GoToXY(0, 0);
		printf("No enough memory!");
		return 0;
	}
	//��Ա��ֵ
	InitialMem(pTemp);
	pTemp->data = *mem;
	mhead->count++;
	//���½ڵ���ӽ��п�ͷ˫��������
	pTemp->pNext = mhead;
	pTemp->pPre = mhead->pPre;
	mhead->pPre->pNext = pTemp;
	mhead->pPre = pTemp;
	return 1;
}

//����Ա��ð������
void SortByMomIDBubble(MNODE* mhead)
{
	//�����Ϸ��Լ��
	if (NULL == mhead || 0 == mhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//ð������
	for (int i = 0; i < mhead->count; i++)
	{
		MNODE* pTemp = mhead->pNext;
		while (pTemp->pNext != mhead)
		{
			if (pTemp->data.memID > pTemp->pNext->data.memID)
			{
				MEMBER temp = pTemp->data;
				pTemp->data = pTemp->pNext->data;
				pTemp->pNext->data = temp;
			}
			pTemp = pTemp->pNext;
		}
	}
}

//��Ա����Ĳ�ѯ
int MemSearch(MNODE* mhead, MEMBER* mem)
{
	//�����Ϸ��Լ��
	if (NULL == mhead || NULL == mem)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	MNODE* pTemp = mhead->pNext;
	while (pTemp != mhead)
	{
		if (0 == strcmp(pTemp->data.memname, mem->memname) || pTemp->data.memID == mem->memID)
		{
			tmem = &pTemp->data;
			return 1;
		}
		pTemp = pTemp->pNext;
	}
	return 0;
}

//��Ա��Ϣ���޸�
void MemCorrect(MNODE* mhead, MEMBER* mem)
{
	//�����Ϸ��Լ��
	if (NULL == mhead || NULL == mem)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	MNODE* pTemp = mhead->pNext;
	while (pTemp != mhead)
	{
		if (0 == strcmp(pTemp->data.memname, mem->memname) || pTemp->data.memID == mem->memID)
		{
			MemManageUI();
			//�����Ա������Ϣ������ʾͷ
			printf("\t\t\t\t\t*           ��Ա��:                     *\n");
			printf("\t\t\t\t\t*            ����:                      *\n");
			printf("\t\t\t\t\t*            ���֣�                     *\n");
			printf("\t\t\t\t\t*****************************************\n");
			//¼���Ա������Ϣ
			GoToXY(M_Row + 9 + 1, 60);
			scanf("%llu", &mem->memID);
			GoToXY(M_Row + 9 + 2, 60);
			scanf("%s", mem->memname);
			GoToXY(M_Row + 9 + 3, 60);
			scanf("%d", &mem->mempoint);
			Time(&mem->memdate);
			pTemp->data = *mem;
			return ;
		}
		pTemp = pTemp->pNext;
	}
	return ;
}

//��Ա����Ľڵ�ɾ��
void MemDelete(MNODE* mhead, MEMBER* mem)
{
	//�����Ϸ��Լ��
	if (NULL == mhead || 0 == mhead->count || NULL == mem)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	//�����������
	MNODE* pTemp = mhead->pNext;
	while (pTemp != mhead)
	{
		if (0 == strcmp(pTemp->data.memname, mem->memname) || pTemp->data.memID == mem->memID)
		{
			MNODE* pT = pTemp;
			pTemp = pTemp->pNext;
			//������һ
			mhead->count--;
			//ɾ���ڵ�
			pT->pPre->pNext = pT->pNext;
			pT->pNext->pPre = pT->pPre;
			free(pT);
			return ;
		}
		pTemp = pTemp->pNext;
	}
	return ;
}

//���ļ��ж�ȡ��Ա����
void MenReadfromFile(MNODE* mhead)
{
	if (NULL == mhead)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("member.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open member.dat!");
		return;
	}
	//��������д���ļ�
	MEMBER pTemp;
	while (0 != fread(&pTemp, sizeof(MEMBER), 1, pFile))
	{
		MemAddToLinkEnd(mhead, &pTemp);
	}
	//�ر��ļ�
	fclose(pFile);
}

//�������л�Ա��Ϣ������ļ�
void MemSaveInFile(MNODE* mhead)
{
	//�����Ϸ��Լ��
	if (NULL == mhead )
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("member.dat", "w")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open member.dat!");
		return;
	}
	//��������д���ļ�
	
	MNODE* pTemp = mhead->pNext;
	while (pTemp != mhead)
	{
		fwrite(&(pTemp->data), sizeof(MEMBER), 1, pFile);
		pTemp = pTemp->pNext;
	}
	//�ر��ļ�
	fclose(pFile);
}

//��ʼ����Ա����ڵ�
void InitialMem(MNODE* mem)
{
	if (NULL == mem)
	{
		GoToXY(0, 0);
		printf("The pointer is NULL!");
		return;
	}
	mem->count = 0;
	mem->pPre = mem;
	mem->pNext = mem;
	mem->data.memID = 0;
	mem->data.mempoint = 0;
	mem->data.memdate.year = 0;
	mem->data.memdate.month = 0;
	mem->data.memdate.day = 0;
	mem->data.memdate.hour = 0;
	mem->data.memdate.min = 0;
	mem->data.memdate.sec = 0;
	memset(mem->data.memname, 0, sizeof(mem->data.memname));
}

//�ͷŻ�Ա����ռ�õ��ڴ�ռ�
void FreeMem(MNODE* mhead)
{
	if (NULL == mhead || 0 == mhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	MNODE* pTemp = mhead->pNext;
	while (pTemp != mhead)
	{
		MNODE* p = pTemp;
		pTemp = pTemp->pNext;
		free(p);
	}
	InitialMem(mhead);
}

//�鼮����ҳ��
void BookManageUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         ͼ�����ϵͳ>>�鼮����        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              ����ָ�               *\n");
	printf("\t\t\t\t\t*             0���������˵�             *\n");
	printf("\t\t\t\t\t*             1����ʾ��Ŀ               *\n");
	printf("\t\t\t\t\t*             2�������Ŀ               *\n");
	printf("\t\t\t\t\t*             3���޸���Ŀ               *\n");
	printf("\t\t\t\t\t*             4��ɾ����Ŀ               *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//��ӡ�����鼮��Ϣ
int PrintAllBook(BNODE* bhead)
{
	//�����Ϸ��Լ��
	if (NULL == bhead || 0 == bhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//���������ʾͷ
	printf("\t\t     *******************************************************************************\n");
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	printf("\t\t     * ͼ���     ͼ����           ������ ���ۼ� �ۿۼ� ���        �������       *\n");
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	//ѭ������
	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		printf("\t\t     * %-11llu%-18s%-7d%-7d%-6d%-7d%04d\\%02d\\%02d %02d:%02d:%02d *\n",pTemp->data.bookID,pTemp->data.bookname,pTemp->data.bookinput,pTemp->data.bookoutput,pTemp->data.bookdiscount,pTemp->data.stock,
			pTemp->data.bookdate.year, pTemp->data.bookdate.month, pTemp->data.bookdate.day, pTemp->data.bookdate.hour, pTemp->data.bookdate.min, pTemp->data.bookdate.sec);
		pTemp = pTemp->pNext;
	}
	//���ݽ�β
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	printf("\t\t     *******************************************************************************\n");
	return 1;
}

//�鼮��ѯ����
void BookSearchUI(BOOK* book)
{
	BookManageUI();
	GoToXY(M_Row + 9 + 1, 0);
	printf("\t\t\t\t\t*            ������������ʽ��           *\n");
	printf("\t\t\t\t\t*    1����ͼ�������   2������������    *\n");
	printf("\t\t\t\t\t*****************************************\n");
	while (1)
	{
		GoToXY(M_Row + 9 + 1, 69);
		int temp = -1;
		scanf("%d", &temp);
		if (1 == temp)
		{
			GoToXY(M_Row + 9 + 3 + 1, 0);
			printf("\t\t\t\t\t*           ����ͼ��ţ�                *\n");
			printf("\t\t\t\t\t*****************************************\n");
			GoToXY(M_Row + 9 + 3 + 1, 64);
			scanf("%llu", &book->bookID);
			break;
		}
		else if (2 == temp)
		{
			GoToXY(M_Row + 9 + 3 + 1, 0);
			printf("\t\t\t\t\t*           ����������                  *\n");
			printf("\t\t\t\t\t*****************************************\n");
			GoToXY(M_Row + 9 + 3 + 1, 62);
			scanf("%s",book->bookname);
			break;
		}
		else
		{
			char c = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			BookManageUI();
			GoToXY(M_Row + 9 + 1, 0);
			printf("\t\t\t\t\t*            ������������ʽ��           *\n");
			printf("\t\t\t\t\t*    1����ͼ�������   2������������    *\n");
			printf("\t\t\t\t\t*****************************************\n");
			OrderWrongUI(M_Row + 9 + 3 + 1);
		}
	}
	return;
}

//����Ŀ��Ϣ
void NonBook(void)
{
	GoToXY(M_Row + 9 + 1, 0);
	printf("\t\t\t\t\t*             ����Ŀ��Ϣ!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�����ɹ�����
void BookSucceedToDoUI(void)
{
	printf("\t\t\t\t\t*               �����ɹ�!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�鼮��ӽ���
void BookAddUI(BOOK* book)
{
	//�����Ϸ��Լ��
	if (NULL == book)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	BookManageUI();
	//�����Ա������Ϣ������ʾͷ
	printf("\t\t\t\t\t*           ͼ��ţ�                    *\n");
	printf("\t\t\t\t\t*           ͼ������                    *\n");
	printf("\t\t\t\t\t*           �����ۣ�                    *\n");
	printf("\t\t\t\t\t*           ���ۼۣ�                    *\n");
	printf("\t\t\t\t\t*           �������                    *\n");
	printf("\t\t\t\t\t*****************************************\n");
	//¼���Ա������Ϣ
	GoToXY(M_Row + 9 + 1, 60);
	scanf("%llu", &book->bookID);
	GoToXY(M_Row + 9 + 2, 60);
	scanf("%s", book->bookname);
	GoToXY(M_Row + 9 + 3, 60);
	scanf("%d", &book->bookinput);
	GoToXY(M_Row + 9 + 4, 60);
	scanf("%d", &book->bookoutput);
	book->bookdiscount = book->bookoutput;
	GoToXY(M_Row + 9 + 5, 60);
	scanf("%d", &book->stock);
	Time(&book->bookdate);
	return;
}

//�鼮�����β���
int BookAddToLinkEnd(BNODE* bhead, BOOK* book)
{
	//�����Ϸ��Լ��
	if (NULL == bhead || NULL == book)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//����ڵ��ڴ�
	BNODE* pTemp = (BNODE*)malloc(sizeof(BNODE));
	if (NULL == pTemp)
	{
		GoToXY(0, 0);
		printf("No enough memory!");
		return 0;
	}
	//��Ա��ֵ
	InitialBook(pTemp);
	pTemp->data = *book;
	bhead->count++;
	//���½ڵ���ӽ��п�ͷ˫��������
	pTemp->pNext = bhead;
	pTemp->pPre = bhead->pPre;
	bhead->pPre->pNext = pTemp;
	bhead->pPre = pTemp;
	return 1;
}

//���鼮���ð������
void SortByBookIDBubble(BNODE* bhead)
{
	//�����Ϸ��Լ��
	if (NULL == bhead || 0 == bhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//ð������
	for (int i = 0; i < bhead->count; i++)
	{
		BNODE* pTemp = bhead->pNext;
		while (pTemp->pNext != bhead)
		{
			if (pTemp->data.bookID > pTemp->pNext->data.bookID)
			{
				BOOK temp = pTemp->data;
				pTemp->data = pTemp->pNext->data;
				pTemp->pNext->data = temp;
			}
			pTemp = pTemp->pNext;
		}
	}
}

//�鼮����Ĳ�ѯ
int BookSearch(BNODE* bhead, BOOK* book)
{
	//�����Ϸ��Լ��
	if (NULL == bhead || NULL == book)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		if (0 == strcmp(pTemp->data.bookname, book->bookname) || pTemp->data.bookID == book->bookID)
		{
			tbook = &pTemp->data;
			return 1;
		}
		pTemp = pTemp->pNext;
	}
	return 0;
}

//�鼮��Ϣ���޸�
void BookCorrect(BNODE* bhead, BOOK* book)
{
	//�����Ϸ��Լ��
	if (NULL == bhead || NULL == book)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		if (0 == strcmp(pTemp->data.bookname, book->bookname) || pTemp->data.bookID == book->bookID)
		{;
			BookManageUI();
			//�����Ա������Ϣ������ʾͷ
			printf("\t\t\t\t\t*           ͼ��ţ�                    *\n");
			printf("\t\t\t\t\t*           ͼ������                    *\n");
			printf("\t\t\t\t\t*           �����ۣ�                    *\n");
			printf("\t\t\t\t\t*           ���ۼۣ�                    *\n");
			printf("\t\t\t\t\t*           �������                    *\n");
			printf("\t\t\t\t\t*****************************************\n");
			//¼���Ա������Ϣ
			GoToXY(M_Row + 9 + 1, 60);
			scanf("%llu", &book->bookID);
			GoToXY(M_Row + 9 + 2, 60);
			scanf("%s", book->bookname);
			GoToXY(M_Row + 9 + 3, 60);
			scanf("%d", &book->bookinput);
			GoToXY(M_Row + 9 + 4, 60);
			scanf("%d", &book->bookoutput);
			book->bookdiscount = book->bookoutput;
			GoToXY(M_Row + 9 + 5, 60);
			scanf("%d", &book->stock);
			Time(&book->bookdate);
			pTemp->data = *book;
			return;
		}
		pTemp = pTemp->pNext;
	}
	return;
}

//�鼮����Ľڵ�ɾ��
void BookDelete(BNODE* bhead, BOOK* book)
{
	//�����Ϸ��Լ��
	if (NULL == bhead || 0 == bhead->count || NULL == book)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	//�����������
	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		if (0 == strcmp(pTemp->data.bookname, book->bookname) || pTemp->data.bookID == book->bookID)
		{
			BNODE* pT = pTemp;
			pTemp = pTemp->pNext;
			//������һ
			bhead->count--;
			//ɾ���ڵ�
			pT->pPre->pNext = pT->pNext;
			pT->pNext->pPre = pT->pPre;
			free(pT);
			return;
		}
		pTemp = pTemp->pNext;
	}
	return;
}

//���ļ��ж�ȡ�鼮����
void BookReadfromFile(BNODE* bhead)
{
	if (NULL == bhead)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("book.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open book.dat!");
		return;
	}
	//��������д���ļ�
	BOOK pTemp;
	while (0 != fread(&pTemp, sizeof(BOOK), 1, pFile))
	{
		BookAddToLinkEnd(bhead, &pTemp);
	}
	//�ر��ļ�
	fclose(pFile);
}

//���������鼮��Ϣ������ļ�
void BookSaveInFile(BNODE* bhead)
{
	//�����Ϸ��Լ��
	if (NULL == bhead )
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("book.dat", "w")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open book.dat!");
		return;
	}
	//��������д���ļ�

	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		fwrite(&(pTemp->data), sizeof(BOOK), 1, pFile);
		pTemp = pTemp->pNext;
	}
	//�ر��ļ�
	fclose(pFile);
}

//��ʼ���鼮����ڵ�
void InitialBook(BNODE* book)
{
	if (NULL == book)
	{
		GoToXY(0, 0);
		printf("The pointer is NULL!");
		return;
	}
	book->count = 0;
	book->pPre = book;
	book->pNext = book;
	book->data.bookID = 0;
	book->data.bookinput = 0;
	book->data.bookoutput = 0;
	book->data.bookdiscount = 0;
	book->data.stock = 0;
	book->data.bookdate.year = 0;
	book->data.bookdate.month = 0;
	book->data.bookdate.day = 0;
	book->data.bookdate.hour = 0;
	book->data.bookdate.min = 0;
	book->data.bookdate.sec = 0;
	memset(book->data.bookname, 0, sizeof(book->data.bookname));
}

//�ͷ��鼮����ռ�õ��ڴ�ռ�
void FreeBook(BNODE* bhead)
{
	if (NULL == bhead || 0 == bhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		BNODE* p = pTemp;
		pTemp = pTemp->pNext;
		free(p);
	}
	InitialBook(bhead);
}

//����������
void Shop(BNODE*bhead,MNODE* mhead,BOOK* book, MEMBER* mem)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         ͼ�����ϵͳ>>�������        *\n");
	PrintAllBook(bhead);
	printf("\t\t     *	�������Ա�ţ�                                                             *\n");
	printf("\t\t     *******************************************************************************\n");
	while(1)
	{
		GoToXY(M_Row + bhead->count+7+1, 38);
		scanf("%llu", &mem->memID);
		if (!MemSearch(mhead, mem))
		{
			GoToXY(M_Row + bhead->count + 7 + 1, 0);
			printf("\t\t     *	�������Ա�ţ�                                           �޸û�Ա��Ϣ����  *\n");
			printf("\t\t     *******************************************************************************\n");
			char c = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		else
		{
			break;
		}
	}
	GoToXY(M_Row + bhead->count + 9 + 1, 0);
	printf("\t\t     *	������ͼ��ţ�                                                             *\n");
	printf("\t\t     *******************************************************************************\n");
	while (1)
	{
		GoToXY(M_Row + bhead->count + 9+ 1, 38);
		scanf("%llu", &book->bookID);
		if (!BookSearch(bhead, book))
		{
			GoToXY(M_Row + bhead->count + 9 + 1, 0);
			printf("\t\t     *	������ͼ��ţ�                                           �޸�ͼ����Ϣ����  *\n");
			printf("\t\t     *******************************************************************************\n");
			char c = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		else
		{
			break;
		}
	}
	int temp, sum,actual;
	temp = sum=actual = 0;
	GoToXY(M_Row + bhead->count + 11 + 1, 0);
	printf("\t\t     *	�����빺������                                                             *\n");
	printf("\t\t     *******************************************************************************\n");
	while (1)
	{
		GoToXY(M_Row + bhead->count + 11 + 1, 38);
		scanf("%d",&temp);
		sum = temp * (tbook->bookoutput);				//�鼮ԭ��
		if (discount[0] == 0)
		{
			actual = temp * (tbook->bookdiscount);
		}
		else
		{
			actual = temp * (tbook->bookdiscount) - (temp * (tbook->bookdiscount) / discount[0] * discount[1]);
		}
		if (temp>tbook->stock)
		{
			GoToXY(M_Row + bhead->count + 11 + 1, 0);
			printf("\t\t     *	�����빺������                                           ��ͼ�鲻�㣡��    *\n");
			printf("\t\t     *******************************************************************************\n");
			char c = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		else if (actual > tmem->mempoint)
		{
			GoToXY(M_Row + bhead->count + 11 + 1, 0);
			printf("\t\t     *	�����빺������                                           �û�Ա���ֲ��㣡��*\n");
			printf("\t\t     *******************************************************************************\n");
			char c = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		else
		{
			tbook->stock -= temp;
			tmem->mempoint -= actual;
			buy.number = temp;
			buy.book = *tbook;
			buy.mem = *tmem;
			buy.primecost = temp * tbook->bookinput;
			buy.originprice = sum;
			buy.actualprice = actual;
			buy.profit = actual - buy.primecost;
			Time(&buy.buydate);
			GoToXY(M_Row + bhead->count + 13 + 1, 0);
			printf("\t\t     *	                              ����ɹ�������                               *\n");
			printf("\t\t     *******************************************************************************\n");
			break;
		}
	}

}

//����ͳ��
void LookAllStatic(void)
{
	//���������ʾͷ
	printf("\t\t     *******************************************************************************\n");
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	printf("\t\t     * �����Ա ������Ŀ  �������� ������ ���ۼ� �ۿۼ� ����        ��������       *\n");
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	//ѭ������
	FILE* pTemp;
	int sum=0;
	if ((pTemp = fopen("record.dat", "r")) == NULL)
	{
		exit(0);
	}
	else
	{
		while (0!=fread(&buy,sizeof(buy),1,pTemp))
		{
			printf("\t\t     * %-9s%-13s%-7d%-7d%-7d%-6d%-7d%04d\\%02d\\%02d %02d:%02d:%02d *\n",buy.mem.memname,buy.book.bookname,buy.number,buy.primecost,buy.originprice,buy.actualprice,buy.profit,
				buy.buydate.year, buy.buydate.month, buy.buydate.day,buy.buydate.hour, buy.buydate.min, buy.buydate.sec);
			sum += buy.profit;
		}
	}
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	printf("\t\t     *                                  ������%-7d                            *\n",sum);
	//���ݽ�β
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	printf("\t\t     *******************************************************************************\n");
	return ;
}

//���۲����ƶ�����
void SellStrategyUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         ͼ�����ϵͳ>>���۲���        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              ����ָ�               *\n");
	printf("\t\t\t\t\t*             0���������˵�             *\n");
	printf("\t\t\t\t\t*             1���鼮����               *\n");
	printf("\t\t\t\t\t*             2���ܼ�����               *\n");
	printf("\t\t\t\t\t*             3���������               *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�鼮����
void BookDiscount(void)
{
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*         �۸�� %-4d �½�Ϊ            *\n",tbook->bookoutput);
	printf("\t\t\t\t\t*****************************************\n");
}

//�鼮���۲�ѯ����
void BookDisSearchUI(BOOK* book)
{
	SellStrategyUI();
	GoToXY(M_Row + 8 + 1, 0);
	printf("\t\t\t\t\t*            ������������ʽ��           *\n");
	printf("\t\t\t\t\t*    1����ͼ�������   2������������    *\n");
	printf("\t\t\t\t\t*****************************************\n");
	while (1)
	{
		GoToXY(M_Row + 8 + 1, 69);
		int temp = -1;
		scanf("%d", &temp);
		if (1 == temp)
		{
			GoToXY(M_Row + 8 + 3 + 1, 0);
			printf("\t\t\t\t\t*           ����ͼ��ţ�                *\n");
			printf("\t\t\t\t\t*****************************************\n");
			GoToXY(M_Row + 8 + 3 + 1, 64);
			scanf("%llu", &book->bookID);
			break;
		}
		else if (2 == temp)
		{
			GoToXY(M_Row + 8 + 3 + 1, 0);
			printf("\t\t\t\t\t*           ����������                  *\n");
			printf("\t\t\t\t\t*****************************************\n");
			GoToXY(M_Row + 8 + 3 + 1, 62);
			scanf("%s", book->bookname);
			break;
		}
		else
		{
			char c = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			SellStrategyUI();
			GoToXY(M_Row + 8 + 1, 0);
			printf("\t\t\t\t\t*            ������������ʽ��           *\n");
			printf("\t\t\t\t\t*    1����ͼ�������   2������������    *\n");
			printf("\t\t\t\t\t*****************************************\n");
			OrderWrongUI(M_Row + 8 + 3 + 1);
		}
	}
	return;
}

//�ܼ�����
void FullMinus(void)
{

	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*           ÿ��        ��              *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//������в���
void CleanAllStrategy(BNODE* bhead)
{
	discount[0] = discount[1] = 0;
	//�����Ϸ��Լ��
	if (NULL == bhead)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		pTemp->data.bookdiscount = pTemp->data.bookoutput;
		pTemp = pTemp->pNext;
	}
	return ;
}

//�û�����˵�
void UserManageUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         ͼ�����ϵͳ>>�û�����        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              ����ָ�               *\n");
	printf("\t\t\t\t\t*            0���������˵�              *\n");
	printf("\t\t\t\t\t*            1���鿴�����û�            *\n");
	printf("\t\t\t\t\t*            2�������ͨ�û�            *\n");
	printf("\t\t\t\t\t*            3����Ӹ߼��û�            *\n");
	//printf("\t\t\t\t\t*            4��ɾ���û�                *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�鿴�����û�
void LookAllUser(void)
{
	ManageMenuUI();
	UserManageUI();
	GoToXY(M_Row + 8, 0);
	//���������ʾͷ
	printf("\t\t\t\t    *************************************************\n");
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	printf("\t\t\t\t    *   �û�����    �˺�            ����            *\n");
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("User.dat", "rb")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open User.dat\n");
		return ;
	}
	//ѭ�����ļ�
	USER us = { 0 };
	while (fread(&us, sizeof(USER), 1, pFile) != 0)
	{
		char str[20];
		if (us.mark == 0) strcpy(str, "��ͨ�û�");
		else strcpy(str, "�߼��û�");
		Encryption(us.key);
		printf("\t\t\t\t    *   %s    %-16s%-16s*\n",str,us.name,us.key);
	}
	//���ݽ�β
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	printf("\t\t\t\t    *************************************************\n");
	return ;
}

//����û�
void AddUser(USER* user, int Mark)
{
	ManageMenuUI();
	UserManageUI();
	GoToXY(M_Row +8+ 1, 0);		//��10��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*           �˺� :                      *\n");
	printf("\t\t\t\t\t*           ���� :                      *\n");
	printf("\t\t\t\t\t*****************************************\n");
	GoToXY(M_Row +8+ 1, 59);
	scanf("%s", user->name);
	GoToXY(M_Row +8+ 1 + 1, 59);
	scanf("%s", user->key);
	Encryption(user->key);
	user->mark = Mark;
}

//�ж��û����Ƿ����
int IsUserExist(USER* user)
{
	if (NULL == user)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
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

//�û���ӳɹ�����
void AddUserSuccess(void)
{
	printf("\t\t\t\t\t*              ��ӳɹ�!!!              *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�û����ʧ��
void AddUserFail(void)
{
	printf("\t\t\t\t\t*         ���ʧ�ܣ��û��Ѵ���!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//ע��󣬽��˺�����洢���ļ�
void SaveUser(USER* user)
{
	if (NULL == user)
	{
		printf("Illegal parameter!");
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

////ɾ���û�����
//void DeleteUser(USER* user)
//{
//	ManageMenuUI();
//	UserManageUI();
//	GoToXY(M_Row + 9 + 1, 0);
//	while (1)
//	{
//			GoToXY(M_Row + 9 + 1, 0);
//			printf("\t\t\t\t\t*           �����˺ţ�                  *\n");
//			printf("\t\t\t\t\t*****************************************\n");
//			GoToXY(M_Row + 9+ 1, 62);
//			scanf("%s", user->name);
//			break;
//	}
//	return;
//}

////�û�ɾ��
//void UserDelete(USER* user)
//{
//
//	if (NULL == user)
//	{
//		GoToXY(0, 0);
//		printf("Illegal parameter!");
//		return ;
//	}
//	//���ļ�
//	FILE* pFile;
//	if ((pFile = fopen("User.dat", "ab")) == NULL)
//	{
//		GoToXY(0, 0);
//		printf("Failure to open User.dat\n");
//		return ;
//	}
//	//ѭ�����ļ�
//	USER us = { 0 };
//	FILE *pT;
//	if ((pT = fopen("Temp.dat", "ab")) == NULL)
//	{
//		GoToXY(0, 0);
//		printf("Failure to open User.dat\n");
//		return;
//	}
//	while (fread(&us, sizeof(USER), 1, pFile) != 0)
//	{
//		if (strcmp(user->name, us.name) == 0)
//		{
//			continue;
//		}
//		else
//		{
//			fwrite(&us, sizeof(USER), 1, pT);
//		}
//	}
//	fclose(pFile);
//	pFile = fopen("User.dat", "wb");
//	fclose(pT);
//	pT = fopen("Temp.dat", "rb");
//	while (fread(&us, sizeof(USER), 1, pT) != 0)
//	{
//		fwrite(&us, sizeof(USER), 1, pFile);
//	}
//	fclose(pT);
//	pT = fopen("Temp.dat", "wb");
//	fclose(pT);
//	fclose(pFile);
//	//SetFileAttributes(_T("Temp.dat"), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
//	//SetFileAttributes(_T("Temp.dat"), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
//	return ;
//}

//���ݵ�������
void StaticToEXCELUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         ͼ�����ϵͳ>>���ݵ���        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              ����ָ�               *\n");
	printf("\t\t\t\t\t*            0���������˵�              *\n");
	printf("\t\t\t\t\t*            1��������Ա��Ϣ            *\n");
	printf("\t\t\t\t\t*            2�������鼮��Ϣ            *\n");
	printf("\t\t\t\t\t*            3������������Ϣ            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//��ȡ�����ļ����ƽ���
void GetFileName(void)
{
	printf("\t\t\t\t\t*       �������ļ����ƣ�                *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//���鼮��Ϣ������EXCEL���
void BookToEXCEL(BNODE*book, char* str)
{
	FILE* pF,*ipTemp;
	if ((pF = fopen(str, "w")) == NULL)
	{
		exit(0);
	}
	else if ((ipTemp = fopen("book.dat", "r")) == NULL)
	{
		exit(0);
	}
	else
	{
		//���������ʾͷ
		fprintf(pF,"ͼ���\tͼ����\t������\t���ۼ�\t�ۿۼ�\t���\t�������\n");
		//�����������
		while (0 != fread(&book->data, sizeof(BOOK), 1, ipTemp))
		{
			BNODE* pTemp = book;
			fprintf(pF,"%llu\t%s\t%d\t%d\t%d\t%d\t%04d\\%02d\\%02d %02d:%02d:%02d\n", pTemp->data.bookID, pTemp->data.bookname, pTemp->data.bookinput, pTemp->data.bookoutput, pTemp->data.bookdiscount, pTemp->data.stock,
				pTemp->data.bookdate.year, pTemp->data.bookdate.month, pTemp->data.bookdate.day, pTemp->data.bookdate.hour, pTemp->data.bookdate.min, pTemp->data.bookdate.sec);
		}
	}
	fclose(pF);
	fclose(ipTemp);
	return;
}

//����Ա��Ϣ������EXCEL���
void MenToEXCEL(MNODE*mem,char* str)
{
	FILE* pF, * ipTemp;
	if ((pF = fopen(str, "w")) == NULL)
	{
		exit(0);
	}
	else if ((ipTemp = fopen("member.dat", "r")) == NULL)
	{
		exit(0);
	}
	else
	{
		//���������ʾͷ
		fprintf(pF,"��Ա��\t����\t����\t�������\n");
		//�����������
		while (0 != fread(&mem->data, sizeof(MEMBER), 1, ipTemp))
		{
			MNODE* pTemp = mem;
			fprintf(pF,"%llu\t%s\t%d\t%04d\\%02d\\%02d %02d:%02d:%02d\n", pTemp->data.memID, pTemp->data.memname, pTemp->data.mempoint,
				pTemp->data.memdate.year, pTemp->data.memdate.month, pTemp->data.memdate.day, pTemp->data.memdate.hour, pTemp->data.memdate.min, pTemp->data.memdate.sec);
		}
	}
	fclose(pF);
	fclose(ipTemp);
	return;
}

//�����ۼ�¼������EXCEL���
void RecordToEXCEL(char* str)
{
	FILE* pF, * ipTemp;
	if ((pF = fopen(str, "w")) == NULL)
	{
		exit(0);
	}
	else if ((ipTemp = fopen("record.dat", "r")) == NULL)
	{
		exit(0);
	}
	else
	{
		int sum = 0;
		//���������ʾͷ
		fprintf(pF,"�����Ա\t������Ŀ\t��������\t������\t���ۼ�\t�ۿۼ�\t����\t��������\n");
		//�����������
		while (0 != fread(&buy, sizeof(BUYRECORD), 1, ipTemp))
		{
			fprintf(pF,"%s\t%s\t%d\t%d\t%d\t%d\t%d\t%04d\\%02d\\%02d %02d:%02d:%02d\n", buy.mem.memname, buy.book.bookname, buy.number, buy.primecost, buy.originprice, buy.actualprice, buy.profit,
				buy.buydate.year, buy.buydate.month, buy.buydate.day, buy.buydate.hour, buy.buydate.min, buy.buydate.sec);
			sum += buy.profit;
		}
		fprintf(pF, "������\t%d",sum);
	}
	fclose(pF);
	fclose(ipTemp);
	return;
}

//�����ɹ���ʾ
void SuccessToExcel(void)
{
	printf("\t\t\t\t\t*            ��Ϣ�����ɹ�!!!            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�˳�ϵͳ
void CancelUI(int iRow)
{
	GoToXY(iRow, 0);		//��iRow��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*         ��лʹ�ã�3 ���ע��!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(iRow, 60, 1000, 3);
}