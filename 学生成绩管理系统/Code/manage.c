#include"manage.h"

//管理界面统筹函数
void Manege(void)
{
	ManageMenuUI();
	//检查是否已经录入科目信息
	if (ChackSubject())	
	{
		m = ReadSubjectFromFile();
	}
	//如果没有录入科目信息
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
		//游客只能查看，不能修改信息
		if (0 == strcmp(g_user.name, "游客")&&(iOrder==1|| iOrder == 2 || iOrder == 3 || iOrder == 4 ))
		{
			VisterNoticeUI();
		}
		//没有学生信息提示
		else if (0 == head.count &&
			(iOrder==3|| iOrder == 4 || iOrder == 5 || iOrder == 6 || iOrder == 7 || iOrder == 8 || iOrder == 9))
		{
			NoneNoticeUI();
		}
		else
		{
			switch (iOrder)
			{
			case 0:		//0.注销并返回
				ManageMenuUI();
				CancelUI(M_Row + 1);
				SaveInFile(&head);
				Free(&head);
				return;
				break;
			case 1:		//1.修改科目信息
				if (ChangSubjectUI())
				{
					m = AddSubject(M_Row + 1 + 2);
					GoToXY(M_Row + 1 + 1 + m + 3, 0);
					AddSubjectSuccessUI();
					SaveSubjectToFile(m);
					//将链表和文件中的学生信息清空
					Free(&head);
					FILE* pFile = fopen("student.dat", "w");
					fclose(pFile);
					//重新进行科目信息统计
					SubjectStatistic(&head);
				}
				else
				{
					GoToXY(M_Row + 1 + 2, 0);
					AddSubjectFailUI();
				}
				break;
			case 2:		//2.添加学生信息
				AddStu(&stu.data);
				GoToXY(M_Row + 8 + m, 0);
				if (AddToLinkEnd(&head, &stu.data))
				{
					AddStuSuccessUI();
					SaveInFile(&head);
					//重新进行科目信息统计
					SubjectStatistic(&head);
				}
				else
				{
					AddStuFailUI();
				}
				break;
			case 3:		//3.修改学生信息
			{
				ManageMenuUI();
				int iTemp;
				while (1)
				{
					//选择搜索方式
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
					//清空缓冲区
					char c = 0;
					while ((c = getchar()) != '\n' && c != EOF);
				}
				//修改指定学生信息
				GoToXY(M_Row + 2 + 1, 0);
				if (1 == Seekone(&head, &stu.data))
				{
					Change(&head, &stu.data);
					GoToXY(M_Row + 8 + m, 0);
					ChangeSuccessUI();
					SaveInFile(&head);
					//重新进行科目信息统计
					SubjectStatistic(&head);
				}
				else
				{
					GoToXY(M_Row + 2 + 1, 0);
					SearchFailUI();
				}
				break;
			}
			case 4:		//4.删除学生信息
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
					//清空缓冲区
					char c = 0;
					while ((c = getchar()) != '\n' && c != EOF);
				}
				//删除指定学生信息
				GoToXY(M_Row + 2 + 1, 0);
				if (Deleteone(&head, &stu.data))
				{
					GoToXY(M_Row + 2 + 1, 0);
					DeleteSuccessUI();
					SaveInFile(&head);
					//重新统计科目信息
					SubjectStatistic(&head);
				}
				else
				{
					GoToXY(M_Row + 2 + 1, 0);
					SearchFailUI();
				}
				break;
			}
			case 5:		//5.显示所有学生信息
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
						//不进行分段统计
						LookAll(&head,0);
						break;
					}
					else if (2 == temp)
					{
						SortByScoreBubble(&head);
						//对学生进行分段统计
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
							//清空缓冲区
							char c = 0;
							while ((c = getchar()) != '\n' && c != EOF);
						}
						//不进行分段统计
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
			case 6:		//6.显示所有科目信息
			{
				PrintSubject(&head);
				break;
			}
			case 7:		//7.个人成绩查询
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
					//清空缓冲区
					char c = 0;
					while ((c = getchar()) != '\n' && c != EOF);
				}
				if (1 == Seekone(&head, &stu.data))	//查找是否有该学生
				{
					LookOne(&head, &stu.data);
				}
				else
				{
					GoToXY(M_Row + 2 + 1, 0);
					SearchFailUI();
				}
				break;
			case 8:		//8.班级成绩查询
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
			case 9:		//9.导出信息到EXCEL表格
				//按学号排序
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

//管理主菜单
void ManageMenuUI(void)
{
	system("cls");
	GoToXY(2, 0);
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*         欢 迎 使 用 本 系 统          *\n");
	printf("\t\t\t\t\t*             操作员：                  *\n");
	GoToXY(4, 62);
	printf(g_user.name);		//输出当前用户账号
	GoToXY(5, 0);
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t* |        0.注销并返回               | *\n");
	printf("\t\t\t\t\t* |        1.修改科目信息             | *\n");
	printf("\t\t\t\t\t* |        2.添加学生信息             | *\n");
	printf("\t\t\t\t\t* |        3.修改学生信息             | *\n");
	printf("\t\t\t\t\t* |        4.删除学生信息             | *\n");
	printf("\t\t\t\t\t* |        5.显示所有学生信息         | *\n");
	printf("\t\t\t\t\t* |        6.显示所有科目信息         | *\n");
	printf("\t\t\t\t\t* |        7.学生成绩查询             | *\n");
	printf("\t\t\t\t\t* |        8.班级成绩查询             | *\n");
	printf("\t\t\t\t\t* |        9.导出信息到EXCEL表格      | *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*             输入指令：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//检查是否输入科目信息
int ChackSubject(void)
{
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("subject.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open subject.dat!");
		return 0;
	}
	//检查是否到达文件末尾
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

//无科目信息提示
void SubjectWrongUI(void)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*        无科目信息，请重新录入!        *\n");
}

//科目信息录入
int AddSubject(int iLine)
{
	GoToXY(iLine, 0);
	printf("\t\t\t\t\t*           请输入科目数：              *\n");
	printf("\t\t\t\t\t*****************************************\n");
	GoToXY(iLine, 66);
	int m=0;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		GoToXY(iLine + i + 1, 0);
		printf("\t\t\t\t\t*    请输入第%-2d个科目的名称：           * \n",i);
		printf("\t\t\t\t\t*****************************************\n");
		GoToXY(iLine + i + 1, 69);
		scanf("%s", subject[i]);
	}
	printf("\t\t\t\t\t*****************************************\n");
	return m;
}

//信息录入成功提示
void AddSubjectSuccessUI(void)
{
	printf("\t\t\t\t\t*           录入科目信息成功!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//信息录入失败提示
void AddSubjectFailUI(void)
{
	printf("\t\t\t\t\t*        已取消，请重新输入指令!        *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//保存科目信息进文件
void SaveSubjectToFile(int m)
{
	//打开文件
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

//从文件中读取科目信息
int ReadSubjectFromFile(void)
{
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("subject.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open subject.dat!");
		return 0;
	}
	//读取科目信息
	int m;
	fscanf(pFile,"%d", &m);
	for (int i = 1; i <= m; i++)
	{
		fscanf(pFile, "%s", subject[i] );
	}
	return m;
	fclose(pFile);
}

//更改科目信息提示
int ChangSubjectUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*   学生信息将清空，是否继续？(Y/N)     *\n");
	printf("\t\t\t\t\t*****************************************\n");
	GoToXY(M_Row + 1, 76);
	while ((getchar()) != '\n');
	char temp = getchar();
	if (temp == 'Y' || temp == 'y')
	{
		//清空缓冲区
		while ((temp = getchar()) != '\n' && temp != EOF);
		return 1;
	}
	while ((temp = getchar()) != '\n' && temp != EOF);
	return 0;
}

//统计科目信息
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

//打印科目信息
void PrintSubject(NODE* head)
{
	ManageMenuUI();
	GoToXY(M_Row, 0);
	printf("\t\t\t\t*********************************************************\n");
	printf("\t\t\t\t*   科目     学生人数    平均分    及格率     优秀率    *\n");
	printf("\t\t\t\t*-------------------------------------------------------*\n");
	for (int i = 1; i <= m; i++)
	{
		printf("\t\t\t\t*  %-13s%-9d%-10.2lf%-6.2lf%%    %-6.2lf%%   *\n",subject[i],head->count,subsco[i][0], subsco[i][1], subsco[i][2]);
	}
	printf("\t\t\t\t*-------------------------------------------------------*\n");
	printf("\t\t\t\t*********************************************************\n");
}

//游客登录提示
void VisterNoticeUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         游客只能进行查看操作!         *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//添加学生信息
void AddStu(STUDENT* stu)
{
	//参数合法性检查
	if (NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	ManageMenuUI();
	//输出学生基本信息数据提示头
	printf("\t\t\t\t\t*          学生班级:                    *\n");
	printf("\t\t\t\t\t*          学生姓名:                    *\n");
	printf("\t\t\t\t\t*          学生学号:                    *\n");
	printf("\t\t\t\t\t*          性别(M or W):                *\n");
	printf("\t\t\t\t\t*   出生日期(如2003 10 01):             *\n");
	printf("\t\t\t\t\t*****************************************\n");
	//录入学生基本信息
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
	//输出学生成绩数据提示头
	GoToXY(M_Row + 7, 0);
	int sum = 0;
	for (int i = 1; i <= m; i++)
	{
		printf("\t\t\t\t\t*         %10s成绩:               *\n", subject[i]);
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

//添加学生信息成功提示
void AddStuSuccessUI(void)
{
	printf("\t\t\t\t\t*           学生信息添加成功!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//添加学生失信息败提示
void AddStuFailUI(void)
{
	printf("\t\t\t\t\t*           学生信息添加失败!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//双向循环链表节点的初始化
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

//链表的尾添加
int AddToLinkEnd(NODE* head, STUDENT* stu)
{
	//参数合法性检查
	if (NULL == head || NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//申请节点内存
	NODE* pTemp = (NODE*)malloc(sizeof(NODE));
	if (NULL == pTemp)
	{
		GoToXY(0, 0);
		printf("No enough memory!");
		return 0;
	}
	//成员赋值
	Initialization(pTemp);
	pTemp->data = *stu;
	head->count++;
	//将新节点添加进有空头双向链表中
	pTemp->pNext = head;
	pTemp->pPre = head->pPre;
	head->pPre->pNext = pTemp;
	head->pPre = pTemp;
	return 1;
}

//把链表中学生信息保存进文件
void SaveInFile(NODE* head)
{
	//参数合法性检查
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("student.dat", "w")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open student.dat!");
		return;
	}
	//遍历链表写入文件
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		fwrite(&(pTemp->data), sizeof(STUDENT), 1, pFile);
		pTemp = pTemp->pNext;
	}
	//关闭文件
	fclose(pFile);
}

//保存成功提示
void SaveInFileSuccessUI()
{
	ManageMenuUI();
	GoToXY(M_Row+ 1, 0);
	printf("\t\t\t\t\t*           学生信息保存成功!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//从文件中读取数据到链表
void ReadfromFile(NODE* head)
{
	if (NULL == head)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("student.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open student.dat!");
		return;
	}
	//遍历链表写入文件
	STUDENT pTemp;
	while (0 != fread(&pTemp, sizeof(STUDENT), 1, pFile))
	{
		AddToLinkEnd(head, &pTemp);
	}
	//关闭文件
	fclose(pFile);
}

//搜索指定学生名字界面
int OneStuNameUI(void)
{

	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*            请输入搜索方式；           *\n");
	printf("\t\t\t\t\t*     1、按学号搜索   2、按姓名搜索     *\n");
	printf("\t\t\t\t\t*****************************************\n");
	GoToXY(M_Row + 1, 69);
	int temp;
	scanf("%d", &temp);
	if (1 == temp)
	{
		ManageMenuUI();
		GoToXY(M_Row + 1, 0);
		printf("\t\t\t\t\t*            搜索学号：                 *\n");
		printf("\t\t\t\t\t*****************************************\n");
		return 1;
	}
	else if (2 == temp)
	{
		ManageMenuUI();
		GoToXY(M_Row + 1, 0);
		printf("\t\t\t\t\t*           搜索姓名：                  *\n");
		printf("\t\t\t\t\t*****************************************\n");
		return 2;
	}
	return 0;
}

//搜索学生是否存在
int Seekone(NODE* head, STUDENT* stu)
{
	//参数合法性检查
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

//显示指定学生
void LookOne(NODE* head, STUDENT* stu)
{
	//参数合法性检查
	if (NULL == head || NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	//输出数据提示头
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
	printf("\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("* 班级       学号         姓名    性别  出生日期   ");
	for (int i = 1; i <= m; i++) printf(" %-9s", subject[i]);
	printf(" 总分  平均分 ");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	//循环链表
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
	//数据结尾
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
}

//查看方式界面
void LookWayUI(void)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*           请输入查看方式；            *\n");
	printf("\t\t\t\t\t*             1、按学号顺序             *\n");
	printf("\t\t\t\t\t*             2、按总成绩顺序           *\n");
	printf("\t\t\t\t\t*             3、按科目排序             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//查看所有学生信息
void LookAll(NODE* head,int Bool)
{
	//参数合法性检查
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	ManageMenuUI();
	GoToXY(M_Row , 0);
	//输出数据提示头
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
	printf("\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("* 班级       学号         姓名    性别  出生日期   ");
	for (int i = 1; i <= m; i++) printf(" %-9s", subject[i]);
	printf(" 总分  平均分 ");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	//循环链表
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
				printf(" 分数段：%-4d～%-4d  该段人数：%-3d 总人数：%-4d"
					, section, section + 10, cnt, head->count);
				for (int i = 0; i <= 8 + 5 * m; i++)
				{
					printf("-");
				}
				printf("*\n");
				//重置计数器
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
	printf("* | 总计 |  及格率 %-6.2lf%%   优秀率 %-6.2lf%%", 100.0 * (Passnum + Excellentnum) / head->count, 100.0 * Excellentnum / head->count);
	for (int i = 0; i <= 21 + 10 * m; i++) printf(" ");
	printf("*\n");
	//数据结尾
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
}

//修改指定学生信息
void Change(NODE* head, STUDENT* stu)
{
	//参数合法性检查
	if (NULL == head || 0 == head->count || NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	//遍历链表查找
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		if (0 == strcmp(pTemp->data.stuName, stu->stuName) || pTemp->data.stuID == stu->stuID)
		{
			ManageMenuUI();
			//输出学生基本信息数据提示头
			printf("\t\t\t\t\t*          学生班级:                    *\n");
			printf("\t\t\t\t\t*          学生姓名:                    *\n");
			printf("\t\t\t\t\t*          学生学号:                    *\n");
			printf("\t\t\t\t\t*          性别(M or W):                *\n");
			printf("\t\t\t\t\t*   出生日期(如2003 10 01):             *\n");
			printf("\t\t\t\t\t*****************************************\n");
			//录入学生基本信息
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
			//输出学生成绩数据提示头
			GoToXY(M_Row + 7, 0);
			int sum = 0;
			for (int i = 1; i <= m; i++)
			{
				printf("\t\t\t\t\t*         %10s成绩:               *\n", subject[i]);
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

//修改成功提示
void ChangeSuccessUI(void)
{
	printf("\t\t\t\t\t*               修改成功!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//修改失败提示
void SearchFailUI(void)
{
	printf("\t\t\t\t\t*       搜索失败，找不到该学生!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//删除指定学生
int Deleteone(NODE* head, STUDENT* stu)
{
	//参数合法性检查
	if (NULL == head || 0 == head->count || NULL == stu)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//遍历链表查找
	NODE* pTemp = head->pNext;
	while (pTemp != head)
	{
		if (0 == strcmp(pTemp->data.stuName, stu->stuName) || pTemp->data.stuID == stu->stuID)
		{
			NODE* pT = pTemp;
			pTemp = pTemp->pNext;
			//数量减一
			head->count--;
			//删除节点
			pT->pPre->pNext = pT->pNext;
			pT->pNext->pPre = pT->pPre;
			free(pT);
			return 1;
		}
		pTemp = pTemp->pNext;
	}
	return 0;
}

//删除成功提示
void DeleteSuccessUI(void)
{
	printf("\t\t\t\t\t*               删除成功!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//班级成绩查询界面
void ClassSearchUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*       请输入要查询的班级：            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//班级成绩查询失败
void ClassSearchFailUI(void)
{
	printf("\t\t\t\t\t*            不存在该班级!!!            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//班级成绩程序打印
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
	//输出数据提示头
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
	printf("\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("* 班级       学号         姓名    性别  出生日期   ");
	for (int i = 1; i <= m; i++) printf(" %-9s", subject[i]);
	printf(" 总分  平均分 ");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	//循环链表
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
	printf("* | 总计 |  班级 %-10s及格率 %-6.2lf%%   优秀率 %-6.2lf%%", Class, 100.0 * (Passnum + Excellentnum) / cnt, 100.0 * Excellentnum / cnt);
	for (int i = 0; i <= 6 + 10 * m; i++) printf(" ");
	printf("*\n");
	//数据结尾
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	printf("*");
	for (int i = 1; i <= 64 + 10 * m; i++) printf("-");
	printf("*\n");
	for (int i = 0; i <= 26 - 5 * m; i++) printf(" ");
	for (int i = 1; i <= 66 + 10 * m; i++) printf("*");
	printf("\n");
	return 1;

}

//按学号冒泡排序
void SortByIDBubble(NODE* head)
{
	ManageMenuUI();
	//参数合法性检查
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//冒泡排序
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

//按总成绩冒泡排序
void SortByScoreBubble(NODE* head)
{
	ManageMenuUI();
	//参数合法性检查
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//冒泡排序
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

//按科目成绩冒泡排序
void SortBySubjectBubble(NODE* head,int subnum)
{
	ManageMenuUI();
	//参数合法性检查
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//冒泡排序
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

//按科目排序选择界面
void SortBySubjectUI(void)
{
	printf("\t\t\t\t\t*            排序依据科目；             *\n");
	for (int i = 1; i <= m; i++)
	{
		printf("\t\t\t\t\t*              %d、%-10s            *\n"
			, i , subject[i]);
	}
	printf("\t\t\t\t\t*****************************************\n");
}

//排序成功提示
void SortSuccessUI(void)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*               排序完毕!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//导出信息到EXCEL表格
int ExportToXls(NODE* head)
{
	ManageMenuUI();
	//参数合法性检查
	if (NULL == head || 0 == head->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("student.xls", "w")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open student.xls!");
		return 0;
	}
	//遍历链表写入文件
		//输出数据提示头
	fprintf(pFile, "班级\t学号\t姓名\t性别\t出生日期\t");
	for (int i = 1; i <= m; i++)
	{
		fprintf(pFile, "%s\t", subject[i]);
	}
	fprintf(pFile, "总分\t平均分\n");
	//循环链表输出数据
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
	//关闭文件
	fclose(pFile);
	return 1;
}

//导出成功提示
void ExportToXlsSuccessUI(void)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*               导出成功!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//没有学生信息提示
void NoneNoticeUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         操作失败，无学生信息!         *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//释放链表占用的内存空间
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

//退出系统
void CancelUI(int iRow)
{
	GoToXY(iRow, 0);		//第iRow行位置开始输出
	printf("\t\t\t\t\t*         感谢使用，3 秒后注销!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(iRow, 60, 1000, 3);
}