#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>  //
#include<assert.h>   //�������������еĴ���
#include<stdbool.h>

#define MAX_N 30  //������󳤶�
#define MAX_T 15  //�绰������󳤶�
#define MAX_A 100 //��ַ��󳤶�
#define MAX_H 100 //��ϣ����󳤶�
#define DIV (97)  //��ʾ����

typedef struct client    //����û���Ϣ�Ľṹ��
{
	char name[MAX_N];		//����
	char telephone[MAX_T];	//�绰����
	char address[MAX_A];	//��ַ
	int name_key;  //��Ӧ�����ֹ�ϣ��ַ
	int tele_key;  //��Ӧ�ĵ绰����Ĺ�ϣ��ַ
	int flag;      //������ʶ�Ƿ����ֹ�ϣ���λ���Ƿ��Ѿ���ͻ
}c_lient;   

typedef struct client_a {
	char name[MAX_N];		//����
	char telephone[MAX_T];	//�绰����
	char address[MAX_A];	//��ַ
	int tele_key;  //��Ӧ�ĵ绰��ϣ��ַ
	int name_key;
	int flag;      //������ʶ�Ƿ����ֹ�ϣ���λ���Ƿ��Ѿ���ͻ�� 1��ʾ������0��ʾ��λ�û�δ����
}client_tele;

	c_lient hash_name[MAX_H];//������ϣ��
	client_tele hash_tele[MAX_H]; //�绰��ϣ��



