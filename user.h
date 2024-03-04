#pragma once
#include "configure.h"

class user
{
public:
	user();

	user(string name, string telephone, string address);

	static user FromString(const string& str);

	string name;		//姓名
	string telephone;	//电话号码
	string address;		//地址
	int name_key;		//对应的名字哈希地址
	int tele_key;		//对应的电话号码的哈希地址
	int flag;			//用来标识是否名字哈希表的位置是否已经冲突
};

