#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>  //
#include<assert.h>   //用来来检查程序中的错误
#include<stdbool.h>

#define MAX_N 30  //姓名最大长度
#define MAX_T 15  //电话号码最大长度
#define MAX_A 100 //地址最大长度
#define MAX_H 100 //哈希表最大长度
#define DIV (97)  //表示除数

typedef struct client    //存放用户信息的结构体
{
	char name[MAX_N];		//姓名
	char telephone[MAX_T];	//电话号码
	char address[MAX_A];	//地址
	int name_key;  //对应的名字哈希地址
	int tele_key;  //对应的电话号码的哈希地址
	int flag;      //用来标识是否名字哈希表的位置是否已经冲突
}c_lient;   

typedef struct client_a {
	char name[MAX_N];		//姓名
	char telephone[MAX_T];	//电话号码
	char address[MAX_A];	//地址
	int tele_key;  //对应的电话哈希地址
	int name_key;
	int flag;      //用来标识是否名字哈希表的位置是否已经冲突， 1表示有数，0表示该位置还未放数
}client_tele;

	c_lient hash_name[MAX_H];//姓名哈希表
	client_tele hash_tele[MAX_H]; //电话哈希表



