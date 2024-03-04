#pragma once
//预编译去掉Unicode字符集
#ifdef UNICODE
#undef UNICODE
#endif // UNICODE

#include <easyx.h>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <memory>
using namespace std;

#define MAX_H 100 //哈希表最大长度
#define DIV (97)  //表示除数
