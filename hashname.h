#pragma once

#include"main.h"

//c_lient hash_name[MAX_H];//姓名哈希表
//client_tele hash_tele[MAX_H]; //电话哈希表

bool name_isfull();

bool tele_isfull();

int method_name(int key);

int method_tele(int tele_key);

void addhash();

int inquire_name(char c_name[]);

int inquire_tele(char c_telephone[]);

void dele();

void change_name();  //根据用户输入的姓名进行修改

void change_tele();  //根据用户输入的电话号码进行修改

void read_();        //用户信息载入文件

void add_name();   //文件导入时用的导入函数

void add_tele();

void init();  //哈希表的初始化

void quit();  //退出函数

//通过公式算出来在姓名哈希表中的地址
int key_name(char c_name[]);

int key_tele(char c_telephone[]);

void SleepCls(); //睡眠加清屏

void ProgressBar(); //模拟进度条

void traverse(); //查看所有人的信息

void serve();  //显示用户信息

void clear();  //清空用户信息