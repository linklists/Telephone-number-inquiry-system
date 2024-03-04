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

	//����������
	void run();

	//��ҳ�棨�˵���
	int menu();

	//0.���
	void add();

	//1.ɾ��
	void earse();

	//2.�޸�
	void modify();

	//3.����������
	void SearchByName();

	//4.���绰�������
	void SearchByTele();

	//5.�鿴������Ϣ������Ա��
	void traverse();

	//6.��ʾ��ǰ����(ϵͳ�洢������)������Ա��
	void surplus();

	//7.���������Ϣ������Ա��
	void clearall();

	//8.�˳�ϵͳ

	void ChangeByName(int location);

	void CHangeByTele(int location);

	//���Ʊ���
	void DrawBackground();

	void EventLoop();

	//������ϣ�������ϣ���ʼ��
	void init(); 

	bool name_isfull();

	bool tele_isfull();

	//���������ļ�ֵ
	int key_name(string name);

	//�������ļ�ֵ
	int key_tele(string telephone);

	//����̽�ⷨ
	int method_name(int key);

	//����̽�ⷨ
	int method_tele(int key);

	//������������Ϊ��ֵ�����ļ��ϵ���Ϣ������ʱ����
	void LoadFile(const string& filename);

	//����ʱ�����е����ݴ����ļ�
	void SaveFile(const string& filename);

	//������Ϊ��ֵ���ң������򷵻�λ���������������򷵻ظ���
	int inquire_name(string name);

	//�Ե绰����Ϊ��ֵ���ң������򷵻�λ���������������򷵻ظ���
	int inquire_tele(string telephone);

	void UpdateShowTable();

private:
	int op;
	IMAGE bk;
	vector<unique_ptr<PushButton>> menu_buttons;

	string header_str;

	user hash_name[MAX_H];
	user hash_tele[MAX_H];

	//�鿴�û����
	unique_ptr<Table> ShowTable;
	//����û���ť
	unique_ptr<PushButton> AddButton;
	unique_ptr<LineEdit> AddEdit;
	//ɾ���û���ť
	unique_ptr<PushButton> DeleteButton;
	unique_ptr<LineEdit> DeleteEdit;
	unique_ptr<Table> DeleteTable;
	//�޸���ϵ��
	//unique_ptr<PushButton> ModifyButton;
	unique_ptr<LineEdit> ModifyEdit;
	vector<unique_ptr<LineEdit>> UserEdit;
	bool isFind = false;
	vector<user> ModifyIt;
	int location;
	//��������ѯ�û���ť
	unique_ptr<PushButton> SearchNameButton;
	unique_ptr<LineEdit> SearchNameEdit;
	//���绰�����ѯ�û���ť
	unique_ptr<PushButton> SearchTeleButton;
	unique_ptr<LineEdit> SearchTeleEdit;
	//��ʾ����
	unique_ptr<PushButton> ShowSurplusButton;
	//����ļ�
	unique_ptr<PushButton> ClearButton;
};

