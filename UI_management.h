#pragma once
#include "UI_window.h"
#include "PushButton.h"
#include "user.h"
#include "Table.h"
#include "LineEdit.h"

class UI_management
{
public:
	UI_management();

	//启动管理类
	void run();

	//主页面（菜单）
	int menu();

	//0.添加
	void add();

	//1.删除
	void earse();

	//2.修改
	void modify();

	//3.按姓名查找
	void SearchByName();

	//4.按电话号码查找
	void SearchByTele();

	//5.查看所有信息（管理员）
	void traverse();

	//6.显示当前容量(系统存储的人数)（管理员）
	void surplus();

	//7.清空所有信息（管理员）
	void clearall();

	//8.退出系统

	void ChangeByName(int location);

	void CHangeByTele(int location);

	//绘制背景
	void DrawBackground();

	void EventLoop();

	//姓名哈希表、号码哈希表初始化
	void init(); 

	bool name_isfull();

	bool tele_isfull();

	//计算姓名的键值
	int key_name(string name);

	//计算号码的键值
	int key_tele(string telephone);

	//线性探测法
	int method_name(int key);

	//线性探测法
	int method_tele(int key);

	//以姓名、号码为键值，将文件上的信息载入临时变量
	void LoadFile(const string& filename);

	//将临时变量中的数据存入文件
	void SaveFile(const string& filename);

	//以名字为键值查找，存在则返回位置索引，不存在则返回负数
	int inquire_name(string name);

	//以电话号码为键值查找，存在则返回位置索引，不存在则返回负数
	int inquire_tele(string telephone);

	void UpdateShowTable();

private:
	int op;
	IMAGE bk;
	vector<unique_ptr<PushButton>> menu_buttons;

	string header_str;

	user hash_name[MAX_H];
	user hash_tele[MAX_H];

	//查看用户表格
	unique_ptr<Table> ShowTable;
	//添加用户按钮
	unique_ptr<PushButton> AddButton;
	unique_ptr<LineEdit> AddEdit;
	//删除用户按钮
	unique_ptr<PushButton> DeleteButton;
	unique_ptr<LineEdit> DeleteEdit;
	unique_ptr<Table> DeleteTable;
	//修改联系人
	//unique_ptr<PushButton> ModifyButton;
	unique_ptr<LineEdit> ModifyEdit;
	vector<unique_ptr<LineEdit>> UserEdit;
	bool isFind = false;
	vector<user> ModifyIt;
	int location;
	//按姓名查询用户按钮
	unique_ptr<PushButton> SearchNameButton;
	unique_ptr<LineEdit> SearchNameEdit;
	//按电话号码查询用户按钮
	unique_ptr<PushButton> SearchTeleButton;
	unique_ptr<LineEdit> SearchTeleEdit;
	//显示余量
	unique_ptr<PushButton> ShowSurplusButton;
	//清空文件
	unique_ptr<PushButton> ClearButton;
};

