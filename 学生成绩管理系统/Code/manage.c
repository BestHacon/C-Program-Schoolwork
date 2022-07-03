#include"manage.h"

//�������ͳ�ﺯ��
void Manege(void)
{
	ManageMenuUI();
	//����Ƿ��Ѿ�¼���Ŀ��Ϣ
	if (ChackSubject())	
	{
		m = ReadSubjectFromFile();
	}
	//���û��¼���Ŀ��Ϣ
	else
	{
		SubjectWrongUI();
		m = AddSubject(M_Row + 1 + 1);
		GoToXY(M_Row + 1 + 1 + m + 3, 0);
		AddSubjectSuccessUI();
		SaveSubjectToFile(m);
	}
	NODE head;
	Initialization(&head);
	ReadfromFile(&head);
	SubjectStatistic(&head);
	while (1)
	{
		NODE stu;
		Initialization(&stu);
		int iOrder = -1;
		GoToXY(M_Row - 1, 64);
		scanf("%d", &iOrder);
		//�ο�ֻ�ܲ鿴�������޸���Ϣ
		if (0 == strcmp(g_user.name, "�ο�")&&(iOrder==1|| iOrder == 2 || iOrder == 3 || iOrder == 4 ))
		{
			VisterNoticeUI();
		}
		//û��ѧ����Ϣ��ʾ
		else if (0 == head.count &&
			(iOrder==3|| iOrder == 4 || iOrder == 5 || iOrder == 6 || iOrder == 7 || iOrder == 8 || iOrder == 9))
		{
			NoneNoticeUI();
		}
		else
		{
			switch (iOrder)
			{
			case 0:		//0.ע��������
				ManageMenuUI();
				CancelUI(M_Row + 1);
				SaveInFile(&head);
				Free(&head);
				return;
				break;
			case 1:		//1.�޸Ŀ�Ŀ��Ϣ
				if (ChangSubjectUI())
				{
					m = AddSubject(M_Row + 1 + 2);
					GoToXY(M_Row + 1 + 1 + m + 3, 0);
					AddSubjectSuccessUI();
					SaveSubjectToFile(m);
					//��������ļ��е�ѧ����Ϣ���
					Free(&head);
					FILE* pFile = fopen("student.dat", "w");
					fclose(pFile);
					//���½��п�Ŀ��Ϣͳ��
					SubjectStatistic(&head);
				}
				else
				{
					GoToXY(M_Row + 1 + 2, 0);
					AddSubjectFailUI();
				}
				break;
			case 2:		//2.���ѧ����Ϣ
				AddStu(&stu.data);
				GoToXY(M_Row + 8 + m, 0);
				if (AddToLinkEnd(&head, &stu.data))
				{
					AddStuSuccessUI();
					SaveInFile(&head);
					//���½��п�Ŀ��Ϣͳ��
					SubjectStatistic(&head);
				}
				else
				{
					AddStuFailUI();
				}
				break;
			case 3:		//3.�޸�ѧ����Ϣ
			{
				ManageMenuUI();
				int iTemp;
				while (1)
				{
					//ѡ��������ʽ
					iTemp = OneStuNameUI();
					if (1 == iTemp)
					{
						GoToXY(M_Row + 1, 63);
						scanf("%llu", &stu.data.stuID);
						break;
					}
					else if (2 == iTemp)
					{
						GoToXY(M_Row + 1, 62);
						scanf("%s", stu.data.stuName);
						break;
					}
					else
					{
						OrderWrongUI(M_Row + 3 + 1);
					}
					//��ջ�����
					char c = 0;
					while ((c = getchar()) != '\n' && c != EOF);
				}
				//�޸�ָ��ѧ����Ϣ
				GoToXY(M_Row + 2 + 1, 0);
				if (1 == Seekone(&head, &stu.data))
				{
					Change(&head, &stu.data);
					GoToXY(M_Row + 8 + m, 0);
					ChangeSuccessUI();
					SaveInFile(&head);
					//���½��п�Ŀ��Ϣͳ��
					SubjectStatistic(&head);
				}
				else
				{
					GoToXY(M_Row + 2 + 1, 0);
					SearchFailUI();
				}
				break;
			}
			case 4:		//4.ɾ��ѧ����Ϣ
			{
				ManageMenuUI();
				int iTemp;
				while (1)
				{
					iTemp = OneStuNameUI();
					if (1 == iTemp)
					{
						GoToXY(M_Row + 1, 63);
						scanf("%llu", &stu.data.stuID);
						break;
					}
					else if (2 == iTemp)
					{
						GoToXY(M_Row + 1, 62);
						scanf("%s", stu.data.stuName);
						break;
					}
					else
					{
						OrderWrongUI(M_Row + 3 + 1);
					}
					//��ջ�����
					char c = 0;
					while ((c = getchar()) != '\n' && c != EOF);
				}
				//ɾ��ָ��ѧ����Ϣ
				GoToXY(M_Row + 2 + 1, 0);
				if (Deleteone(&head, &stu.data))
				{
					GoToXY(M_Row + 2 + 1, 0);
					DeleteSuccessUI();
					SaveInFile(&head);
					//����ͳ�ƿ�Ŀ��Ϣ
					SubjectStatistic(&head);
				}
				else
				{
					GoToXY(M_Row + 2 + 1, 0);
					SearchFailUI();
				}
				break;
			}
			case 5:		//5.��ʾ����ѧ����Ϣ
				ManageMenuUI();
				int temp;
				while (1)
				{
					LookWayUI();
					GoToXY(M_Row + 1, 68);
					scanf("%d", &temp);
					if (1 == temp)
					{
						SortByIDBubble(&head);
						//�����зֶ�ͳ��
						LookAll(&head,0);
						break;
					}
					else if (2 == temp)
					{
						SortByScoreBubble(&head);
						//��ѧ�����зֶ�ͳ��
						LookAll(&head,1);
						break;
					}
					else if (3 == temp)
					{
						while (1)
						{
							GoToXY(M_Row + 5 + 1, 0);
							SortBySubjectUI();
							GoToXY(M_Row + 5 + 1, 67);
							int temp;
							scanf("%d", &temp);
							if (temp > 0 && temp <= m)
							{
								SortBySubjectBubble(&head, temp);
								break;
							}
							else
							{
								OrderWrongUI(M_Row + 8 + m);
							}
							//��ջ�����
							char c = 0;
							while ((c = getchar()) != '\n' && c != EOF);
						}
						//�����зֶ�ͳ��
						LookAll(&head, 0);
						break;
					}
					else
					{
						OrderWrongUI(M_Row + 5 + 1);
					}
					char c = 0;
					while ((c = getchar()) != '\n' && c != EOF);
				}
				break;
			case 6:		//6.��ʾ���п�Ŀ��Ϣ
			{
				PrintSubject(&head);
				break;
			}
			case 7:		//7.���˳ɼ���ѯ
				ManageMenuUI();
				int iTemp;
				while (1)
				{
					iTemp = OneStuNameUI();
					if (1 == iTemp)
					{
						GoToXY(M_Row + 1, 63);
						scanf("%llu", &stu.data.stuID);
						break;
					}
					else if (2 == iTemp)
					{
						GoToXY(M_Row + 1, 62);
						scanf("%s", stu.data.stuName);
						break;
					}
					else
					{
						OrderWrongUI(M_Row + 3 + 1);
					}
					//��ջ�����
					char c = 0;
					while ((c = getchar()) != '\n' && c != EOF);
				}
				if (1 == Seekone(&head, &stu.data))	//�����Ƿ��и�ѧ��
				{
					LookOne(&head, &stu.data);
				}
				else
				{
					GoToXY(M_Row + 2 + 1, 0);
					SearchFailUI();
				}
				break;
			case 8:		//8.�༶�ɼ���ѯ
				ManageMenuUI();
				ClassSearchUI();
				GoToXY(M_Row + 1, 68);
				char class[40];
				scanf("%s", class);
				GoToXY(M_Row + 2, 0);
				if (0 == ClassPrint(&head, class))
				{
					ManageMenuUI();
					GoToXY(M_Row + 1, 0);
					ClassSearchFailUI();
				}
				break;
			case 9:		//9.������Ϣ��EXCEL���
				//��ѧ������
				SortByIDBubble(&head);
				if (ExportToXls(&head))
				{
					ExportToXlsSuccessUI();
				}
				break;
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
	printf("\t\t\t\t\t*             ����Ա��                  *\n");
	GoToXY(4, 62);
	printf(g_user.name);		//�����ǰ�û��˺�
	GoToXY(5, 0);
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t* |        0.ע��������               | *\n");
	printf("\t\t\t\t\t* |        1.�޸Ŀ�Ŀ��Ϣ             | *\n");
	printf("\t\t\t\t\t* |        2.���ѧ����Ϣ             | *\n");
	printf("\t\t\t\t\t* |        3.�޸�ѧ����Ϣ             | *\n");
	printf("\t\t\t\t\t* |        4.ɾ��ѧ����Ϣ             | *\n");
	printf("\t\t\t\t\t* |        5.��ʾ����ѧ����Ϣ         | *\n");
	printf("\t\t\t\t\t* |        6.��ʾ���п�Ŀ��Ϣ         | *\n");
	printf("\t\t\t\t\t* |        7.ѧ���ɼ���ѯ             | *\n");
	printf("\t\t\t\t\t* |        8.�༶�ɼ���ѯ             | *\n");
	printf("\t\t\t\t\t* |        9.������Ϣ��EXCEL���      | *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*             ����ָ�                *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//����Ƿ������Ŀ��Ϣ
int ChackSubject(void)
{
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("subject.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open subject.dat!");
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

//�޿�Ŀ��Ϣ��ʾ
void SubjectWrongUI(void)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*        �޿�Ŀ��Ϣ��������¼��!        *\n");
}

//��Ŀ��Ϣ¼��
int AddSubject(int iLine)
{
	GoToXY(iLine, 0);
	printf("\t\t\t\t\t*           �������Ŀ����              *\n");
	printf("\t\t\t\t\t*****************************************\n");
	GoToXY(iLine, 66);
	int m=0;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		GoToXY(iLine + i + 1, 0);
		printf("\t\t\t\t\t*    �������%-2d����Ŀ�����ƣ�           * \n",i);
		printf("\t\t\t\t\t*****************************************\n");
		GoToXY(iLine + i + 1, 69);
		scanf("%s", subject[i]);
	}
	printf("\t\t\t\t\t*****************************************\n");
	return m;
}

//��Ϣ¼��ɹ���ʾ
void AddSubjectSuccessUI(void)
{
	printf("\t\t\t\t\t*           ¼���Ŀ��Ϣ�ɹ�!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//��Ϣ¼��ʧ����ʾ
void AddSubjectFailUI(void)
{
	printf("\t\t\t\t\t*        ��ȡ��������������ָ��!        *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�����Ŀ��Ϣ���ļ�
void SaveSubjectToFile(int m)
{
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("subject.dat", "w")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open subject.dat!");
		return;
	}
	fprintf(pFile,"%d\n", m);
	for (int i = 1; i <= m; i++)
	{
		fprintf(pFile, "%s ", subject[i]);
	}
	fclose(pFile);
}

//���ļ��ж�ȡ��Ŀ��Ϣ
int ReadSubjectFromFile(void)
{
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("subject.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open subject.dat!");
		return 0;
	}
	//��ȡ��Ŀ��Ϣ
	int m;
	fscanf(pFile,"%d", &m);
	for (int i = 1; i <= m; i++)
	{
		fscanf(pFile, "%s", subject[i] );
	}
	return m;
	fclose(pFile);
}

//���Ŀ�Ŀ��Ϣ��ʾ
int ChangSubjectUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*   ѧ����Ϣ����գ��Ƿ������(Y/N)     *\n");
	printf("\t\t\t\t\t*****************************************\n");
	GoToXY(M_Row + 1, 76);
	while ((getchar()) != '\n');
	char temp = getchar();
	if (temp == 'Y' || temp == 'y')
	{
		//��ջ�����
		while ((temp = getchar()) != '\n' && temp != EOF);
		return 1;
	}
	while ((temp = getchar()) != '\n' && temp != EOF);
	return 0;
}

//ͳ�ƿ�Ŀ��Ϣ
void SubjectStatistic(NODE* head)
{
	for (int i = 1; i <= m; i++)
	{
		int Passnum=0, Excellentnum=0, Sum=0;
		NODE* pTemp = head->pNext;
		while (pTemp != head)
		{
			Sum += pTemp->data.score[i];
			if (pTemp->data.score[i] >= 85)
			{
				Excellentnum++;
			}
			else if (pTemp->data.score[i] >= 60)
			{
				Passnum++;
			}
			pTemp = pTemp->pNext;
		}
		subsco[i][0] = 1.0 * Sum / head->count;
		subsco[i][1] = 100.0 * (Passnum + Excellentnum) / head->count;
		subsco[i][2] = 100.0 * (Excellentnum) / head->count;
	}
}

//��ӡ��Ŀ��Ϣ
void PrintSubject(NODE* head)
{
	ManageMenuUI();
	GoToXY(M_Row, 0);
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*   ��Ŀ     ѧ������    ƽ����    ������     ������    *\n");
	printf("\t\t\t\t*-------------------------------------------------------*\n");
	for (int i = 1; i <= m; i++)
	{
		printf("\t\t\t\t*  %-13s%-9d%-10.2lf%-6.2lf%%    %-6.2lf%%   *\n",subject[i],head->count,subsco[i][0], subsco[i][1], subsco[i][2]);
	}
	printf("\t\t\t\t*-------------------------------------------------------*\n");
	printf("\t\t\t\t*********************************************************\n");
}

//�ο͵�¼��ʾ
void VisterNoticeUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         �ο�ֻ�ܽ��в鿴����!         *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//���ѧ����Ϣ
void AddStu(STUDENT* stu)
{
	//�����Ϸ��Լ��
	if (NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	ManageMenuUI();
	//���ѧ��������Ϣ������ʾͷ
	printf("\t\t\t\t\t*          ѧ���༶:                    *\n");
	printf("\t\t\t\t\t*          ѧ������:                    *\n");
	printf("\t\t\t\t\t*          ѧ��ѧ��:                    *\n");
	printf("\t\t\t\t\t*          �Ա�(M or W):                *\n");
	printf("\t\t\t\t\t*   ��������(��2003 10 01):             *\n");
	printf("\t\t\t\t\t*****************************************\n");
	//¼��ѧ��������Ϣ
	GoToXY(M_Row+1, 61);
	scanf("%s", stu->class);
	GoToXY(M_Row + 2, 61);
	scanf("%s", stu->stuName);
	GoToXY(M_Row + 3, 61);
	scanf("%llu", &stu->stuID);
	GoToXY(M_Row + 4, 65);
	scanf("%s", stu->stuSex);
	GoToXY(M_Row + 5, 68);
	scanf("%d%d%d", &stu->birthday.year, &stu->birthday.month, &stu->birthday.day);
	//���ѧ���ɼ�������ʾͷ
	GoToXY(M_Row + 7, 0);
	int sum = 0;
	for (int i = 1; i <= m; i++)
	{
		printf("\t\t\t\t\t*         %10s�ɼ�:               *\n", subject[i]);
	}
	printf("\t\t\t\t\t*****************************************\n");
	for (int i = 1; i <= m; i++)
	{
		GoToXY(M_Row + 7 + i - 1, 66);
		scanf("%d", &stu->score[i]);
		sum += stu->score[i];
	}
	stu->sum = sum;
	stu->aver = 1.0 * sum / m;
}

//���ѧ����Ϣ�ɹ���ʾ
void AddStuSuccessUI(void)
{
	printf("\t\t\t\t\t*           ѧ����Ϣ��ӳɹ�!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//���ѧ��ʧ��Ϣ����ʾ
void AddStuFailUI(void)
{
	printf("\t\t\t\t\t*           ѧ����Ϣ���ʧ��!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//˫��ѭ������ڵ�ĳ�ʼ��
void Initialization(NODE* node)
{
	if (NULL == node)
	{
		GoToXY(0, 0);
		printf("The pointer is NULL!");
		return;
	}
	node->count = 0;
	node->pPre = node;
	node->pNext = node;
	node->data.aver = 0;
	node->data.birthday.day = 0;
	node->data.birthday.month = 0;
	node->data.birthday.year = 0;
	memset(node->data.class, 0, sizeof(node->data.class));
	for (int i = 0; i < 6; i++) 
	node->data.score[i] = 0;
	node->data.stuID = 0;
	memset(node->data.stuName, 0, sizeof(node->data.stuName));
	memmove(node->data.stuSex,"Unknow",sizeof("Unknow"));
	node->data.sum = 0;
}

//�����β���
int AddToLinkEnd(NODE* head, STUDENT* stu)
{
	//�����Ϸ��Լ��
	if (NULL == head || NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//����ڵ��ڴ�
	NODE* pTemp = (NODE*)malloc(sizeof(NODE));
	if (NULL == pTemp)
	{
		GoToXY(0, 0);
		printf("No enough memory!");
		return 0;
	}
	//��Ա��ֵ
	Initialization(pTemp);
	pTemp->data = *stu;
	head->count++;
	//���½ڵ���ӽ��п�ͷ˫��������
	pTemp->pNext = head;
	pTemp->pPre = head->pPre;
	head->pPre->pNext = pTemp;
	head->pPre = pTemp;
	return 1;
}

//��������ѧ����Ϣ������ļ�
void SaveInFile(NODE* head)
{
	//�����Ϸ��Լ��
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("student.dat", "w")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open student.dat!");
		return;
	}
	//��������д���ļ�
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		fwrite(&(pTemp->data), sizeof(STUDENT), 1, pFile);
		pTemp = pTemp->pNext;
	}
	//�ر��ļ�
	fclose(pFile);
}

//����ɹ���ʾ
void SaveInFileSuccessUI()
{
	ManageMenuUI();
	GoToXY(M_Row+ 1, 0);
	printf("\t\t\t\t\t*           ѧ����Ϣ����ɹ�!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//���ļ��ж�ȡ���ݵ�����
void ReadfromFile(NODE* head)
{
	if (NULL == head)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("student.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open student.dat!");
		return;
	}
	//��������д���ļ�
	STUDENT pTemp;
	while (0 != fread(&pTemp, sizeof(STUDENT), 1, pFile))
	{
		AddToLinkEnd(head, &pTemp);
	}
	//�ر��ļ�
	fclose(pFile);
}

//����ָ��ѧ�����ֽ���
int OneStuNameUI(void)
{

	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*            ������������ʽ��           *\n");
	printf("\t\t\t\t\t*     1����ѧ������   2������������     *\n");
	printf("\t\t\t\t\t*****************************************\n");
	GoToXY(M_Row + 1, 69);
	int temp;
	scanf("%d", &temp);
	if (1 == temp)
	{
		ManageMenuUI();
		GoToXY(M_Row + 1, 0);
		printf("\t\t\t\t\t*            ����ѧ�ţ�                 *\n");
		printf("\t\t\t\t\t*****************************************\n");
		return 1;
	}
	else if (2 == temp)
	{
		ManageMenuUI();
		GoToXY(M_Row + 1, 0);
		printf("\t\t\t\t\t*           ����������                  *\n");
		printf("\t\t\t\t\t*****************************************\n");
		return 2;
	}
	return 0;
}

//����ѧ���Ƿ����
int Seekone(NODE* head, STUDENT* stu)
{
	//�����Ϸ��Լ��
	if (NULL == head || NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		if (0 == strcmp(pTemp->data.stuName, stu->stuName) || pTemp->data.stuID == stu->stuID)
		{
			return 1;
		}
		pTemp = pTemp->pNext;
	}
	return 0;
}

//��ʾָ��ѧ��
void LookOne(NODE* head, STUDENT* stu)
{
	//�����Ϸ��Լ��
	if (NULL == head || NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	//���������ʾͷ
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
	printf("\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("* �༶       ѧ��         ����    �Ա�  ��������   ");
	for (int i = 1; i <= m; i++) printf(" %-9s", subject[i]);
	printf(" �ܷ�  ƽ���� ");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	//ѭ������
	NODE* pTemp = head->pNext;
	while (pTemp!=head)
	{
		if (0 == strcmp(pTemp->data.stuName, stu->stuName) || pTemp->data.stuID == stu->stuID)
		{
			for (int i =0; i <= 26-5*m; i++) printf(" ");
			printf("* %-11s%-13llu%-8s%-6s%-04d/%02d/%02d ",
				pTemp->data.class, pTemp->data.stuID, pTemp->data.stuName, pTemp->data.stuSex, pTemp->data.birthday.year, pTemp->data.birthday.month, pTemp->data.birthday.day);
			for (int i = 1; i <= m; i++)
			{
				printf(" %-9d", pTemp->data.score[i]);
			}
			printf(" %-4d  %-6.2lf ", pTemp->data.sum, pTemp->data.aver);
			printf("*\n");
		}
		pTemp = pTemp->pNext;
	}
	//���ݽ�β
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
}

//�鿴��ʽ����
void LookWayUI(void)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*           ������鿴��ʽ��            *\n");
	printf("\t\t\t\t\t*             1����ѧ��˳��             *\n");
	printf("\t\t\t\t\t*             2�����ܳɼ�˳��           *\n");
	printf("\t\t\t\t\t*             3������Ŀ����             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�鿴����ѧ����Ϣ
void LookAll(NODE* head,int Bool)
{
	//�����Ϸ��Լ��
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	ManageMenuUI();
	GoToXY(M_Row , 0);
	//���������ʾͷ
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
	printf("\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("* �༶       ѧ��         ����    �Ա�  ��������   ");
	for (int i = 1; i <= m; i++) printf(" %-9s", subject[i]);
	printf(" �ܷ�  ƽ���� ");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	//ѭ������
	int Passnum = 0, Excellentnum = 0;
	NODE* pTemp = head->pNext;
	int section=0, cnt=0;
	if (Bool)
	{
		section = (int)(pTemp->data.aver / 10) * 10;
		cnt = 0;
	}
	while (pTemp != head)
	{
		for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
		printf("* %-11s%-13llu%-8s%-6s%-04d/%02d/%02d ",
			pTemp->data.class, pTemp->data.stuID, pTemp->data.stuName, pTemp->data.stuSex, pTemp->data.birthday.year, pTemp->data.birthday.month, pTemp->data.birthday.day);
		for (int i = 1; i <= m; i++)
		{
			printf(" %-9d", pTemp->data.score[i]);
		}
		printf(" %-4d  %-6.2lf ", pTemp->data.sum, pTemp->data.aver);
		printf("*\n");
		if (pTemp->data.aver >= 85)
		{
			Excellentnum++;
		}
		else if (pTemp->data.aver >= 60)
		{
			Passnum++;
		}
		if (Bool)
		{
			cnt++;
			if (pTemp->pNext->data.aver < section)
			{
				for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
				printf("*");
				for (int i = 0; i <= 7 + 5 * m; i++)
				{
					printf("-");
				}
				printf(" �����Σ�%-4d��%-4d  �ö�������%-3d ��������%-4d"
					, section, section + 10, cnt, head->count);
				for (int i = 0; i <= 8 + 5 * m; i++)
				{
					printf("-");
				}
				printf("*\n");
				//���ü�����
				section = (int)(pTemp->pNext->data.aver / 10) * 10;
				cnt = 0;
			}
		}
		pTemp = pTemp->pNext;
	}
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("* | �ܼ� |  ������ %-6.2lf%%   ������ %-6.2lf%%", 100.0 * (Passnum + Excellentnum) / head->count, 100.0 * Excellentnum / head->count);
	for (int i = 0; i <= 21 + 10 * m; i++) printf(" ");
	printf("*\n");
	//���ݽ�β
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
}

//�޸�ָ��ѧ����Ϣ
void Change(NODE* head, STUDENT* stu)
{
	//�����Ϸ��Լ��
	if (NULL == head || 0 == head->count || NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	//�����������
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		if (0 == strcmp(pTemp->data.stuName, stu->stuName) || pTemp->data.stuID == stu->stuID)
		{
			ManageMenuUI();
			//���ѧ��������Ϣ������ʾͷ
			printf("\t\t\t\t\t*          ѧ���༶:                    *\n");
			printf("\t\t\t\t\t*          ѧ������:                    *\n");
			printf("\t\t\t\t\t*          ѧ��ѧ��:                    *\n");
			printf("\t\t\t\t\t*          �Ա�(M or W):                *\n");
			printf("\t\t\t\t\t*   ��������(��2003 10 01):             *\n");
			printf("\t\t\t\t\t*****************************************\n");
			//¼��ѧ��������Ϣ
			GoToXY(M_Row + 1, 61);
			scanf("%s", stu->class);
			GoToXY(M_Row + 2, 61);
			scanf("%s", stu->stuName);
			GoToXY(M_Row + 3, 61);
			scanf("%llu", &stu->stuID);
			GoToXY(M_Row + 4, 65);
			scanf("%s", stu->stuSex);
			GoToXY(M_Row + 5, 68);
			scanf("%d%d%d", &stu->birthday.year, &stu->birthday.month, &stu->birthday.day);
			//���ѧ���ɼ�������ʾͷ
			GoToXY(M_Row + 7, 0);
			int sum = 0;
			for (int i = 1; i <= m; i++)
			{
				printf("\t\t\t\t\t*         %10s�ɼ�:               *\n", subject[i]);
			}
			printf("\t\t\t\t\t*****************************************\n");
			for (int i = 1; i <= m; i++)
			{
				GoToXY(M_Row + 7 + i - 1, 66);
				scanf("%d", &stu->score[i]);
				sum += stu->score[i];
			}
			stu->sum = sum;
			stu->aver = 1.0 * sum / m;
			pTemp->data = *stu;
			return ;
		}
		pTemp = pTemp->pNext;
	}
	return ;
}

//�޸ĳɹ���ʾ
void ChangeSuccessUI(void)
{
	printf("\t\t\t\t\t*               �޸ĳɹ�!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�޸�ʧ����ʾ
void SearchFailUI(void)
{
	printf("\t\t\t\t\t*       ����ʧ�ܣ��Ҳ�����ѧ��!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//ɾ��ָ��ѧ��
int Deleteone(NODE* head, STUDENT* stu)
{
	//�����Ϸ��Լ��
	if (NULL == head || 0 == head->count || NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//�����������
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		if (0 == strcmp(pTemp->data.stuName, stu->stuName) || pTemp->data.stuID == stu->stuID)
		{
			NODE* pT = pTemp;
			pTemp = pTemp->pNext;
			//������һ
			head->count--;
			//ɾ���ڵ�
			pT->pPre->pNext = pT->pNext;
			pT->pNext->pPre = pT->pPre;
			free(pT);
			return 1;
		}
		pTemp = pTemp->pNext;
	}
	return 0;
}

//ɾ���ɹ���ʾ
void DeleteSuccessUI(void)
{
	printf("\t\t\t\t\t*               ɾ���ɹ�!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�༶�ɼ���ѯ����
void ClassSearchUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*       ������Ҫ��ѯ�İ༶��            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�༶�ɼ���ѯʧ��
void ClassSearchFailUI(void)
{
	printf("\t\t\t\t\t*            �����ڸð༶!!!            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�༶�ɼ������ӡ
int ClassPrint(NODE*head,char Class[])
{
	if (NULL == head)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	int Passnum = 0, Excellentnum = 0,cnt=0;
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		if (0 == strcmp(pTemp->data.class, Class))
		{
			cnt++;
		}
		pTemp = pTemp->pNext;
	}
	if (0 == cnt) return 0;
	pTemp = head->pNext;
	//���������ʾͷ
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
	printf("\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("* �༶       ѧ��         ����    �Ա�  ��������   ");
	for (int i = 1; i <= m; i++) printf(" %-9s", subject[i]);
	printf(" �ܷ�  ƽ���� ");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	//ѭ������
	while (pTemp != head)
	{
		if (0 == strcmp(pTemp->data.class, Class))
		{
			for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
			printf("* %-11s%-13llu%-8s%-6s%-4d/%-2d/%-3d",
				pTemp->data.class, pTemp->data.stuID, pTemp->data.stuName, pTemp->data.stuSex, pTemp->data.birthday.year, pTemp->data.birthday.month, pTemp->data.birthday.day);
			for (int i = 1; i <= m; i++)
			{
				printf(" %-9d", pTemp->data.score[i]);
			}
			printf(" %-4d  %-6.2lf ", pTemp->data.sum, pTemp->data.aver);
			printf("*\n");
			if (pTemp->data.aver >= 85)
			{
				Excellentnum++;
			}
			else if (pTemp->data.aver >= 60)
			{
				Passnum++;
			}
		}
		pTemp = pTemp->pNext;
	}
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("* | �ܼ� |  �༶ %-10s������ %-6.2lf%%   ������ %-6.2lf%%", Class, 100.0 * (Passnum + Excellentnum) / cnt, 100.0 * Excellentnum / cnt);
	for (int i = 0; i <= 6 + 10 * m; i++) printf(" ");
	printf("*\n");
	//���ݽ�β
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
	printf("\n");
	return 1;

}

//��ѧ��ð������
void SortByIDBubble(NODE* head)
{
	ManageMenuUI();
	//�����Ϸ��Լ��
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//ð������
	for (int i = 0; i < head->count; i++)
	{
		NODE* pTemp = head->pNext;
		while (pTemp->pNext != head)
		{
			if (pTemp->data.stuID > pTemp->pNext->data.stuID)
			{
				STUDENT temp = pTemp->data;
				pTemp->data = pTemp->pNext->data;
				pTemp->pNext->data = temp;
			}
			pTemp = pTemp->pNext;
		}
	}
}

//���ܳɼ�ð������
void SortByScoreBubble(NODE* head)
{
	ManageMenuUI();
	//�����Ϸ��Լ��
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//ð������
	for (int i = 0; i < head->count; i++)
	{
		NODE* pTemp = head->pNext;
		while (pTemp->pNext != head)
		{
			if (pTemp->data.sum < pTemp->pNext->data.sum)
			{
				STUDENT temp = pTemp->data;
				pTemp->data = pTemp->pNext->data;
				pTemp->pNext->data = temp;
			}
			pTemp = pTemp->pNext;
		}
	}

}

//����Ŀ�ɼ�ð������
void SortBySubjectBubble(NODE* head,int subnum)
{
	ManageMenuUI();
	//�����Ϸ��Լ��
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//ð������
	for (int i = 0; i < head->count; i++)
	{
		NODE* pTemp = head->pNext;
		while (pTemp->pNext != head)
		{
			if (pTemp->data.score[subnum] < pTemp->pNext->data.score[subnum])
			{
				STUDENT temp = pTemp->data;
				pTemp->data = pTemp->pNext->data;
				pTemp->pNext->data = temp;
			}
			pTemp = pTemp->pNext;
		}
	}
}

//����Ŀ����ѡ�����
void SortBySubjectUI(void)
{
	printf("\t\t\t\t\t*            �������ݿ�Ŀ��             *\n");
	for (int i = 1; i <= m; i++)
	{
		printf("\t\t\t\t\t*              %d��%-10s            *\n"
			, i , subject[i]);
	}
	printf("\t\t\t\t\t*****************************************\n");
}

//����ɹ���ʾ
void SortSuccessUI(void)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*               �������!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//������Ϣ��EXCEL���
int ExportToXls(NODE* head)
{
	ManageMenuUI();
	//�����Ϸ��Լ��
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//���ļ�
	FILE* pFile;
	if ((pFile = fopen("student.xls", "w")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open student.xls!");
		return 0;
	}
	//��������д���ļ�
		//���������ʾͷ
	fprintf(pFile, "�༶\tѧ��\t����\t�Ա�\t��������\t");
	for (int i = 1; i <= m; i++)
	{
		fprintf(pFile, "%s\t", subject[i]);
	}
	fprintf(pFile, "�ܷ�\tƽ����\n");
	//ѭ�������������
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		fprintf(pFile, "%s\t%llu\t%s\t%s\t%-04d/%-02d/%-02d\t",
			pTemp->data.class,pTemp->data.stuID,pTemp->data.stuName,pTemp->data.stuSex,pTemp->data.birthday.year, pTemp->data.birthday.month, pTemp->data.birthday.day);
		for (int i = 1; i <= m; i++)
		{
			fprintf(pFile, "%d\t", pTemp->data.score[i]);
		}
		fprintf(pFile, "%d\t%.2lf\n",pTemp->data.sum,pTemp->data.aver);
		pTemp = pTemp->pNext;
	}
	//�ر��ļ�
	fclose(pFile);
	return 1;
}

//�����ɹ���ʾ
void ExportToXlsSuccessUI(void)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*               �����ɹ�!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//û��ѧ����Ϣ��ʾ
void NoneNoticeUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         ����ʧ�ܣ���ѧ����Ϣ!         *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//�ͷ�����ռ�õ��ڴ�ռ�
void Free(NODE* head)
{
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		NODE* p = pTemp;
		pTemp = pTemp->pNext;
		free(p);
	}
	Initialization(head);
}

//�˳�ϵͳ
void CancelUI(int iRow)
{
	GoToXY(iRow, 0);		//��iRow��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*         ��лʹ�ã�3 ���ע��!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(iRow, 60, 1000, 3);
}