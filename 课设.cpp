#define _CRT_SECURE_NO_WARNINGS 1
//用名字来建立哈希表
//关键字的取法:  姓名的首尾字符相加再模上97，因为97是100以内的最大质数，可以减少冲突的发生
//              电话号码的尾号四位数字相加再模上97
//处理冲突的方法：线性探测法

#include"hashname.h"
#include"main.h"
//待添加的功能，显示当前有多少人的信息，以及还有多少空余位置
//待添加的功能，清空目前所有用户的信息
void menu()   //主菜单
{
	system("color 3");
	printf("\t _______________________________________________________\n");
	printf("\t|\t电话号码查询系统\t\t\t\t|\n");
	printf("\t|\t  1.增加用户信息\t\t\t\t|\n");
	printf("\t|\t  2.删除用户信息\t\t\t\t|\n");
	printf("\t|\t  3.按用户名查找\t\t\t\t|\n");
	printf("\t|\t  4.按电话号码查找\t\t\t\t|\n");
	printf("\t|\t  5.按用户名修改用户信息\t\t\t|\n");
	printf("\t|\t  6.按电话号码修改用户信息\t\t\t|\n");
	printf("\t|\t  7.查看所有用户信息(需要验证管理员身份)\t|\n");
	printf("\t|\t  8.显示目前的系统存储的人数(需要验证管理员身份)|\n");
	printf("\t|\t  9.清空所有用户信息(需要验证管理员身份)\t|\n");
	printf("\t|\t  0.退出\t\t\t\t\t|\n");
	printf("\t|_______________________________________________________|\n");
}
	
void serve()  //显示用户信息
{
	int number = 5;  //表示五次机会
	char mima[MAX_A], arr[] = "666666";
	printf("访问此功能需要管理员权限\n");
	while (number--)
	{
		printf("下面请输入管理员密码(6位数字):\n");
		scanf("%s", mima);
		if (strcmp(mima, arr) == 0)
		{
			printf("密码正确，用户的信息如下:\n");
			int num = 0;
			for (int i = 0; i < MAX_H; i++)
				if (hash_name[i].flag == 1) num++;
			printf("目前系统中共存储了%d名用户的信息，还空余%d个位置\n", num, 100 - num);
			break;
		}
		else
			printf("密码错误,您还有%d次机会\n", number);
	}
	return;
}

void clear()  //清空用户信息
{
	int number = 5;  //表示五次机会
	char mima[MAX_A], arr[] = "666666";
	printf("访问此功能需要管理员权限\n");
	while (number--)
	{
		printf("下面请输入管理员密码(6位数字):\n");
		scanf("%s", mima);
		if (strcmp(mima, arr) == 0)
		{
			printf("密码正确\n");
			for (int i = 0; i < MAX_A; i++)
			{
				hash_name[i].flag = 0;
				hash_tele[i].flag = 0;
			}
			printf("清空成功！\n");
			break;
		}
		else
			printf("密码错误,您还有%d次机会\n", number);
	}
	return;
}

void SleepCls() //睡眠加清屏
{
	Sleep(500);//程序在这里暂停0.5秒
	system("cls");//清屏操作
}

void ProgressBar() //模拟进度条
{
	system("color 3");
	int i = 0;
	char arr[51] = { 0 };	//存放进度的"#"
	char brr[] = "|/-\\";	//模拟转圈圈
	printf("\n");
	for (i = 0; i < 50; i++)
	{
		arr[i] = '#';
		printf("[%-50s][%d%%][%c]\r", arr, (i + 1) * 2, brr[i % 5]);  //中间是进度，右边是转圈圈
		Sleep(50);
	}
	printf("\n系统加载完毕！\n");	//退格后的光标向下一行移动
}

int main01()
{
	SleepCls();
	ProgressBar();
	init();
	int num;
	while (1)
	{
		menu();
		int a, b;
		printf("\n请输入您的选择:\n");
		scanf("%d", &num);
		switch (num)
		{
		case 1:
				addhash();
				break;
		case 2:
				dele();
				break;
			
		case 3:
			printf("请输入您的姓名:\n");
			char name[MAX_N];
			scanf("%s", name);
		    b = inquire_name(name);
			if (b >= 0) {
				printf("您查找的姓名的记录按姓名、电话号、地址分别如下：\n");
				printf("%s %s %s\n", hash_name[b].name, hash_name[b].telephone, hash_name[b].address);
			}
			else printf("您所查询的信息不存在!\n");
			break;
		case 4:
			printf("请输入您的电话号码:\n");
			char tele[MAX_T];
			scanf("%s", tele);
			a = inquire_tele(tele);
			if (a >= 0)
			{
				printf("您查找的姓名的记录按姓名、电话号、地址分别如下：\n");
				printf("%s %s %s\n", hash_tele[a].name, hash_tele[a].telephone, hash_tele[a].address);
			}
			else printf("您所查询的信息不存在!\n");
			break;
		case 5:
			change_name();
			break;
		case 6:
			change_tele();
			break;
		case 7:
			traverse();
			break;
		case 8:
			serve();
			break;
		case 9:
			clear();
			break;
		case 0:
			quit();  //将结构数组中的内容添加到文本中
			return 0;
		}
	}
	return 0;
}

void traverse()  //查看所有人的信息
{
	int number = 5;  //表示五次机会
	char mima[MAX_A], arr[] = "666666";
	printf("访问此功能需要管理员权限\n");
	while (number--)
	{
		printf("下面请输入管理员密码(6位数字):\n");
		scanf("%s", mima);
		if (strcmp(mima, arr) == 0)
		{
			printf("密码正确，用户的信息如下:\n");
			for (int i = 0; i < MAX_H; i++)
			{
				if (hash_name[i].flag == 1)  //如果有数的话
					printf("%s %s %s\n", hash_name[i].name, hash_name[i].telephone, hash_name[i].address);
			}
			break;
		}
		else
			printf("密码错误,您还有%d次机会\n", number);
	}
}

void quit()  //退出函数
{
	FILE* f;
	f = fopen("keshe.txt", "w");  //W模式,只写，打开文本，清空原有的数据
	if (f == NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
	int i;
	for (i = 0; i < MAX_H; i++)
	{
		if (hash_name[i].flag == 1)
			fprintf(f, "%s %s %s\n", hash_name[i].name, hash_name[i].telephone, hash_name[i].address);
	}
	fclose(f);
}

void init()   //初始化函数
{
	for (int i = 0; i < MAX_H; i++)
	{
		hash_name[i].flag = 0;  //赋值为0，表示未放数
		hash_tele[i].flag = 0;
	}
	read_();
}

void read_()  //用户信息载入文件
{
	add_name();
	add_tele();
}

void add_name()
{
	FILE* f = NULL;
	f = fopen("keshe.txt", "r+");

	if (f == NULL)
	{
		printf("未成功打开文件！\n");
		exit(0);
	}
	char c_name[MAX_N];
	char c_telephone[MAX_T];
	char c_address[MAX_A];
	
	while (!feof(f))
	{
		fscanf(f, "%s %s %s", c_name, c_telephone, c_address);
		if (!feof(f))
		{
			int key = key_name(c_name); //计算其在名字哈希表中的位置
			if (hash_name[key].flag == 0)  //当前位置不冲突
			{
				strcpy(hash_name[key].address, c_address); //进行添加操作
				strcpy(hash_name[key].name, c_name);
				strcpy(hash_name[key].telephone, c_telephone);
				hash_name[key].name_key = key;
				hash_name[key].flag = 1;  //标记该位置已经有数
			}
			else  //当前位置冲突
			{
				if (name_isfull() == 1)  //先判断是否名字哈希表已经满了
					printf("尊敬的客户您好，您输入的信息所在的名字哈希表已经满了，请联系工作人员\n");
				else  //利用线性探察法解决冲突
				{
					key = method_name(key);
					strcpy(hash_name[key].address, c_address); //进行添加操作
					strcpy(hash_name[key].name, c_name);
					strcpy(hash_name[key].telephone, c_telephone);
					hash_name[key].name_key = key;
					hash_name[key].flag = 1;  //标记该位置已经有数
				}
			}
		}
	}
	fclose(f);
}

void add_tele()
{
	FILE* f;
	f = fopen("keshe.txt", "r+");

	if (f == NULL)
	{
		printf("未成功打开文件！\n");
		exit(0);
	}
	char c_name[MAX_N];
	char c_telephone[MAX_T];
	char c_address[MAX_A];
	while (!feof(f))
	{
		fscanf(f, "%s %s %s", c_name, c_telephone, c_address);
		if (!feof(f))
		{
			int tele_key = key_tele(c_telephone);  //算出在哈希表中的地址

			if (hash_tele[tele_key].flag == 0) //当前位置不冲突
			{
				strcpy(hash_tele[tele_key].address, c_address); //进行添加操作
				strcpy(hash_tele[tele_key].name, c_name);
				strcpy(hash_tele[tele_key].telephone, c_telephone);
				hash_tele[tele_key].tele_key = tele_key;
				hash_tele[tele_key].flag = 1;  //标记该位置已经有数
			}
			else
			{
				if (tele_isfull() == 1)
					printf("尊敬的客户您好，您输入的信息所在的电话哈希表已经满了，请联系工作人员\n");
				else {
					tele_key = method_tele(tele_key);
					strcpy(hash_tele[tele_key].address, c_address); //进行添加操作
					strcpy(hash_tele[tele_key].name, c_name);
					strcpy(hash_tele[tele_key].telephone, c_telephone);
					hash_tele[tele_key].tele_key = tele_key;
					hash_tele[tele_key].flag = 1;  //标记该位置已经有数
				}
			}
		}
	}
	fclose(f);
}

bool name_isfull()
{
	int flag = 1;
	for (int i = 0; i < MAX_H; i++)
		if (hash_name[i].flag == 0) return 0;  //有空余位置，直接返回0
	return 1;
}

bool tele_isfull()
{
	int flag = 1;
	for (int i = 0; i < MAX_H; i++)
		if (hash_tele[i].flag == 0) return 0;  //有空余位置，直接返回0
	return 1;
}

int method_name(int key)  //线性探察法解决
{
	int i;
	for (i = 1; (i + key) % MAX_H < MAX_H; i++)
		if (hash_name[(i + key) % MAX_H].flag == 0) return ((i + key) % MAX_H);
}

int method_tele(int tele_key)  //线性探察法解决
{
	int i;
	for (i = 1; (i + tele_key) % MAX_H < MAX_H; i++)
		if (hash_name[(i + tele_key) % MAX_H].flag == 0) return ((i + tele_key) % MAX_H);
}

void addhash()   //增
{
	char c_name[MAX_N];
	char c_telephone[MAX_T];
	char c_address[MAX_A];

	int name_flag = 0, tele_flag = 0;   //用来标记是否添加成功

	printf("请输入您的姓名:\n");
	scanf("%s", c_name);

	printf("请输入您的电话号码:\n");
	scanf("%s", c_telephone);

	printf("请输入您的地址:\n");
	scanf("%s", c_address);
	int panduan = 1, biaoji;
	while (1)
	{
		for(int i = 0; i < MAX_H; i ++)
			if (strcmp(hash_name[i].name, c_name) == 0 && hash_name[i].flag == 1)
			{
				printf("添加失败，您输入的信息已经存在！\n");
				panduan = 0;
				break;
			}
		if (panduan == 0)
		{
			printf("请确认是否重新输入: 重新输入请按1, 退出请按0\n");
			scanf("%d", &biaoji);
			if (biaoji)
			{
				panduan = 1;
				printf("请输入您的姓名:\n");
				scanf("%s", c_name);

				printf("请输入您的电话号码:\n");
				scanf("%s", c_telephone);

				printf("请输入您的地址:\n");
				scanf("%s", c_address);
			}
			else return;   //否则退出
		}
		else break;
	}
	
	
	int tele_len = strlen(c_telephone), na_len = strlen(c_name), add_len = strlen(c_address);

	while (tele_len > MAX_T || tele_len < 0)  //输入不正确时，一直提醒
	{
		printf("尊敬的客户您好，您输入的电话号码长度不正确，请重新输入。\n");
		printf("请输入您的电话号码:\n");
		scanf("%s", c_telephone);
	}
		
	while (na_len > MAX_N || na_len < 0)  //输入不正确时，一直提醒
	{
		printf("尊敬的客户您好，您输入的名字长度不正确，请重新输入。\n");
		printf("请输入您的用户名:\n");
		scanf("%s", c_name);
	}

	while (add_len > MAX_A || add_len < 0)  //输入不正确时，一直提醒
	{
		printf("尊敬的客户您好，您输入的地址长度不正确，请重新输入。\n");
		printf("请输入您的地址:\n");
		scanf("%s", c_address);
	}

	tele_len = strlen(c_telephone), na_len = strlen(c_name), add_len = strlen(c_address);

	int key = key_name(c_name);  //计算其在名字哈希表中的位置
	if (hash_name[key].flag == 0)  //当前位置不冲突
	{
		strcpy(hash_name[key].address, c_address); //进行添加操作
		strcpy(hash_name[key].name, c_name);
		strcpy(hash_name[key].telephone, c_telephone);
		hash_name[key].name_key = key;
		hash_name[key].flag = 1;  //标记该位置已经有数
		name_flag = 1;
	}
	else  //当前位置冲突
	{
		if (name_isfull() == 1)  //先判断是否名字哈希表已经满了
			printf("尊敬的客户您好，您输入的信息所在的名字哈希表已经满了，请联系工作人员\n");
		else  //利用线性探察法解决冲突
		{
			key = method_name(key);
			strcpy(hash_name[key].address, c_address); //进行添加操作
			strcpy(hash_name[key].name, c_name);
			strcpy(hash_name[key].telephone, c_telephone);
			hash_name[key].name_key = key;
			hash_name[key].flag = 1;  //标记该位置已经有数
			name_flag = 1;
		}
	}
	int tele_key = key_tele(c_telephone);

	if (hash_tele[tele_key].flag == 0) //当前位置不冲突
	{
		strcpy(hash_tele[tele_key].address, c_address); //进行添加操作
		strcpy(hash_tele[tele_key].name, c_name);
		strcpy(hash_tele[tele_key].telephone, c_telephone);
		hash_tele[tele_key].tele_key = tele_key;
		hash_tele[tele_key].flag = 1;  //标记该位置已经有数
		tele_flag = 1;
	}
	else
	{
		if (tele_isfull() == 1)
			printf("尊敬的客户您好，您输入的信息所在的电话哈希表已经满了，请联系工作人员\n");
		else {
			tele_key = method_tele(tele_key);
			strcpy(hash_tele[tele_key].address, c_address); //进行添加操作
			strcpy(hash_tele[tele_key].name, c_name);
			strcpy(hash_tele[tele_key].telephone, c_telephone);
			hash_tele[tele_key].tele_key = tele_key;
			hash_tele[tele_key].flag = 1;  //标记该位置已经有数
			tele_flag = 1;
		}
	}
	if (tele_flag == 1 && name_flag == 1) printf("添加成功！\n");
}

int key_name(char c_name[])   //通过公式算出来在姓名哈希表中的地址
{
	int na_len = strlen(c_name);
	int key = (c_name[0] + c_name[na_len - 1] - '\0') % DIV;
	return key;
}

int key_tele(char c_telephone[])  //通过公式计算出来在电话哈希表中的地址
{
	int tele_len = strlen(c_telephone);
	int tele_key = (c_telephone[tele_len - 4] - '0') + (c_telephone[tele_len - 3] - '0') + (c_telephone[tele_len - 2] - '0') + (c_telephone[tele_len - 1] - '0');
	return tele_key;
}

int inquire_name(char c_name[])	  //按名字查
{
	int i, j;
	j = key_name(c_name);
	if (strcmp(hash_name[j].name, c_name) == 0 && hash_name[j].flag == 1) return j;   //如果不冲突直接返回

	for (i = 0; i < MAX_H; i++)
	{
		if (strcmp(c_name, hash_name[i].name) == 0 && hash_name[i].flag == 1)
			return i;
	}
	return -1;  //没找到返回错误信息
}

int inquire_tele(char c_telephone[])  //按电话号码查找
{
	int j = key_tele(c_telephone);
	if (strcmp(c_telephone, hash_tele[j].telephone) == 0 && hash_tele[j].flag == 1) return j;

	for (int i = 0; i < MAX_H; i++)
	{
		if (strcmp(c_telephone, hash_tele[i].telephone) == 0 && hash_tele[i].flag == 1)
			return i;
	}
	return -1;  //查找失败返回错误信息
}

void dele()  //删
{
	char c_name[MAX_N];
	char c_telephone[MAX_T];
	char c_address[MAX_A];

	printf("请输入您要删除的信息的姓名:\n");
	scanf("%s", c_name);

	printf("请输入您要删除的信息的电话号码:\n");
	scanf("%s", c_telephone);

	printf("请输入您要删除的信息的地址:\n");
	scanf("%s", c_address);

	int num = inquire_name(c_name), queren = 0;
	printf("您确认要删除信息吗？ 确认请按1，取消操作请按0\n");
	printf("请输入您的选择:\n");
	scanf("%d", &queren);
	if (queren == 0) return;
	if (num >= 0 && queren)
	{
		hash_name[num].flag = 0;  //直接赋值为0，表示该位置没有数，不必处理，下一个数添加直接覆盖了
		hash_tele[hash_name[num].tele_key].flag = 0;
		printf("删除成功！\n");
	}
	else
		printf("抱歉，您所查询的信息不存在，请重新输入");

}

void change_name()  //改,根据用户输入的姓名进行修改操作
{
	char c_address[MAX_A];
	char c_name[MAX_N];
	char c_tele[MAX_T];
	printf("请输入您要修改的信息的姓名:\n");
	scanf("%s", c_name);

	int num_name = inquire_name(c_name);  //得到其在姓名哈希表中的地址
	int flag = 1;
	if (num_name < 0 && flag)  //判断输入的信息是否存在
	{
		printf("您所要查询的信息不存在,请确认是否重新输入\n");
		printf("确认请按1，退出请按0\n");
		scanf("%d", &flag);
		if (flag)
		{
			printf("请输入您要修改的信息的姓名:\n");
			scanf("%s", c_name);
			num_name = inquire_name(c_name);
		}
		else return;
	}
	int num, num_tele = hash_name[num_name].tele_key;
	printf("按1修改姓名:\n");
	printf("按2修改电话号码:\n");
	printf("按3修改地址:\n");
	printf("按4修改全部信息:\n");
	printf("请输入您的选择:\n");

	scanf("%d", &num);
	switch (num)
	{
	case 1:
		printf("请输入修改后的姓名:\n");
		scanf("%s", c_name);
		strcpy(hash_name[num_name].name, c_name);
		strcpy(hash_tele[num_tele].name, c_name);
		printf("修改成功!\n");
		break;

	case 2:
		printf("请输入修改后的电话号码:\n");
		scanf("%s", c_tele);
		strcpy(hash_name[num_name].telephone, c_tele);
		strcpy(hash_tele[num_tele].telephone, c_tele);
		printf("修改成功!\n");
		break;

	case 3:
		printf("请输入修改后的地址:\n");
		scanf("%s", c_address);
		strcpy(hash_name[num_name].address, c_address);
		strcpy(hash_tele[num_tele].address, c_address);
		printf("修改成功!\n");
		break;

	case 4:
		printf("请输入修改后的姓名:\n");
		scanf("%s", c_name);
		printf("请输入修改后的电话号码:\n");
		scanf("%s", c_tele);
		printf("请输入修改后的地址:\n");
		scanf("%s", c_address);

		strcpy(hash_name[num_name].name, c_name);
		strcpy(hash_tele[num_tele].name, c_name);
		strcpy(hash_name[num_name].telephone, c_tele);
		strcpy(hash_tele[num_tele].telephone, c_tele);
		strcpy(hash_name[num_name].address, c_address);
		strcpy(hash_tele[num_tele].address, c_address);
		printf("修改成功!\n");
		break;
	}

}

void change_tele()  //根据用户输入的电话号码进行修改
{
	char c_tele[MAX_N];
	char c_name[MAX_N];
	char c_address[MAX_A];
	printf("请输入您要修改的信息的电话号码:\n");
	scanf("%s", c_tele); 

	int num_tele = inquire_tele(c_tele);
	int flag = 1;
	if (num_tele < 0 && flag)  //判断输入的信息是否存在
	{
		printf("您所要查询的信息不存在,请确认是否重新输入\n");
		printf("确认请按1，退出请按0\n");
		scanf("%d", &flag);
		if (flag)
		{
			printf("请输入您要修改的信息的电话号码:\n");
			scanf("%s", c_tele);
			num_tele = inquire_tele(c_tele);
		}
	}
	int num, num_name = hash_tele[num_tele].name_key;
	printf("按1修改姓名:\n");
	printf("按2修改电话号码:\n");
	printf("按3修改地址:\n");
	printf("按4修改全部信息:\n");
	printf("请输入您的选择:\n");

	scanf("%d", &num);
	switch (num)
	{
	case 1:
		printf("请输入修改后的姓名:");
		scanf("%s", c_name);
		strcpy(hash_name[num_name].name, c_name);
		strcpy(hash_tele[num_tele].name, c_name);
		printf("修改成功!\n");
		break;

	case 2:
		printf("请输入修改后的电话号码:");
		scanf("%s", c_tele);
		strcpy(hash_name[num_name].telephone, c_tele);
		strcpy(hash_tele[num_tele].telephone, c_tele);
		printf("修改成功!\n");
		break;

	case 3:
		printf("请输入修改后的地址:\n");
		scanf("%s", c_address);
		strcpy(hash_name[num_name].address, c_address);
		strcpy(hash_tele[num_tele].address, c_address);
		printf("修改成功!\n");
		break;

	case 4:
		printf("请输入修改后的姓名:\n");
		scanf("%s", c_name);
		printf("请输入修改后的电话号码:\n");
		scanf("%s", c_tele);
		printf("请输入修改后的地址:\n");
		scanf("%s", c_address);

		strcpy(hash_name[num_name].name, c_name);
		strcpy(hash_tele[num_tele].name, c_name);
		strcpy(hash_name[num_name].telephone, c_tele);
		strcpy(hash_tele[num_tele].telephone, c_tele);
		strcpy(hash_name[num_name].address, c_address);
		strcpy(hash_tele[num_tele].address, c_address);
		printf("修改成功!\n");
		break;
	}

}