//管理界面头文件
#pragma once
#include"common.h"
#define M_Row 18		//管理菜单行数
#define M 6			    //科目数量上限

int m;					//实际科目数量

char subject[6][40];	//储存科目信息的全局变量
double subsco[6][3];		//储存科目成绩的全局变量

struct date
{
	int year;
	int month;
	int day;
};		//日期

//声明储存学生信息的结构体
typedef struct student
{
	char class[25];				//班级
	unsigned long long stuID;	//学号
	char stuName[25];			//姓名
	char stuSex[10];			//性别
	struct date birthday;		//出生日期
	int score[M];				//M门课程成绩
	int sum;					//总分
	double aver;				//平均分
}STUDENT;

//声明有空头双向循环链表节点
typedef struct node
{
	int count;				//学生数目
	STUDENT data;			//学生信息
	struct node* pPre;		//指向前一个节点的指针
	struct node* pNext;		//指向后一个节点的指针
}NODE;

//登录统筹函数
void Manege(void);

//管理主菜单
void ManageMenuUI(void);

//检查是否输入科目信息
int ChackSubject(void);
//无科目信息提示
void SubjectWrongUI(void);
//科目信息录入
int AddSubject(int iLine);
//信息录入成功提示
void AddSubjectSuccessUI(void);
//信息录入失败提示
void AddSubjectFailUI(void);
//保存科目信息进文件
void SaveSubjectToFile(int m);
//从文件中读取科目信息
int ReadSubjectFromFile(void);
//更改科目信息提示
int ChangSubjectUI(void);

//统计科目信息
void SubjectStatistic(NODE* head);
//打印科目信息
void PrintSubject(NODE* head);

//游客登录提示
void VisterNoticeUI(void);

//添加学生信息
void AddStu(STUDENT* stu);
//添加学生信息成功提示
void AddStuSuccessUI(void);
//添加学生信息失败提示
void AddStuFailUI(void);
//双向循环链表节点的初始化
void Initialization(NODE* node);
//链表的尾添加
int AddToLinkEnd(NODE*head,STUDENT*stu);

//把链表中学生信息保存进文件
void SaveInFile(NODE* head);
//保存成功提示
void SaveInFileSuccessUI(void);

//从文件中读取数据到链表
void ReadfromFile(NODE* head);

//搜索指定学生名字界面
int OneStuNameUI(void);

//搜索学生是否存在
int Seekone(NODE* head, STUDENT* stu);

//显示指定学生
void LookOne(NODE* head, STUDENT* stu);

//查看所有学生信息
void LookAll(NODE* head, int Boo);

//查看方式界面
void LookWayUI(void);

//修改指定学生信息
void Change(NODE* head, STUDENT* stu);
//修改成功提示
void ChangeSuccessUI(void);
//修改失败提示
void SearchFailUI(void);

//删除指定学生
int Deleteone(NODE* head, STUDENT* stu);
//删除成功提示
void DeleteSuccessUI(void);

//班级成绩查询界面
void ClassSearchUI(void);
//班级成绩查询失败
void ClassSearchFailUI(void);
//班级成绩程序打印
int ClassPrint(NODE* head, char Class[]);

//按学号冒泡排序
void SortByIDBubble(NODE* head);
//按总成绩冒泡排序
void SortByScoreBubble(NODE*head);
//按科目成绩冒泡排序
void SortBySubjectBubble(NODE* head,int subnum);
//按科目排序选择界面
void SortBySubjectUI(void);
//排序成功提示
void SortSuccessUI(void);

//导出信息到EXCEL表格
int ExportToXls(NODE* head);
//导出成功提示
void ExportToXlsSuccessUI(void);
//没有学生信息提示
void NoneNoticeUI(void);

//释放链表占用的内存空间
void Free(NODE* head);

//注销并退出
void CancelUI(int iRow);