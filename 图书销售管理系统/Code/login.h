//��¼����ͷ�ļ�
#pragma once
#include"common.h"
#define L_Row 10		//��¼�˵�����


//��¼����ͳ�ﺯ��
int Login(void);

//��¼���˵�
void LoginMenuUI(void);

//����Ƿ�����û���Ϣ
int ChackUser(void);

//д���ʼ�˺�����
void FirstUser(void);

//�û���¼����
void LoginUI(void);
//��¼ʧ����ʾ
void LoginFailUI(void);
//��¼�ɹ���ʾ
void LoginSuccessUI(void);

//�ж��û����������Ƿ���ȷ
int IsRight(USER* user);

//�˳�ϵͳ
void QuitUI(int iRow);