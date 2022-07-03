//��¼����ͷ�ļ�
#pragma once
#include"common.h"
#define L_Row 12		//��¼�˵�����


//��¼����ͳ�ﺯ��
int Login(void);

//��¼���˵�
void LoginMenuUI(void);

//�ο͵�¼
void VisterLoginUI(void);

//�û���¼����
void LoginUI(void);
//��¼ʧ����ʾ
void LoginFailUI(void);
//��¼�ɹ���ʾ
void LoginSuccessUI(void);

//�û�ע�����
void RegisterUI(void);
//ע��ʧ����ʾ
void RegisterFailUI(void);
//ע��ɹ���ʾ
void RegisterSuccessUI(void);

//ע��󣬽��˺�����洢���ļ�
void SaveUser(USER* user);

//�ж��û����������Ƿ���ȷ
int IsRight(USER* user);
//�ж��û����Ƿ���ڣ���¼��Ҫ��ע����Ҫ��
int IsUserExist(struct User* user);

//�˳�ϵͳ
void QuitUI(int iRow);