#pragma once

#include"main.h"

//c_lient hash_name[MAX_H];//������ϣ��
//client_tele hash_tele[MAX_H]; //�绰��ϣ��

bool name_isfull();

bool tele_isfull();

int method_name(int key);

int method_tele(int tele_key);

void addhash();

int inquire_name(char c_name[]);

int inquire_tele(char c_telephone[]);

void dele();

void change_name();  //�����û���������������޸�

void change_tele();  //�����û�����ĵ绰��������޸�

void read_();        //�û���Ϣ�����ļ�

void add_name();   //�ļ�����ʱ�õĵ��뺯��

void add_tele();

void init();  //��ϣ��ĳ�ʼ��

void quit();  //�˳�����

//ͨ����ʽ�������������ϣ���еĵ�ַ
int key_name(char c_name[]);

int key_tele(char c_telephone[]);

void SleepCls(); //˯�߼�����

void ProgressBar(); //ģ�������

void traverse(); //�鿴�����˵���Ϣ

void serve();  //��ʾ�û���Ϣ

void clear();  //����û���Ϣ