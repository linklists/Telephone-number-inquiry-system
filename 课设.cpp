#define _CRT_SECURE_NO_WARNINGS 1
//��������������ϣ��
//�ؼ��ֵ�ȡ��:  ��������β�ַ������ģ��97����Ϊ97��100���ڵ�������������Լ��ٳ�ͻ�ķ���
//              �绰�����β����λ���������ģ��97
//�����ͻ�ķ���������̽�ⷨ

#include"hashname.h"
#include"main.h"
//����ӵĹ��ܣ���ʾ��ǰ�ж����˵���Ϣ���Լ����ж��ٿ���λ��
//����ӵĹ��ܣ����Ŀǰ�����û�����Ϣ
void menu()   //���˵�
{
	system("color 3");
	printf("\t _______________________________________________________\n");
	printf("\t|\t�绰�����ѯϵͳ\t\t\t\t|\n");
	printf("\t|\t  1.�����û���Ϣ\t\t\t\t|\n");
	printf("\t|\t  2.ɾ���û���Ϣ\t\t\t\t|\n");
	printf("\t|\t  3.���û�������\t\t\t\t|\n");
	printf("\t|\t  4.���绰�������\t\t\t\t|\n");
	printf("\t|\t  5.���û����޸��û���Ϣ\t\t\t|\n");
	printf("\t|\t  6.���绰�����޸��û���Ϣ\t\t\t|\n");
	printf("\t|\t  7.�鿴�����û���Ϣ(��Ҫ��֤����Ա���)\t|\n");
	printf("\t|\t  8.��ʾĿǰ��ϵͳ�洢������(��Ҫ��֤����Ա���)|\n");
	printf("\t|\t  9.��������û���Ϣ(��Ҫ��֤����Ա���)\t|\n");
	printf("\t|\t  0.�˳�\t\t\t\t\t|\n");
	printf("\t|_______________________________________________________|\n");
}
	
void serve()  //��ʾ�û���Ϣ
{
	int number = 5;  //��ʾ��λ���
	char mima[MAX_A], arr[] = "666666";
	printf("���ʴ˹�����Ҫ����ԱȨ��\n");
	while (number--)
	{
		printf("�������������Ա����(6λ����):\n");
		scanf("%s", mima);
		if (strcmp(mima, arr) == 0)
		{
			printf("������ȷ���û�����Ϣ����:\n");
			int num = 0;
			for (int i = 0; i < MAX_H; i++)
				if (hash_name[i].flag == 1) num++;
			printf("Ŀǰϵͳ�й��洢��%d���û�����Ϣ��������%d��λ��\n", num, 100 - num);
			break;
		}
		else
			printf("�������,������%d�λ���\n", number);
	}
	return;
}

void clear()  //����û���Ϣ
{
	int number = 5;  //��ʾ��λ���
	char mima[MAX_A], arr[] = "666666";
	printf("���ʴ˹�����Ҫ����ԱȨ��\n");
	while (number--)
	{
		printf("�������������Ա����(6λ����):\n");
		scanf("%s", mima);
		if (strcmp(mima, arr) == 0)
		{
			printf("������ȷ\n");
			for (int i = 0; i < MAX_A; i++)
			{
				hash_name[i].flag = 0;
				hash_tele[i].flag = 0;
			}
			printf("��ճɹ���\n");
			break;
		}
		else
			printf("�������,������%d�λ���\n", number);
	}
	return;
}

void SleepCls() //˯�߼�����
{
	Sleep(500);//������������ͣ0.5��
	system("cls");//��������
}

void ProgressBar() //ģ�������
{
	system("color 3");
	int i = 0;
	char arr[51] = { 0 };	//��Ž��ȵ�"#"
	char brr[] = "|/-\\";	//ģ��תȦȦ
	printf("\n");
	for (i = 0; i < 50; i++)
	{
		arr[i] = '#';
		printf("[%-50s][%d%%][%c]\r", arr, (i + 1) * 2, brr[i % 5]);  //�м��ǽ��ȣ��ұ���תȦȦ
		Sleep(50);
	}
	printf("\nϵͳ������ϣ�\n");	//�˸��Ĺ������һ���ƶ�
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
		printf("\n����������ѡ��:\n");
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
			printf("��������������:\n");
			char name[MAX_N];
			scanf("%s", name);
		    b = inquire_name(name);
			if (b >= 0) {
				printf("�����ҵ������ļ�¼���������绰�š���ַ�ֱ����£�\n");
				printf("%s %s %s\n", hash_name[b].name, hash_name[b].telephone, hash_name[b].address);
			}
			else printf("������ѯ����Ϣ������!\n");
			break;
		case 4:
			printf("���������ĵ绰����:\n");
			char tele[MAX_T];
			scanf("%s", tele);
			a = inquire_tele(tele);
			if (a >= 0)
			{
				printf("�����ҵ������ļ�¼���������绰�š���ַ�ֱ����£�\n");
				printf("%s %s %s\n", hash_tele[a].name, hash_tele[a].telephone, hash_tele[a].address);
			}
			else printf("������ѯ����Ϣ������!\n");
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
			quit();  //���ṹ�����е�������ӵ��ı���
			return 0;
		}
	}
	return 0;
}

void traverse()  //�鿴�����˵���Ϣ
{
	int number = 5;  //��ʾ��λ���
	char mima[MAX_A], arr[] = "666666";
	printf("���ʴ˹�����Ҫ����ԱȨ��\n");
	while (number--)
	{
		printf("�������������Ա����(6λ����):\n");
		scanf("%s", mima);
		if (strcmp(mima, arr) == 0)
		{
			printf("������ȷ���û�����Ϣ����:\n");
			for (int i = 0; i < MAX_H; i++)
			{
				if (hash_name[i].flag == 1)  //��������Ļ�
					printf("%s %s %s\n", hash_name[i].name, hash_name[i].telephone, hash_name[i].address);
			}
			break;
		}
		else
			printf("�������,������%d�λ���\n", number);
	}
}

void quit()  //�˳�����
{
	FILE* f;
	f = fopen("keshe.txt", "w");  //Wģʽ,ֻд�����ı������ԭ�е�����
	if (f == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
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

void init()   //��ʼ������
{
	for (int i = 0; i < MAX_H; i++)
	{
		hash_name[i].flag = 0;  //��ֵΪ0����ʾδ����
		hash_tele[i].flag = 0;
	}
	read_();
}

void read_()  //�û���Ϣ�����ļ�
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
		printf("δ�ɹ����ļ���\n");
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
			int key = key_name(c_name); //�����������ֹ�ϣ���е�λ��
			if (hash_name[key].flag == 0)  //��ǰλ�ò���ͻ
			{
				strcpy(hash_name[key].address, c_address); //������Ӳ���
				strcpy(hash_name[key].name, c_name);
				strcpy(hash_name[key].telephone, c_telephone);
				hash_name[key].name_key = key;
				hash_name[key].flag = 1;  //��Ǹ�λ���Ѿ�����
			}
			else  //��ǰλ�ó�ͻ
			{
				if (name_isfull() == 1)  //���ж��Ƿ����ֹ�ϣ���Ѿ�����
					printf("�𾴵Ŀͻ����ã����������Ϣ���ڵ����ֹ�ϣ���Ѿ����ˣ�����ϵ������Ա\n");
				else  //��������̽�취�����ͻ
				{
					key = method_name(key);
					strcpy(hash_name[key].address, c_address); //������Ӳ���
					strcpy(hash_name[key].name, c_name);
					strcpy(hash_name[key].telephone, c_telephone);
					hash_name[key].name_key = key;
					hash_name[key].flag = 1;  //��Ǹ�λ���Ѿ�����
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
		printf("δ�ɹ����ļ���\n");
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
			int tele_key = key_tele(c_telephone);  //����ڹ�ϣ���еĵ�ַ

			if (hash_tele[tele_key].flag == 0) //��ǰλ�ò���ͻ
			{
				strcpy(hash_tele[tele_key].address, c_address); //������Ӳ���
				strcpy(hash_tele[tele_key].name, c_name);
				strcpy(hash_tele[tele_key].telephone, c_telephone);
				hash_tele[tele_key].tele_key = tele_key;
				hash_tele[tele_key].flag = 1;  //��Ǹ�λ���Ѿ�����
			}
			else
			{
				if (tele_isfull() == 1)
					printf("�𾴵Ŀͻ����ã����������Ϣ���ڵĵ绰��ϣ���Ѿ����ˣ�����ϵ������Ա\n");
				else {
					tele_key = method_tele(tele_key);
					strcpy(hash_tele[tele_key].address, c_address); //������Ӳ���
					strcpy(hash_tele[tele_key].name, c_name);
					strcpy(hash_tele[tele_key].telephone, c_telephone);
					hash_tele[tele_key].tele_key = tele_key;
					hash_tele[tele_key].flag = 1;  //��Ǹ�λ���Ѿ�����
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
		if (hash_name[i].flag == 0) return 0;  //�п���λ�ã�ֱ�ӷ���0
	return 1;
}

bool tele_isfull()
{
	int flag = 1;
	for (int i = 0; i < MAX_H; i++)
		if (hash_tele[i].flag == 0) return 0;  //�п���λ�ã�ֱ�ӷ���0
	return 1;
}

int method_name(int key)  //����̽�취���
{
	int i;
	for (i = 1; (i + key) % MAX_H < MAX_H; i++)
		if (hash_name[(i + key) % MAX_H].flag == 0) return ((i + key) % MAX_H);
}

int method_tele(int tele_key)  //����̽�취���
{
	int i;
	for (i = 1; (i + tele_key) % MAX_H < MAX_H; i++)
		if (hash_name[(i + tele_key) % MAX_H].flag == 0) return ((i + tele_key) % MAX_H);
}

void addhash()   //��
{
	char c_name[MAX_N];
	char c_telephone[MAX_T];
	char c_address[MAX_A];

	int name_flag = 0, tele_flag = 0;   //��������Ƿ���ӳɹ�

	printf("��������������:\n");
	scanf("%s", c_name);

	printf("���������ĵ绰����:\n");
	scanf("%s", c_telephone);

	printf("���������ĵ�ַ:\n");
	scanf("%s", c_address);
	int panduan = 1, biaoji;
	while (1)
	{
		for(int i = 0; i < MAX_H; i ++)
			if (strcmp(hash_name[i].name, c_name) == 0 && hash_name[i].flag == 1)
			{
				printf("���ʧ�ܣ����������Ϣ�Ѿ����ڣ�\n");
				panduan = 0;
				break;
			}
		if (panduan == 0)
		{
			printf("��ȷ���Ƿ���������: ���������밴1, �˳��밴0\n");
			scanf("%d", &biaoji);
			if (biaoji)
			{
				panduan = 1;
				printf("��������������:\n");
				scanf("%s", c_name);

				printf("���������ĵ绰����:\n");
				scanf("%s", c_telephone);

				printf("���������ĵ�ַ:\n");
				scanf("%s", c_address);
			}
			else return;   //�����˳�
		}
		else break;
	}
	
	
	int tele_len = strlen(c_telephone), na_len = strlen(c_name), add_len = strlen(c_address);

	while (tele_len > MAX_T || tele_len < 0)  //���벻��ȷʱ��һֱ����
	{
		printf("�𾴵Ŀͻ����ã�������ĵ绰���볤�Ȳ���ȷ�����������롣\n");
		printf("���������ĵ绰����:\n");
		scanf("%s", c_telephone);
	}
		
	while (na_len > MAX_N || na_len < 0)  //���벻��ȷʱ��һֱ����
	{
		printf("�𾴵Ŀͻ����ã�����������ֳ��Ȳ���ȷ�����������롣\n");
		printf("�����������û���:\n");
		scanf("%s", c_name);
	}

	while (add_len > MAX_A || add_len < 0)  //���벻��ȷʱ��һֱ����
	{
		printf("�𾴵Ŀͻ����ã�������ĵ�ַ���Ȳ���ȷ�����������롣\n");
		printf("���������ĵ�ַ:\n");
		scanf("%s", c_address);
	}

	tele_len = strlen(c_telephone), na_len = strlen(c_name), add_len = strlen(c_address);

	int key = key_name(c_name);  //�����������ֹ�ϣ���е�λ��
	if (hash_name[key].flag == 0)  //��ǰλ�ò���ͻ
	{
		strcpy(hash_name[key].address, c_address); //������Ӳ���
		strcpy(hash_name[key].name, c_name);
		strcpy(hash_name[key].telephone, c_telephone);
		hash_name[key].name_key = key;
		hash_name[key].flag = 1;  //��Ǹ�λ���Ѿ�����
		name_flag = 1;
	}
	else  //��ǰλ�ó�ͻ
	{
		if (name_isfull() == 1)  //���ж��Ƿ����ֹ�ϣ���Ѿ�����
			printf("�𾴵Ŀͻ����ã����������Ϣ���ڵ����ֹ�ϣ���Ѿ����ˣ�����ϵ������Ա\n");
		else  //��������̽�취�����ͻ
		{
			key = method_name(key);
			strcpy(hash_name[key].address, c_address); //������Ӳ���
			strcpy(hash_name[key].name, c_name);
			strcpy(hash_name[key].telephone, c_telephone);
			hash_name[key].name_key = key;
			hash_name[key].flag = 1;  //��Ǹ�λ���Ѿ�����
			name_flag = 1;
		}
	}
	int tele_key = key_tele(c_telephone);

	if (hash_tele[tele_key].flag == 0) //��ǰλ�ò���ͻ
	{
		strcpy(hash_tele[tele_key].address, c_address); //������Ӳ���
		strcpy(hash_tele[tele_key].name, c_name);
		strcpy(hash_tele[tele_key].telephone, c_telephone);
		hash_tele[tele_key].tele_key = tele_key;
		hash_tele[tele_key].flag = 1;  //��Ǹ�λ���Ѿ�����
		tele_flag = 1;
	}
	else
	{
		if (tele_isfull() == 1)
			printf("�𾴵Ŀͻ����ã����������Ϣ���ڵĵ绰��ϣ���Ѿ����ˣ�����ϵ������Ա\n");
		else {
			tele_key = method_tele(tele_key);
			strcpy(hash_tele[tele_key].address, c_address); //������Ӳ���
			strcpy(hash_tele[tele_key].name, c_name);
			strcpy(hash_tele[tele_key].telephone, c_telephone);
			hash_tele[tele_key].tele_key = tele_key;
			hash_tele[tele_key].flag = 1;  //��Ǹ�λ���Ѿ�����
			tele_flag = 1;
		}
	}
	if (tele_flag == 1 && name_flag == 1) printf("��ӳɹ���\n");
}

int key_name(char c_name[])   //ͨ����ʽ�������������ϣ���еĵ�ַ
{
	int na_len = strlen(c_name);
	int key = (c_name[0] + c_name[na_len - 1] - '\0') % DIV;
	return key;
}

int key_tele(char c_telephone[])  //ͨ����ʽ��������ڵ绰��ϣ���еĵ�ַ
{
	int tele_len = strlen(c_telephone);
	int tele_key = (c_telephone[tele_len - 4] - '0') + (c_telephone[tele_len - 3] - '0') + (c_telephone[tele_len - 2] - '0') + (c_telephone[tele_len - 1] - '0');
	return tele_key;
}

int inquire_name(char c_name[])	  //�����ֲ�
{
	int i, j;
	j = key_name(c_name);
	if (strcmp(hash_name[j].name, c_name) == 0 && hash_name[j].flag == 1) return j;   //�������ͻֱ�ӷ���

	for (i = 0; i < MAX_H; i++)
	{
		if (strcmp(c_name, hash_name[i].name) == 0 && hash_name[i].flag == 1)
			return i;
	}
	return -1;  //û�ҵ����ش�����Ϣ
}

int inquire_tele(char c_telephone[])  //���绰�������
{
	int j = key_tele(c_telephone);
	if (strcmp(c_telephone, hash_tele[j].telephone) == 0 && hash_tele[j].flag == 1) return j;

	for (int i = 0; i < MAX_H; i++)
	{
		if (strcmp(c_telephone, hash_tele[i].telephone) == 0 && hash_tele[i].flag == 1)
			return i;
	}
	return -1;  //����ʧ�ܷ��ش�����Ϣ
}

void dele()  //ɾ
{
	char c_name[MAX_N];
	char c_telephone[MAX_T];
	char c_address[MAX_A];

	printf("��������Ҫɾ������Ϣ������:\n");
	scanf("%s", c_name);

	printf("��������Ҫɾ������Ϣ�ĵ绰����:\n");
	scanf("%s", c_telephone);

	printf("��������Ҫɾ������Ϣ�ĵ�ַ:\n");
	scanf("%s", c_address);

	int num = inquire_name(c_name), queren = 0;
	printf("��ȷ��Ҫɾ����Ϣ�� ȷ���밴1��ȡ�������밴0\n");
	printf("����������ѡ��:\n");
	scanf("%d", &queren);
	if (queren == 0) return;
	if (num >= 0 && queren)
	{
		hash_name[num].flag = 0;  //ֱ�Ӹ�ֵΪ0����ʾ��λ��û���������ش�����һ�������ֱ�Ӹ�����
		hash_tele[hash_name[num].tele_key].flag = 0;
		printf("ɾ���ɹ���\n");
	}
	else
		printf("��Ǹ��������ѯ����Ϣ�����ڣ�����������");

}

void change_name()  //��,�����û���������������޸Ĳ���
{
	char c_address[MAX_A];
	char c_name[MAX_N];
	char c_tele[MAX_T];
	printf("��������Ҫ�޸ĵ���Ϣ������:\n");
	scanf("%s", c_name);

	int num_name = inquire_name(c_name);  //�õ�����������ϣ���еĵ�ַ
	int flag = 1;
	if (num_name < 0 && flag)  //�ж��������Ϣ�Ƿ����
	{
		printf("����Ҫ��ѯ����Ϣ������,��ȷ���Ƿ���������\n");
		printf("ȷ���밴1���˳��밴0\n");
		scanf("%d", &flag);
		if (flag)
		{
			printf("��������Ҫ�޸ĵ���Ϣ������:\n");
			scanf("%s", c_name);
			num_name = inquire_name(c_name);
		}
		else return;
	}
	int num, num_tele = hash_name[num_name].tele_key;
	printf("��1�޸�����:\n");
	printf("��2�޸ĵ绰����:\n");
	printf("��3�޸ĵ�ַ:\n");
	printf("��4�޸�ȫ����Ϣ:\n");
	printf("����������ѡ��:\n");

	scanf("%d", &num);
	switch (num)
	{
	case 1:
		printf("�������޸ĺ������:\n");
		scanf("%s", c_name);
		strcpy(hash_name[num_name].name, c_name);
		strcpy(hash_tele[num_tele].name, c_name);
		printf("�޸ĳɹ�!\n");
		break;

	case 2:
		printf("�������޸ĺ�ĵ绰����:\n");
		scanf("%s", c_tele);
		strcpy(hash_name[num_name].telephone, c_tele);
		strcpy(hash_tele[num_tele].telephone, c_tele);
		printf("�޸ĳɹ�!\n");
		break;

	case 3:
		printf("�������޸ĺ�ĵ�ַ:\n");
		scanf("%s", c_address);
		strcpy(hash_name[num_name].address, c_address);
		strcpy(hash_tele[num_tele].address, c_address);
		printf("�޸ĳɹ�!\n");
		break;

	case 4:
		printf("�������޸ĺ������:\n");
		scanf("%s", c_name);
		printf("�������޸ĺ�ĵ绰����:\n");
		scanf("%s", c_tele);
		printf("�������޸ĺ�ĵ�ַ:\n");
		scanf("%s", c_address);

		strcpy(hash_name[num_name].name, c_name);
		strcpy(hash_tele[num_tele].name, c_name);
		strcpy(hash_name[num_name].telephone, c_tele);
		strcpy(hash_tele[num_tele].telephone, c_tele);
		strcpy(hash_name[num_name].address, c_address);
		strcpy(hash_tele[num_tele].address, c_address);
		printf("�޸ĳɹ�!\n");
		break;
	}

}

void change_tele()  //�����û�����ĵ绰��������޸�
{
	char c_tele[MAX_N];
	char c_name[MAX_N];
	char c_address[MAX_A];
	printf("��������Ҫ�޸ĵ���Ϣ�ĵ绰����:\n");
	scanf("%s", c_tele); 

	int num_tele = inquire_tele(c_tele);
	int flag = 1;
	if (num_tele < 0 && flag)  //�ж��������Ϣ�Ƿ����
	{
		printf("����Ҫ��ѯ����Ϣ������,��ȷ���Ƿ���������\n");
		printf("ȷ���밴1���˳��밴0\n");
		scanf("%d", &flag);
		if (flag)
		{
			printf("��������Ҫ�޸ĵ���Ϣ�ĵ绰����:\n");
			scanf("%s", c_tele);
			num_tele = inquire_tele(c_tele);
		}
	}
	int num, num_name = hash_tele[num_tele].name_key;
	printf("��1�޸�����:\n");
	printf("��2�޸ĵ绰����:\n");
	printf("��3�޸ĵ�ַ:\n");
	printf("��4�޸�ȫ����Ϣ:\n");
	printf("����������ѡ��:\n");

	scanf("%d", &num);
	switch (num)
	{
	case 1:
		printf("�������޸ĺ������:");
		scanf("%s", c_name);
		strcpy(hash_name[num_name].name, c_name);
		strcpy(hash_tele[num_tele].name, c_name);
		printf("�޸ĳɹ�!\n");
		break;

	case 2:
		printf("�������޸ĺ�ĵ绰����:");
		scanf("%s", c_tele);
		strcpy(hash_name[num_name].telephone, c_tele);
		strcpy(hash_tele[num_tele].telephone, c_tele);
		printf("�޸ĳɹ�!\n");
		break;

	case 3:
		printf("�������޸ĺ�ĵ�ַ:\n");
		scanf("%s", c_address);
		strcpy(hash_name[num_name].address, c_address);
		strcpy(hash_tele[num_tele].address, c_address);
		printf("�޸ĳɹ�!\n");
		break;

	case 4:
		printf("�������޸ĺ������:\n");
		scanf("%s", c_name);
		printf("�������޸ĺ�ĵ绰����:\n");
		scanf("%s", c_tele);
		printf("�������޸ĺ�ĵ�ַ:\n");
		scanf("%s", c_address);

		strcpy(hash_name[num_name].name, c_name);
		strcpy(hash_tele[num_tele].name, c_name);
		strcpy(hash_name[num_name].telephone, c_tele);
		strcpy(hash_tele[num_tele].telephone, c_tele);
		strcpy(hash_name[num_name].address, c_address);
		strcpy(hash_tele[num_tele].address, c_address);
		printf("�޸ĳɹ�!\n");
		break;
	}

}