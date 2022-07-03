//�������ͷ�ļ�
#pragma once
#include"common.h"
#define M_Row 18		//����˵�����
#define M 6			    //��Ŀ��������

int m;					//ʵ�ʿ�Ŀ����

char subject[6][40];	//�����Ŀ��Ϣ��ȫ�ֱ���
double subsco[6][3];		//�����Ŀ�ɼ���ȫ�ֱ���

struct date
{
	int year;
	int month;
	int day;
};		//����

//��������ѧ����Ϣ�Ľṹ��
typedef struct student
{
	char class[25];				//�༶
	unsigned long long stuID;	//ѧ��
	char stuName[25];			//����
	char stuSex[10];			//�Ա�
	struct date birthday;		//��������
	int score[M];				//M�ſγ̳ɼ�
	int sum;					//�ܷ�
	double aver;				//ƽ����
}STUDENT;

//�����п�ͷ˫��ѭ������ڵ�
typedef struct node
{
	int count;				//ѧ����Ŀ
	STUDENT data;			//ѧ����Ϣ
	struct node* pPre;		//ָ��ǰһ���ڵ��ָ��
	struct node* pNext;		//ָ���һ���ڵ��ָ��
}NODE;

//��¼ͳ�ﺯ��
void Manege(void);

//�������˵�
void ManageMenuUI(void);

//����Ƿ������Ŀ��Ϣ
int ChackSubject(void);
//�޿�Ŀ��Ϣ��ʾ
void SubjectWrongUI(void);
//��Ŀ��Ϣ¼��
int AddSubject(int iLine);
//��Ϣ¼��ɹ���ʾ
void AddSubjectSuccessUI(void);
//��Ϣ¼��ʧ����ʾ
void AddSubjectFailUI(void);
//�����Ŀ��Ϣ���ļ�
void SaveSubjectToFile(int m);
//���ļ��ж�ȡ��Ŀ��Ϣ
int ReadSubjectFromFile(void);
//���Ŀ�Ŀ��Ϣ��ʾ
int ChangSubjectUI(void);

//ͳ�ƿ�Ŀ��Ϣ
void SubjectStatistic(NODE* head);
//��ӡ��Ŀ��Ϣ
void PrintSubject(NODE* head);

//�ο͵�¼��ʾ
void VisterNoticeUI(void);

//���ѧ����Ϣ
void AddStu(STUDENT* stu);
//���ѧ����Ϣ�ɹ���ʾ
void AddStuSuccessUI(void);
//���ѧ����Ϣʧ����ʾ
void AddStuFailUI(void);
//˫��ѭ������ڵ�ĳ�ʼ��
void Initialization(NODE* node);
//�����β���
int AddToLinkEnd(NODE*head,STUDENT*stu);

//��������ѧ����Ϣ������ļ�
void SaveInFile(NODE* head);
//����ɹ���ʾ
void SaveInFileSuccessUI(void);

//���ļ��ж�ȡ���ݵ�����
void ReadfromFile(NODE* head);

//����ָ��ѧ�����ֽ���
int OneStuNameUI(void);

//����ѧ���Ƿ����
int Seekone(NODE* head, STUDENT* stu);

//��ʾָ��ѧ��
void LookOne(NODE* head, STUDENT* stu);

//�鿴����ѧ����Ϣ
void LookAll(NODE* head, int Boo);

//�鿴��ʽ����
void LookWayUI(void);

//�޸�ָ��ѧ����Ϣ
void Change(NODE* head, STUDENT* stu);
//�޸ĳɹ���ʾ
void ChangeSuccessUI(void);
//�޸�ʧ����ʾ
void SearchFailUI(void);

//ɾ��ָ��ѧ��
int Deleteone(NODE* head, STUDENT* stu);
//ɾ���ɹ���ʾ
void DeleteSuccessUI(void);

//�༶�ɼ���ѯ����
void ClassSearchUI(void);
//�༶�ɼ���ѯʧ��
void ClassSearchFailUI(void);
//�༶�ɼ������ӡ
int ClassPrint(NODE* head, char Class[]);

//��ѧ��ð������
void SortByIDBubble(NODE* head);
//���ܳɼ�ð������
void SortByScoreBubble(NODE*head);
//����Ŀ�ɼ�ð������
void SortBySubjectBubble(NODE* head,int subnum);
//����Ŀ����ѡ�����
void SortBySubjectUI(void);
//����ɹ���ʾ
void SortSuccessUI(void);

//������Ϣ��EXCEL���
int ExportToXls(NODE* head);
//�����ɹ���ʾ
void ExportToXlsSuccessUI(void);
//û��ѧ����Ϣ��ʾ
void NoneNoticeUI(void);

//�ͷ�����ռ�õ��ڴ�ռ�
void Free(NODE* head);

//ע�����˳�
void CancelUI(int iRow);