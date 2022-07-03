//�������ͷ�ļ�
#pragma once
#include"common.h"
#define M_Row 16		//����˵�����	

USER nowuser;

//����ʱ��Ľṹ��
struct date
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
};		

//�����Ա��Ϣ�Ľṹ��
typedef struct member
{
	unsigned long long memID;	//��Ա��
	char memname[30];			//����
	struct date memdate;		//�������
	int mempoint;				//����

}MEMBER;

//������Ա���п�ͷ˫��ѭ������ڵ�
typedef struct memnode
{
	int count;					//��Ա��Ŀ
	MEMBER data;				//��Ա��Ϣ
	struct memnode* pPre;		//ָ��ǰһ���ڵ��ָ��
	struct memnode* pNext;		//ָ���һ���ڵ��ָ��
}MNODE;

//�����鼮��Ϣ�Ľṹ��
typedef struct book
{
	unsigned long long bookID;	//ͼ���
	char bookname[50];			//ͼ������
	struct date bookdate;		//�������
	int bookinput;				//������
	int bookoutput;				//���ۼ�
	int bookdiscount;			//�ۿۼ�
	int stock;					//���

}BOOK;

//�����鼮���п�ͷ˫��ѭ������ڵ�
typedef struct booknode
{
	int count;					//ͼ������
	BOOK data;					//ͼ����Ϣ
	struct booknode* pPre;		//ָ��ǰһ���ڵ��ָ��
	struct booknode* pNext;		//ָ���һ���ڵ��ָ��
}BNODE;

//�������湺���¼�Ľṹ��
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

//�����ۿ���Ϣ
int discount[2];

//��¼ͳ�ﺯ��
void Manege(void);

//�������˵�
void ManageMenuUI(void);

//��ͨ�û�������ʾ
void VisterNoticeUI(void);

//����ʱ��
void Time(struct date* iTime);

//��Ա����˵�
void MemManageUI(void);
//��ӡ���л�Ա��Ϣ
int PrintAllMen(MNODE* mhead);
//��Ա��ѯ����
void MemSearchUI(MEMBER* mem);
//��ѯʧ�ܽ���
void SearchFailUI(void);
//�޻�Ա��Ϣ
void NonMem(void);
//�����ɹ�����
void MemSucceedToDoUI(void);
//��Ա��ӽ���
void MemAddUI(MEMBER* mem);

//��Ա�����β���
int MemAddToLinkEnd(MNODE* mhead, MEMBER* mem);
//����Ա��ð������
void SortByMomIDBubble(MNODE* mhead);
//��Ա����Ĳ�ѯ
int MemSearch(MNODE* mhead, MEMBER* mem);
//��Ա��Ϣ���޸�
void MemCorrect(MNODE* mhead, MEMBER* mem);
//��Ա����Ľڵ�ɾ��
void MemDelete(MNODE* mhead, MEMBER* mem);
//���ļ��ж�ȡ��Ա����
void MenReadfromFile(MNODE* mhead);
//�������л�Ա��Ϣ������ļ�
void MemSaveInFile(MNODE* mhead);
//��ʼ����Ա����ڵ�
void InitialMem(MNODE* mem);
//�ͷŻ�Ա����ռ�õ��ڴ�ռ�
void FreeMem(MNODE* mhead);

//�鼮����ҳ��
void BookManageUI(void);
//��ӡ�����鼮��Ϣ
int PrintAllBook(BNODE* bhead);
//�鼮��ѯ����
void BookSearchUI(BOOK* book);
//����Ŀ��Ϣ
void NonBook(void);
//�����ɹ�����
void BookSucceedToDoUI(void);
//�鼮��ӽ���
void BookAddUI(BOOK* book);

//�鼮�����β���
int BookAddToLinkEnd(BNODE* bhead, BOOK* book);
//���鼮���ð������
void SortByBookIDBubble(BNODE* bhead);
//�鼮����Ĳ�ѯ
int BookSearch(BNODE* bhead, BOOK* book);
//�鼮��Ϣ���޸�
void BookCorrect(BNODE* bhead, BOOK* book);
//�鼮����Ľڵ�ɾ��
void BookDelete(BNODE* bhead, BOOK* book);
//���ļ��ж�ȡ�鼮����
void BookReadfromFile(BNODE* bhead);
//���������鼮��Ϣ������ļ�
void BookSaveInFile(BNODE* bhead);
//��ʼ���鼮����ڵ�
void InitialBook(BNODE* book);
//�ͷ��鼮����ռ�õ��ڴ�ռ�
void FreeBook(BNODE* bhead);

//����������
void Shop(BNODE* bhead,MNODE*mhead,BOOK *book,MEMBER *mem);

//����ͳ��
void LookAllStatic(void);

//���۲����ƶ�����
void SellStrategyUI(void);
//�鼮����
void BookDiscount(void);
//�鼮���۲�ѯ����
void BookDisSearchUI(BOOK* book);
//�ܼ�����
void FullMinus(void);
//������в���
void CleanAllStrategy(BNODE* bhead);

//�û�����˵�
void UserManageUI(void);
//�鿴�����û�
void LookAllUser(void);
//����û�
void AddUser(USER* user,int Mark);
//�ж��û����Ƿ����
int IsUserExist(USER* user);
//�û���ӳɹ�����
void AddUserSuccess(void);
//�û����ʧ��
void AddUserFail(void);
//ע��󣬽��˺�����洢���ļ�
void SaveUser(USER* user);
//ɾ���û�����
void DeleteUser(USER* user);
//�û�ɾ��
void UserDelete(USER* user);
//���ݵ�������
void StaticToEXCELUI(void);
//��ȡ�����ļ����ƽ���
void GetFileName(void);
//���鼮��Ϣ������EXCEL���
void BookToEXCEL(BNODE* book, char* str);
//����Ա��Ϣ������EXCEL���
void MenToEXCEL(MNODE* mem, char* str);
//�����ۼ�¼������EXCEL���
void RecordToEXCEL(char* str);
//�����ɹ���ʾ
void SuccessToExcel(void);
//ע�����˳�
void CancelUI(int iRow);