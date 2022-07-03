#include"manage.h"

//管理界面统筹函数
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
		//普通用户不能更改用户信息
		if (0 == nowuser.mark && (iOrder == 6))
		{
			VisterNoticeUI();
		}
		else
		{
			switch (iOrder)
			{
			case 0:		//0.注销并返回
				ManageMenuUI();
				CancelUI(M_Row + 1);
				FreeMem(&mhead);
				FreeBook(&bhead);
				return;
				break;
			case 1:		//1.会员管理
			{
				MemManageUI();
				while (1)
				{
					int Order1 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order1);
					if (Order1 == 0)		//返回主菜单
					{
						ManageMenuUI();
						break;
					}
					else if (Order1 == 1)	//显示会员信息
					{
						if (!PrintAllMen(&mhead))
						{
							NonMem();
							GoToXY(M_Row + 3, 65);
							putchar(' ');
						}
					}
					else if (Order1 == 2)	//添加会员
					{
						MemAddUI(&mem.data);
						MemAddToLinkEnd(&mhead, &mem.data);
						MemSaveInFile(&mhead);
						GoToXY(M_Row + 9 + 4 + 1, 0);
						MemSucceedToDoUI();
					}
					else if (Order1 == 3)	//修改会员
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
					else if (Order1 == 4)	//删除会员
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
			case 2:		//2.书籍管理
			{
				BookManageUI();
				while (1)
				{
					int Order2 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order2);
					if (Order2 == 0)		//返回主菜单
					{
						ManageMenuUI();
						break;
					}
					else if (Order2 == 1)	//查看书目
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
					else if (Order2 == 2)	//添加书目
					{
						BookAddUI(&book.data);
						BookAddToLinkEnd(&bhead, &book.data);
						BookSaveInFile(&bhead);
						GoToXY(M_Row + 9 + 6 + 1, 0);
						BookSucceedToDoUI();
					}
					else if (Order2 == 3)	//修改书目
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
					else if (Order2 == 4)	//删除书目
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
			case 3:		//3.购物结算
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
			case 4:		//4.数据统计
			{
				ManageMenuUI();
				GoToXY(M_Row, 0);
				LookAllStatic();
				break;
			}
			case 5:		//5.销售策略
			{
				SellStrategyUI();
				while (1)
				{
					int Order5 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order5);
					if (Order5 == 0)		//返回主菜单
					{
						ManageMenuUI();
						break;
					}
					else if (Order5 == 1)	//书籍降价
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
					else if (Order5 == 2)	//总价满减
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
					else if (Order5 == 3)	//清除策略
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
			case 6:		//6.用户管理
			{

				UserManageUI();
				while (1)
				{
					int Order6 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order6);
					if (Order6 == 0)		//返回主菜单
					{
						ManageMenuUI();
						break;
					}
					else if (Order6 == 1)	//查看所有用户
					{
						LookAllUser();
					}
					else if (Order6 == 2)	//添加普通用户
					{
						AddUser(&g_user, 0);
						if (0 == IsUserExist(&g_user))		//不存在 保存进文件 用户添加成功
						{
							GoToXY(M_Row + 8 + 3 + 1, 0);
							AddUserSuccess();
							SaveUser(&g_user);
						}
						else				//存在 现实添加失败
						{
							GoToXY(M_Row + 8 + 3 + 1, 0);
							AddUserFail();
						}
					}
					else if (Order6 == 3)	//添加高级用户
					{
						AddUser(&g_user, 1);
						if (0 == IsUserExist(&g_user))		//不存在 保存进文件 用户添加成功
						{
							GoToXY(M_Row + 8 + 3 + 1, 0);
							AddUserSuccess();
							SaveUser(&g_user);
						}
						else				//存在 现实添加失败
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
			case 7:		//7.导出数据到EXCEL表格
			{
				StaticToEXCELUI();
				while (1)
				{
					char str[30];
					int Order7 = -1;
					GoToXY(M_Row + 3, 65);
					scanf("%d", &Order7);
					if (Order7 == 0)		//返回主菜单
					{
						ManageMenuUI();
						break;
					}
					else if (Order7 == 1)	//将会员数据导出到EXCEL
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
					else if (Order7 == 2)	//将书籍数据导出到EXCEL
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
					else if (Order7 == 3)	//将销售数据导出到EXCEL
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
//管理主菜单
void ManageMenuUI(void)
{
	system("cls");
	GoToXY(2, 0);
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*         欢 迎 使 用 本 系 统          *\n");
	printf("\t\t\t\t\t*                   ：                  *\n");
	GoToXY(4, 52);
	if (nowuser.mark == 1) printf("高级用户");
	else printf("普通用户");
	GoToXY(4, 62);
	printf(nowuser.name);		//输出当前用户账号
	GoToXY(5, 0);
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t* |             0.注销返回            | *\n");
	printf("\t\t\t\t\t* |             1.会员管理            | *\n");
	printf("\t\t\t\t\t* |             2.书籍管理            | *\n");
	printf("\t\t\t\t\t* |             3.购物结算            | *\n");
	printf("\t\t\t\t\t* |             4.数据统计            | *\n");
	printf("\t\t\t\t\t* |             5.销售策略            | *\n");
	printf("\t\t\t\t\t* |             6.用户管理            | *\n");
	printf("\t\t\t\t\t* |             7.数据导出            | *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*             输入指令：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//普通用户操作提示
void VisterNoticeUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*       普通用户不能更改用户信息!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//生成时间
void Time(struct date* iTime)
{
	time_t t;
	struct tm* lt;
	time(&t);			//获取Unix时间戳
	lt = localtime(&t);	//转为时间结构
	iTime->year = lt->tm_year + 1900;
	iTime->month = lt->tm_mon + 1;
	iTime->day = lt->tm_mday;
	iTime->hour = lt->tm_hour;
	iTime->min = lt->tm_min;
	iTime->sec = lt->tm_sec;
	return ;
}

//会员管理菜单
void MemManageUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         图书管理系统>>会员管理        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              输入指令：               *\n");
	printf("\t\t\t\t\t*             0、返回主菜单             *\n");
	printf("\t\t\t\t\t*             1、显示会员               *\n");
	printf("\t\t\t\t\t*             2、添加会员               *\n");
	printf("\t\t\t\t\t*             3、修改会员               *\n");                                                                  
	printf("\t\t\t\t\t*             4、删除会员               *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//打印所有会员信息
int PrintAllMen(MNODE* mhead)
{
	//参数合法性检查
	if (NULL == mhead || 0 == mhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	MemManageUI();
	SortByMomIDBubble(mhead);
	GoToXY(M_Row+9, 0);
	//输出数据提示头
	printf("\t\t\t\t    *************************************************\n");
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	printf("\t\t\t\t    * 会员号    姓名     积分        添加日期       *\n");
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	//循环链表
	MNODE* pTemp = mhead->pNext;
	while (pTemp != mhead)
	{
		printf("\t\t\t\t    * %-10llu%-9s%-6d %04d\\%02d\\%02d %02d:%02d:%02d *\n",pTemp->data.memID, pTemp->data.memname, pTemp->data.mempoint,
			pTemp->data.memdate.year, pTemp->data.memdate.month, pTemp->data.memdate.day, pTemp->data.memdate.hour, pTemp->data.memdate.min, pTemp->data.memdate.sec);
		pTemp = pTemp->pNext;
	}
	//数据结尾
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	printf("\t\t\t\t    *************************************************\n");
	return 1;
}

//会员查询界面
void MemSearchUI(MEMBER* mem)
{
	MemManageUI();
	GoToXY(M_Row + 9 + 1, 0);
	printf("\t\t\t\t\t*            请输入搜索方式：           *\n");
	printf("\t\t\t\t\t*    1、按会员号搜索   2、按姓名搜索    *\n");
	printf("\t\t\t\t\t*****************************************\n");
	while (1)
	{
		GoToXY(M_Row + 9 + 1, 69);
		int temp = -1;
		scanf("%d", &temp);
		if (1 == temp)
		{
			GoToXY(M_Row + 9 + 3 + 1, 0);
			printf("\t\t\t\t\t*           搜索会员号：                *\n");
			printf("\t\t\t\t\t*****************************************\n");
			GoToXY(M_Row + 9 + 3 + 1, 64);
			scanf("%llu", &mem->memID);
			break;
		}
		else if (2 == temp)
		{
			GoToXY(M_Row + 9 + 3 + 1, 0);
			printf("\t\t\t\t\t*           搜索姓名：                  *\n");
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
			printf("\t\t\t\t\t*            请输入搜索方式：           *\n");
			printf("\t\t\t\t\t*    1、按会员号搜索   2、按姓名搜索    *\n");
			printf("\t\t\t\t\t*****************************************\n");
			OrderWrongUI(M_Row + 9 + 3 + 1);
		}
	}
	return;
}

//查询失败界面
void SearchFailUI(void)
{
	printf("\t\t\t\t\t*       搜索失败，不存在该信息!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//无会员信息
void NonMem(void)
{
	GoToXY(M_Row + 9 + 1, 0);
	printf("\t\t\t\t\t*             无会员信息!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//操作成功界面
void MemSucceedToDoUI(void)
{
	printf("\t\t\t\t\t*               操作成功!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//会员添加界面
void MemAddUI(MEMBER*mem)
{
	//参数合法性检查
	if (NULL == mem)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	MemManageUI();
	//输出会员基本信息数据提示头
	printf("\t\t\t\t\t*           会员号:                     *\n");
	printf("\t\t\t\t\t*            姓名:                      *\n");
	printf("\t\t\t\t\t*            积分：                     *\n");
	printf("\t\t\t\t\t*****************************************\n");
	//录入会员基本信息
	GoToXY(M_Row +9+ 1, 60);
	scanf("%llu", &mem->memID);
	GoToXY(M_Row +9+ 2, 60);
	scanf("%s", mem->memname);
	GoToXY(M_Row +9+ 3, 60);
	scanf("%d", &mem->mempoint);
	Time(&mem->memdate);
}

//会员链表的尾添加
int MemAddToLinkEnd(MNODE* mhead, MEMBER* mem)
{
	//参数合法性检查
	if (NULL == mhead || NULL == mem)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//申请节点内存
	MNODE* pTemp = (MNODE*)malloc(sizeof(MNODE));
	if (NULL == pTemp)
	{
		GoToXY(0, 0);
		printf("No enough memory!");
		return 0;
	}
	//成员赋值
	InitialMem(pTemp);
	pTemp->data = *mem;
	mhead->count++;
	//将新节点添加进有空头双向链表中
	pTemp->pNext = mhead;
	pTemp->pPre = mhead->pPre;
	mhead->pPre->pNext = pTemp;
	mhead->pPre = pTemp;
	return 1;
}

//按会员号冒泡排序
void SortByMomIDBubble(MNODE* mhead)
{
	//参数合法性检查
	if (NULL == mhead || 0 == mhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//冒泡排序
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

//会员链表的查询
int MemSearch(MNODE* mhead, MEMBER* mem)
{
	//参数合法性检查
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

//会员信息的修改
void MemCorrect(MNODE* mhead, MEMBER* mem)
{
	//参数合法性检查
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
			//输出会员基本信息数据提示头
			printf("\t\t\t\t\t*           会员号:                     *\n");
			printf("\t\t\t\t\t*            姓名:                      *\n");
			printf("\t\t\t\t\t*            积分：                     *\n");
			printf("\t\t\t\t\t*****************************************\n");
			//录入会员基本信息
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

//会员链表的节点删除
void MemDelete(MNODE* mhead, MEMBER* mem)
{
	//参数合法性检查
	if (NULL == mhead || 0 == mhead->count || NULL == mem)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	//遍历链表查找
	MNODE* pTemp = mhead->pNext;
	while (pTemp != mhead)
	{
		if (0 == strcmp(pTemp->data.memname, mem->memname) || pTemp->data.memID == mem->memID)
		{
			MNODE* pT = pTemp;
			pTemp = pTemp->pNext;
			//数量减一
			mhead->count--;
			//删除节点
			pT->pPre->pNext = pT->pNext;
			pT->pNext->pPre = pT->pPre;
			free(pT);
			return ;
		}
		pTemp = pTemp->pNext;
	}
	return ;
}

//从文件中读取会员数据
void MenReadfromFile(MNODE* mhead)
{
	if (NULL == mhead)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("member.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open member.dat!");
		return;
	}
	//遍历链表写入文件
	MEMBER pTemp;
	while (0 != fread(&pTemp, sizeof(MEMBER), 1, pFile))
	{
		MemAddToLinkEnd(mhead, &pTemp);
	}
	//关闭文件
	fclose(pFile);
}

//把链表中会员信息保存进文件
void MemSaveInFile(MNODE* mhead)
{
	//参数合法性检查
	if (NULL == mhead )
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("member.dat", "w")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open member.dat!");
		return;
	}
	//遍历链表写入文件
	
	MNODE* pTemp = mhead->pNext;
	while (pTemp != mhead)
	{
		fwrite(&(pTemp->data), sizeof(MEMBER), 1, pFile);
		pTemp = pTemp->pNext;
	}
	//关闭文件
	fclose(pFile);
}

//初始化会员链表节点
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

//释放会员链表占用的内存空间
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

//书籍管理页面
void BookManageUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         图书管理系统>>书籍管理        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              输入指令：               *\n");
	printf("\t\t\t\t\t*             0、返回主菜单             *\n");
	printf("\t\t\t\t\t*             1、显示书目               *\n");
	printf("\t\t\t\t\t*             2、添加书目               *\n");
	printf("\t\t\t\t\t*             3、修改书目               *\n");
	printf("\t\t\t\t\t*             4、删除书目               *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//打印所有书籍信息
int PrintAllBook(BNODE* bhead)
{
	//参数合法性检查
	if (NULL == bhead || 0 == bhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//输出数据提示头
	printf("\t\t     *******************************************************************************\n");
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	printf("\t\t     * 图书号     图书名           进货价 销售价 折扣价 库存        添加日期       *\n");
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	//循环链表
	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		printf("\t\t     * %-11llu%-18s%-7d%-7d%-6d%-7d%04d\\%02d\\%02d %02d:%02d:%02d *\n",pTemp->data.bookID,pTemp->data.bookname,pTemp->data.bookinput,pTemp->data.bookoutput,pTemp->data.bookdiscount,pTemp->data.stock,
			pTemp->data.bookdate.year, pTemp->data.bookdate.month, pTemp->data.bookdate.day, pTemp->data.bookdate.hour, pTemp->data.bookdate.min, pTemp->data.bookdate.sec);
		pTemp = pTemp->pNext;
	}
	//数据结尾
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	printf("\t\t     *******************************************************************************\n");
	return 1;
}

//书籍查询界面
void BookSearchUI(BOOK* book)
{
	BookManageUI();
	GoToXY(M_Row + 9 + 1, 0);
	printf("\t\t\t\t\t*            请输入搜索方式：           *\n");
	printf("\t\t\t\t\t*    1、按图书号搜索   2、按书名搜索    *\n");
	printf("\t\t\t\t\t*****************************************\n");
	while (1)
	{
		GoToXY(M_Row + 9 + 1, 69);
		int temp = -1;
		scanf("%d", &temp);
		if (1 == temp)
		{
			GoToXY(M_Row + 9 + 3 + 1, 0);
			printf("\t\t\t\t\t*           搜索图书号：                *\n");
			printf("\t\t\t\t\t*****************************************\n");
			GoToXY(M_Row + 9 + 3 + 1, 64);
			scanf("%llu", &book->bookID);
			break;
		}
		else if (2 == temp)
		{
			GoToXY(M_Row + 9 + 3 + 1, 0);
			printf("\t\t\t\t\t*           搜索书名：                  *\n");
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
			printf("\t\t\t\t\t*            请输入搜索方式：           *\n");
			printf("\t\t\t\t\t*    1、按图书号搜索   2、按书名搜索    *\n");
			printf("\t\t\t\t\t*****************************************\n");
			OrderWrongUI(M_Row + 9 + 3 + 1);
		}
	}
	return;
}

//无书目信息
void NonBook(void)
{
	GoToXY(M_Row + 9 + 1, 0);
	printf("\t\t\t\t\t*             无书目信息!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//操作成功界面
void BookSucceedToDoUI(void)
{
	printf("\t\t\t\t\t*               操作成功!!!             *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//书籍添加界面
void BookAddUI(BOOK* book)
{
	//参数合法性检查
	if (NULL == book)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	BookManageUI();
	//输出会员基本信息数据提示头
	printf("\t\t\t\t\t*           图书号：                    *\n");
	printf("\t\t\t\t\t*           图书名：                    *\n");
	printf("\t\t\t\t\t*           进货价：                    *\n");
	printf("\t\t\t\t\t*           销售价：                    *\n");
	printf("\t\t\t\t\t*           存货量：                    *\n");
	printf("\t\t\t\t\t*****************************************\n");
	//录入会员基本信息
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

//书籍链表的尾添加
int BookAddToLinkEnd(BNODE* bhead, BOOK* book)
{
	//参数合法性检查
	if (NULL == bhead || NULL == book)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//申请节点内存
	BNODE* pTemp = (BNODE*)malloc(sizeof(BNODE));
	if (NULL == pTemp)
	{
		GoToXY(0, 0);
		printf("No enough memory!");
		return 0;
	}
	//成员赋值
	InitialBook(pTemp);
	pTemp->data = *book;
	bhead->count++;
	//将新节点添加进有空头双向链表中
	pTemp->pNext = bhead;
	pTemp->pPre = bhead->pPre;
	bhead->pPre->pNext = pTemp;
	bhead->pPre = pTemp;
	return 1;
}

//按书籍编号冒泡排序
void SortByBookIDBubble(BNODE* bhead)
{
	//参数合法性检查
	if (NULL == bhead || 0 == bhead->count)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//冒泡排序
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

//书籍链表的查询
int BookSearch(BNODE* bhead, BOOK* book)
{
	//参数合法性检查
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

//书籍信息的修改
void BookCorrect(BNODE* bhead, BOOK* book)
{
	//参数合法性检查
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
			//输出会员基本信息数据提示头
			printf("\t\t\t\t\t*           图书号：                    *\n");
			printf("\t\t\t\t\t*           图书名：                    *\n");
			printf("\t\t\t\t\t*           进货价：                    *\n");
			printf("\t\t\t\t\t*           销售价：                    *\n");
			printf("\t\t\t\t\t*           存货量：                    *\n");
			printf("\t\t\t\t\t*****************************************\n");
			//录入会员基本信息
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

//书籍链表的节点删除
void BookDelete(BNODE* bhead, BOOK* book)
{
	//参数合法性检查
	if (NULL == bhead || 0 == bhead->count || NULL == book)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return ;
	}
	//遍历链表查找
	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		if (0 == strcmp(pTemp->data.bookname, book->bookname) || pTemp->data.bookID == book->bookID)
		{
			BNODE* pT = pTemp;
			pTemp = pTemp->pNext;
			//数量减一
			bhead->count--;
			//删除节点
			pT->pPre->pNext = pT->pNext;
			pT->pNext->pPre = pT->pPre;
			free(pT);
			return;
		}
		pTemp = pTemp->pNext;
	}
	return;
}

//从文件中读取书籍数据
void BookReadfromFile(BNODE* bhead)
{
	if (NULL == bhead)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("book.dat", "r")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open book.dat!");
		return;
	}
	//遍历链表写入文件
	BOOK pTemp;
	while (0 != fread(&pTemp, sizeof(BOOK), 1, pFile))
	{
		BookAddToLinkEnd(bhead, &pTemp);
	}
	//关闭文件
	fclose(pFile);
}

//把链表中书籍信息保存进文件
void BookSaveInFile(BNODE* bhead)
{
	//参数合法性检查
	if (NULL == bhead )
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("book.dat", "w")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open book.dat!");
		return;
	}
	//遍历链表写入文件

	BNODE* pTemp = bhead->pNext;
	while (pTemp != bhead)
	{
		fwrite(&(pTemp->data), sizeof(BOOK), 1, pFile);
		pTemp = pTemp->pNext;
	}
	//关闭文件
	fclose(pFile);
}

//初始化书籍链表节点
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

//释放书籍链表占用的内存空间
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

//购物结算界面
void Shop(BNODE*bhead,MNODE* mhead,BOOK* book, MEMBER* mem)
{
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         图书管理系统>>购物结算        *\n");
	PrintAllBook(bhead);
	printf("\t\t     *	请输入会员号：                                                             *\n");
	printf("\t\t     *******************************************************************************\n");
	while(1)
	{
		GoToXY(M_Row + bhead->count+7+1, 38);
		scanf("%llu", &mem->memID);
		if (!MemSearch(mhead, mem))
		{
			GoToXY(M_Row + bhead->count + 7 + 1, 0);
			printf("\t\t     *	请输入会员号：                                           无该会员信息！！  *\n");
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
	printf("\t\t     *	请输入图书号：                                                             *\n");
	printf("\t\t     *******************************************************************************\n");
	while (1)
	{
		GoToXY(M_Row + bhead->count + 9+ 1, 38);
		scanf("%llu", &book->bookID);
		if (!BookSearch(bhead, book))
		{
			GoToXY(M_Row + bhead->count + 9 + 1, 0);
			printf("\t\t     *	请输入图书号：                                           无该图书信息！！  *\n");
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
	printf("\t\t     *	请输入购买量：                                                             *\n");
	printf("\t\t     *******************************************************************************\n");
	while (1)
	{
		GoToXY(M_Row + bhead->count + 11 + 1, 38);
		scanf("%d",&temp);
		sum = temp * (tbook->bookoutput);				//书籍原价
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
			printf("\t\t     *	请输入购买量：                                           该图书不足！！    *\n");
			printf("\t\t     *******************************************************************************\n");
			char c = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		else if (actual > tmem->mempoint)
		{
			GoToXY(M_Row + bhead->count + 11 + 1, 0);
			printf("\t\t     *	请输入购买量：                                           该会员积分不足！！*\n");
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
			printf("\t\t     *	                              购买成功！！！                               *\n");
			printf("\t\t     *******************************************************************************\n");
			break;
		}
	}

}

//数据统计
void LookAllStatic(void)
{
	//输出数据提示头
	printf("\t\t     *******************************************************************************\n");
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	printf("\t\t     * 购买会员 购买书目  购买数量 进货价 销售价 折扣价 利润        购买日期       *\n");
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	//循环链表
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
	printf("\t\t     *                                  总利润：%-7d                            *\n",sum);
	//数据结尾
	printf("\t\t     *-----------------------------------------------------------------------------*\n");
	printf("\t\t     *******************************************************************************\n");
	return ;
}

//销售策略制定界面
void SellStrategyUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         图书管理系统>>销售策略        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              输入指令：               *\n");
	printf("\t\t\t\t\t*             0、返回主菜单             *\n");
	printf("\t\t\t\t\t*             1、书籍降价               *\n");
	printf("\t\t\t\t\t*             2、总价满减               *\n");
	printf("\t\t\t\t\t*             3、清除策略               *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//书籍降价
void BookDiscount(void)
{
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*         价格从 %-4d 下降为            *\n",tbook->bookoutput);
	printf("\t\t\t\t\t*****************************************\n");
}

//书籍降价查询界面
void BookDisSearchUI(BOOK* book)
{
	SellStrategyUI();
	GoToXY(M_Row + 8 + 1, 0);
	printf("\t\t\t\t\t*            请输入搜索方式：           *\n");
	printf("\t\t\t\t\t*    1、按图书号搜索   2、按书名搜索    *\n");
	printf("\t\t\t\t\t*****************************************\n");
	while (1)
	{
		GoToXY(M_Row + 8 + 1, 69);
		int temp = -1;
		scanf("%d", &temp);
		if (1 == temp)
		{
			GoToXY(M_Row + 8 + 3 + 1, 0);
			printf("\t\t\t\t\t*           搜索图书号：                *\n");
			printf("\t\t\t\t\t*****************************************\n");
			GoToXY(M_Row + 8 + 3 + 1, 64);
			scanf("%llu", &book->bookID);
			break;
		}
		else if (2 == temp)
		{
			GoToXY(M_Row + 8 + 3 + 1, 0);
			printf("\t\t\t\t\t*           搜索书名：                  *\n");
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
			printf("\t\t\t\t\t*            请输入搜索方式：           *\n");
			printf("\t\t\t\t\t*    1、按图书号搜索   2、按书名搜索    *\n");
			printf("\t\t\t\t\t*****************************************\n");
			OrderWrongUI(M_Row + 8 + 3 + 1);
		}
	}
	return;
}

//总价满减
void FullMinus(void)
{

	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*           每满        减              *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//清除所有策略
void CleanAllStrategy(BNODE* bhead)
{
	discount[0] = discount[1] = 0;
	//参数合法性检查
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

//用户管理菜单
void UserManageUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         图书管理系统>>用户管理        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              输入指令：               *\n");
	printf("\t\t\t\t\t*            0、返回主菜单              *\n");
	printf("\t\t\t\t\t*            1、查看所有用户            *\n");
	printf("\t\t\t\t\t*            2、添加普通用户            *\n");
	printf("\t\t\t\t\t*            3、添加高级用户            *\n");
	//printf("\t\t\t\t\t*            4、删除用户                *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//查看所有用户
void LookAllUser(void)
{
	ManageMenuUI();
	UserManageUI();
	GoToXY(M_Row + 8, 0);
	//输出数据提示头
	printf("\t\t\t\t    *************************************************\n");
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	printf("\t\t\t\t    *   用户属性    账号            密码            *\n");
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("User.dat", "rb")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open User.dat\n");
		return ;
	}
	//循环读文件
	USER us = { 0 };
	while (fread(&us, sizeof(USER), 1, pFile) != 0)
	{
		char str[20];
		if (us.mark == 0) strcpy(str, "普通用户");
		else strcpy(str, "高级用户");
		Encryption(us.key);
		printf("\t\t\t\t    *   %s    %-16s%-16s*\n",str,us.name,us.key);
	}
	//数据结尾
	printf("\t\t\t\t    *-----------------------------------------------*\n");
	printf("\t\t\t\t    *************************************************\n");
	return ;
}

//添加用户
void AddUser(USER* user, int Mark)
{
	ManageMenuUI();
	UserManageUI();
	GoToXY(M_Row +8+ 1, 0);		//第10行位置开始输出
	printf("\t\t\t\t\t*           账号 :                      *\n");
	printf("\t\t\t\t\t*           密码 :                      *\n");
	printf("\t\t\t\t\t*****************************************\n");
	GoToXY(M_Row +8+ 1, 59);
	scanf("%s", user->name);
	GoToXY(M_Row +8+ 1 + 1, 59);
	scanf("%s", user->key);
	Encryption(user->key);
	user->mark = Mark;
}

//判断用户名是否存在
int IsUserExist(USER* user)
{
	if (NULL == user)
	{
		GoToXY(0, 0);
		printf("Illegal parameter!");
		return 0;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("User.dat", "rb")) == NULL)
	{
		GoToXY(0, 0);
		printf("Failure to open User.dat\n");
		return 0;
	}
	//循环读文件
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

//用户添加成功界面
void AddUserSuccess(void)
{
	printf("\t\t\t\t\t*              添加成功!!!              *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//用户添加失败
void AddUserFail(void)
{
	printf("\t\t\t\t\t*         添加失败，用户已存在!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//注册后，将账号密码存储进文件
void SaveUser(USER* user)
{
	if (NULL == user)
	{
		printf("Illegal parameter!");
		return;
	}
	//打开文件
	FILE* pFile;
	if ((pFile = fopen("User.dat", "ab")) == NULL)
	{
		printf("Failure to open User.dat\n");
		return;
	}
	//写入文件
	fwrite(user, sizeof(USER), 1, pFile);
	//关闭文件
	fclose(pFile);
}

////删除用户界面
//void DeleteUser(USER* user)
//{
//	ManageMenuUI();
//	UserManageUI();
//	GoToXY(M_Row + 9 + 1, 0);
//	while (1)
//	{
//			GoToXY(M_Row + 9 + 1, 0);
//			printf("\t\t\t\t\t*           搜索账号：                  *\n");
//			printf("\t\t\t\t\t*****************************************\n");
//			GoToXY(M_Row + 9+ 1, 62);
//			scanf("%s", user->name);
//			break;
//	}
//	return;
//}

////用户删除
//void UserDelete(USER* user)
//{
//
//	if (NULL == user)
//	{
//		GoToXY(0, 0);
//		printf("Illegal parameter!");
//		return ;
//	}
//	//打开文件
//	FILE* pFile;
//	if ((pFile = fopen("User.dat", "ab")) == NULL)
//	{
//		GoToXY(0, 0);
//		printf("Failure to open User.dat\n");
//		return ;
//	}
//	//循环读文件
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

//数据导出界面
void StaticToEXCELUI(void)
{
	ManageMenuUI();
	GoToXY(M_Row + 1, 0);
	printf("\t\t\t\t\t*         图书管理系统>>数据导出        *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*              输入指令：               *\n");
	printf("\t\t\t\t\t*            0、返回主菜单              *\n");
	printf("\t\t\t\t\t*            1、导出会员信息            *\n");
	printf("\t\t\t\t\t*            2、导出书籍信息            *\n");
	printf("\t\t\t\t\t*            3、导出销售信息            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//获取导出文件名称界面
void GetFileName(void)
{
	printf("\t\t\t\t\t*       请输入文件名称：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//将书籍信息导出到EXCEL表格
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
		//输出数据提示头
		fprintf(pF,"图书号\t图书名\t进货价\t销售价\t折扣价\t库存\t添加日期\n");
		//输出数据主体
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

//将会员信息导出到EXCEL表格
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
		//输出数据提示头
		fprintf(pF,"会员号\t姓名\t积分\t添加日期\n");
		//输出数据主体
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

//将销售记录导出到EXCEL表格
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
		//输出数据提示头
		fprintf(pF,"购买会员\t购买书目\t购买数量\t进货价\t销售价\t折扣价\t利润\t购买日期\n");
		//输出数据主体
		while (0 != fread(&buy, sizeof(BUYRECORD), 1, ipTemp))
		{
			fprintf(pF,"%s\t%s\t%d\t%d\t%d\t%d\t%d\t%04d\\%02d\\%02d %02d:%02d:%02d\n", buy.mem.memname, buy.book.bookname, buy.number, buy.primecost, buy.originprice, buy.actualprice, buy.profit,
				buy.buydate.year, buy.buydate.month, buy.buydate.day, buy.buydate.hour, buy.buydate.min, buy.buydate.sec);
			sum += buy.profit;
		}
		fprintf(pF, "总利润\t%d",sum);
	}
	fclose(pF);
	fclose(ipTemp);
	return;
}

//导出成功提示
void SuccessToExcel(void)
{
	printf("\t\t\t\t\t*            信息导出成功!!!            *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

//退出系统
void CancelUI(int iRow)
{
	GoToXY(iRow, 0);		//第iRow行位置开始输出
	printf("\t\t\t\t\t*         感谢使用，3 秒后注销!!!       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	CountDown(iRow, 60, 1000, 3);
}