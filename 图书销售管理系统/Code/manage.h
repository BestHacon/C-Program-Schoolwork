//管理界面头文件
#pragma once
#include"common.h"
#define M_Row 16		//管理菜单行数	

USER nowuser;

//储存时间的结构体
struct date
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
};		

//储存会员信息的结构体
typedef struct member
{
	unsigned long long memID;	//会员号
	char memname[30];			//姓名
	struct date memdate;		//添加日期
	int mempoint;				//积分

}MEMBER;

//声明会员的有空头双向循环链表节点
typedef struct memnode
{
	int count;					//会员数目
	MEMBER data;				//会员信息
	struct memnode* pPre;		//指向前一个节点的指针
	struct memnode* pNext;		//指向后一个节点的指针
}MNODE;

//储存书籍信息的结构体
typedef struct book
{
	unsigned long long bookID;	//图书号
	char bookname[50];			//图书名称
	struct date bookdate;		//添加日期
	int bookinput;				//进货价
	int bookoutput;				//销售价
	int bookdiscount;			//折扣价
	int stock;					//库存

}BOOK;

//声明书籍的有空头双向循环链表节点
typedef struct booknode
{
	int count;					//图书种类
	BOOK data;					//图书信息
	struct booknode* pPre;		//指向前一个节点的指针
	struct booknode* pNext;		//指向后一个节点的指针
}BNODE;

//声明储存购买记录的结构体
typedef struct buyrecord
{
	MEMBER mem;
	BOOK book;
	int number;
	int primecost;
	int originprice;
	int actualprice;
	int profit;
	struct date buydate;
}BUYRECORD;
BUYRECORD buy;

MEMBER* tmem;
BOOK* tbook;

//储存折扣信息
int discount[2];

//登录统筹函数
void Manege(void);

//管理主菜单
void ManageMenuUI(void);

//普通用户操作提示
void VisterNoticeUI(void);

//生成时间
void Time(struct date* iTime);

//会员管理菜单
void MemManageUI(void);
//打印所有会员信息
int PrintAllMen(MNODE* mhead);
//会员查询界面
void MemSearchUI(MEMBER* mem);
//查询失败界面
void SearchFailUI(void);
//无会员信息
void NonMem(void);
//操作成功界面
void MemSucceedToDoUI(void);
//会员添加界面
void MemAddUI(MEMBER* mem);

//会员链表的尾添加
int MemAddToLinkEnd(MNODE* mhead, MEMBER* mem);
//按会员号冒泡排序
void SortByMomIDBubble(MNODE* mhead);
//会员链表的查询
int MemSearch(MNODE* mhead, MEMBER* mem);
//会员信息的修改
void MemCorrect(MNODE* mhead, MEMBER* mem);
//会员链表的节点删除
void MemDelete(MNODE* mhead, MEMBER* mem);
//从文件中读取会员数据
void MenReadfromFile(MNODE* mhead);
//把链表中会员信息保存进文件
void MemSaveInFile(MNODE* mhead);
//初始化会员链表节点
void InitialMem(MNODE* mem);
//释放会员链表占用的内存空间
void FreeMem(MNODE* mhead);

//书籍管理页面
void BookManageUI(void);
//打印所有书籍信息
int PrintAllBook(BNODE* bhead);
//书籍查询界面
void BookSearchUI(BOOK* book);
//无书目信息
void NonBook(void);
//操作成功界面
void BookSucceedToDoUI(void);
//书籍添加界面
void BookAddUI(BOOK* book);

//书籍链表的尾添加
int BookAddToLinkEnd(BNODE* bhead, BOOK* book);
//按书籍编号冒泡排序
void SortByBookIDBubble(BNODE* bhead);
//书籍链表的查询
int BookSearch(BNODE* bhead, BOOK* book);
//书籍信息的修改
void BookCorrect(BNODE* bhead, BOOK* book);
//书籍链表的节点删除
void BookDelete(BNODE* bhead, BOOK* book);
//从文件中读取书籍数据
void BookReadfromFile(BNODE* bhead);
//把链表中书籍信息保存进文件
void BookSaveInFile(BNODE* bhead);
//初始化书籍链表节点
void InitialBook(BNODE* book);
//释放书籍链表占用的内存空间
void FreeBook(BNODE* bhead);

//购物结算界面
void Shop(BNODE* bhead,MNODE*mhead,BOOK *book,MEMBER *mem);

//数据统计
void LookAllStatic(void);

//销售策略制定界面
void SellStrategyUI(void);
//书籍降价
void BookDiscount(void);
//书籍降价查询界面
void BookDisSearchUI(BOOK* book);
//总价满减
void FullMinus(void);
//清除所有策略
void CleanAllStrategy(BNODE* bhead);

//用户管理菜单
void UserManageUI(void);
//查看所有用户
void LookAllUser(void);
//添加用户
void AddUser(USER* user,int Mark);
//判断用户名是否存在
int IsUserExist(USER* user);
//用户添加成功界面
void AddUserSuccess(void);
//用户添加失败
void AddUserFail(void);
//注册后，将账号密码存储进文件
void SaveUser(USER* user);
//删除用户界面
void DeleteUser(USER* user);
//用户删除
void UserDelete(USER* user);
//数据导出界面
void StaticToEXCELUI(void);
//获取导出文件名称界面
void GetFileName(void);
//将书籍信息导出到EXCEL表格
void BookToEXCEL(BNODE* book, char* str);
//将会员信息导出到EXCEL表格
void MenToEXCEL(MNODE* mem, char* str);
//将销售记录导出到EXCEL表格
void RecordToEXCEL(char* str);
//导出成功提示
void SuccessToExcel(void);
//注销并退出
void CancelUI(int iRow);