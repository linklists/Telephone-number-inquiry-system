#pragma once
#include "configure.h"

class user
{
public:
	user();

	user(string name, string telephone, string address);

	static user FromString(const string& str);

	string name;		//����
	string telephone;	//�绰����
	string address;		//��ַ
	int name_key;		//��Ӧ�����ֹ�ϣ��ַ
	int tele_key;		//��Ӧ�ĵ绰����Ĺ�ϣ��ַ
	int flag;			//������ʶ�Ƿ����ֹ�ϣ���λ���Ƿ��Ѿ���ͻ
};

