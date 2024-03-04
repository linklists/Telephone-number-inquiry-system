#include "UI_management.h"
#include "UI_window.h"
#include "user.h"

UI_management::UI_management()
{
	init();
	LoadFile("./�ļ��������.txt");
	header_str = "���� �绰���� סַ";
	::loadimage(&bk, "./��.jpg", UI_window::GetWidth(), UI_window::GetHeight());
	::settextstyle(20, 0, "����");

	//�������ʼ��
	menu_buttons.emplace_back(new PushButton("���"));
	menu_buttons.emplace_back(new PushButton("ɾ��"));
	menu_buttons.emplace_back(new PushButton("�޸�"));
	menu_buttons.emplace_back(new PushButton("����������"));
	menu_buttons.emplace_back(new PushButton("���绰�������"));
	menu_buttons.emplace_back(new PushButton("�鿴������Ϣ"));
	menu_buttons.emplace_back(new PushButton("��ʾ��ǰ����"));
	menu_buttons.emplace_back(new PushButton("���������Ϣ"));
	menu_buttons.emplace_back(new PushButton("�˳�ϵͳ"));
	for (int i = 0; i < menu_buttons.size(); ++i) {
		menu_buttons[i]->SetFixedSize(250, 50);
		int bx = (UI_window::GetWidth() - menu_buttons[i]->GetWidth()) / 2;
		int by = (UI_window::GetHeight() - menu_buttons.size() * menu_buttons[i]->GetHeight()) / 2 + i * menu_buttons[i]->GetHeight();
		menu_buttons[i]->move(bx, by);
	}

	//��ʼ���鿴�û��ı��
	ShowTable.reset(new Table);
	ShowTable->SetRowCount(11);
	ShowTable->SetHeader(header_str);
	//������
	//int tx = (UI_window::GetWidth() - ShowTable->cols * ShowTable->GridWidth) / 2;
	//int ty = (UI_window::GetHeight() - ShowTable->rows * ShowTable->GridHeight) / 2;
	int tx = (UI_window::GetWidth() - ShowTable->GetWidth()) / 2;
	int ty = (UI_window::GetHeight() - ShowTable->GetHeight()) / 2;
	ShowTable->move(tx, ty);

	//���ܵ��Ƶ�DrawTableData��
	//for (int i = 0; i < MAX_H; ++i) {
	//	if (hash_name[i].flag == 1) {
	//		//һ���û���Ϊһ������
	//		ShowTable->InsertData(hash_name[i]);
	//	}
	//}

	//�����ϵ��
	AddButton.reset(new PushButton("���", 1000, 260, 80, 40));
	AddEdit.reset(new LineEdit(400, 260, 500, 40));
	AddEdit->SetTitle("��������ϵ����Ϣ");
	AddEdit->SetHitText("�밴��<���� �绰���� ��ַ>��ʽ������Ϣ");

	//ɾ����ϵ��
	DeleteButton.reset(new PushButton("ɾ��", 1000, 260, 80, 40));
	DeleteEdit.reset(new LineEdit(400, 260, 500, 40));
	DeleteEdit->SetTitle("��ʾ");
	DeleteEdit->SetHitText("������Ҫɾ������ϵ������");
	//DeleteTable.reset(new Table);
	//DeleteTable->SetHeader(header_str);
	//DeleteTable->move(DeleteEdit->GetX(), DeleteEdit->GetY() + 120);
	//DeleteTable->SetRowCount(1);

	//�޸���ϵ����Ϣ
	ModifyEdit.reset(new LineEdit(400, 260, 500, 40));
	ModifyEdit->move((UI_window::GetWidth() - ModifyEdit->GetWidth()) / 2, 260);
	int x = (UI_window::GetWidth() - 200 * 3) / 2;
	for (int i = 0; i < 3; ++i) {
		UserEdit.emplace_back(new LineEdit);
		UserEdit[i]->SetFixedSize(200, 40);
		UserEdit[i]->move(x + i * UserEdit[i]->GetWidth(), ModifyEdit->GetY() + 50);
	}
	location = -1;

	//��������ѯ��ϵ��
	SearchNameButton.reset(new PushButton("��ѯ", 1000, 260, 80, 40));
	SearchNameEdit.reset(new LineEdit(400, 260, 500, 40));
	SearchNameEdit->SetTitle("��ʾ");
	SearchNameEdit->SetHitText("������Ҫ��ѯ����ϵ������");

	//��������ѯ��ϵ��
	SearchTeleButton.reset(new PushButton("��ѯ", 1000, 260, 80, 40));
	SearchTeleEdit.reset(new LineEdit(400, 260, 500, 40));
	SearchTeleEdit->SetTitle("��ʾ");
	SearchTeleEdit->SetHitText("������Ҫ��ѯ����ϵ�˵绰����");

	//��ʾ����
	int bx = (UI_window::GetWidth() - 80) / 2;
	ShowSurplusButton.reset(new PushButton("��ʾ", bx, 260, 80, 40));

	//���
	int bbx = (UI_window::GetWidth() - 80) / 2;
	ClearButton.reset(new PushButton("���", bbx, 260, 80, 40));
}

void UI_management::run()
{
	//::settextstyle(20, 0, "����");
	//��ȡ�˵�����ֵ
	int op = 66;
	UI_window::BeginDraw();
	while (true) {
		UI_window::clear();
		DrawBackground();
		
		if (UI_window::HasMsg()) {
			switch (UI_window::GetMsg().message)
			{
			case WM_KEYDOWN:	//���°���
				//��ESC���˳�����������������
				if (UI_window::GetMsg().vkcode == VK_ESCAPE) {
					cout << "escape" << endl;
					op = 66;
				}
				break;
			default:			//������
				EventLoop();
				break;
			}
		}

		//ExMessage msg;
		//peekmessage(&msg, EX_MOUSE | EX_KEY);
		//if (msg.message == WM_KEYDOWN) {
		//	switch (msg.vkcode)
		//	{
		//	case VK_ESCAPE:
		//		cout << "escape" << endl;
		//		op = 66;
		//		break;
		//	case VK_LEFT:
		//		cout << "left" << endl;
		//		break;
		//	default:
		//		break;
		//	}
		//}
		
		switch (op) {
		case 66:
			op = menu();
			break;
		case 0:
			add();
			break;
		case 1:
			earse();
			break;
		case 2:
			modify();
			break;
		case 3:
			SearchByName();
			break;
		case 4:
			SearchByTele();
			break;
		case 5:
			traverse();
			break;
		case 6:
			surplus();
			break;
		case 7:
			clearall();
			break;
		default:	
			SaveFile("./�ļ��������.txt");
			exit(666);
			break;
		}

		UI_window::FlushDraw();
		UI_window::GetMsg().message = 0;
	}
	UI_window::EndDraw();
}

int UI_management::menu()
{
	for (int i = 0; i < menu_buttons.size(); ++i) {
		menu_buttons[i]->show();
		menu_buttons[i]->event();
		if (menu_buttons[i]->IsClicked()) {
			return i;
		}
	}

	return 66;
}

//���ݼ���keyֵ�ĺ������������绰�����ַ���̫�̻ᱨ��
void UI_management::add()
{
	const char* title = "��������ϵ����Ϣ<���� �绰���� ��ַ>";
	settextstyle(36, 0, "����");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "����");	//Ӧ����run������
	AddButton->show();
	AddEdit->show();

	string str = AddEdit->text();
	//if(AddButton->IsClicked()){ }
	if (AddButton->IsClicked() && !str.empty() && name_isfull() != 1) {
		//FromString
		string name, telephone, address;
		stringstream ss(str);
		ss >> name >> telephone >> address;

		//������ʾ����Ϣ�ظ����Ѵ��ڣ�
		for (int i = 0; i < MAX_H; i++) {
			if (hash_name[i].name == name && hash_name[i].flag == 1)
			{
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "��Ϣ�ظ�����ϵ���Ѵ���", "��ʾ", MB_OKCANCEL);
				}
				AddEdit->clear();
				return;
			}
		}
			
		int key = key_name(name);  //�����������ֹ�ϣ���е�λ��
		if (hash_name[key].flag == 0)  //��ǰλ�ò���ͻ
		{
			hash_name[key].address = address; //������Ӳ���
			hash_name[key].name = name;
			hash_name[key].telephone = telephone;
			hash_name[key].name_key = key;
			hash_name[key].flag = 1;  //��Ǹ�λ���Ѿ�����
			if (AddButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "��ӳɹ�", "��ʾ", MB_OKCANCEL);
			}
			AddEdit->clear();
			return;
		}
		else  //��ǰλ�ó�ͻ
		{
			if (name_isfull() == 1)  //���ж��Ƿ����ֹ�ϣ���Ѿ�����
			{
				//printf("�𾴵Ŀͻ����ã����������Ϣ���ڵ����ֹ�ϣ���Ѿ����ˣ�����ϵ������Ա\n");
				//������ʾ
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "��ϵͳ�޴洢����", "��ʾ", MB_OKCANCEL);
				}
				AddEdit->clear();
				return;
			}
			else  //��������̽�취�����ͻ
			{
				key = method_name(key);
				hash_name[key].address = address; //������Ӳ���
				hash_name[key].name = name;
				hash_name[key].telephone = telephone;
				hash_name[key].name_key = key;
				hash_name[key].flag = 1;  //��Ǹ�λ���Ѿ�����
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "��ӳɹ�", "��ʾ", MB_OKCANCEL);
				}
				AddEdit->clear();
				return;
			}
		}
		
		int tele_key = key_tele(telephone);
		if (hash_tele[tele_key].flag == 0) //��ǰλ�ò���ͻ
		{
			hash_tele[tele_key].address = address; //������Ӳ���
			hash_tele[tele_key].name = name;
			hash_tele[tele_key].telephone = telephone;
			hash_tele[tele_key].tele_key = tele_key;
			hash_tele[tele_key].flag = 1;  //��Ǹ�λ���Ѿ�����
			if (AddButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "��ӳɹ�", "��ʾ", MB_OKCANCEL);
			}
			AddEdit->clear();
			return;
		}
		else
		{
			if (tele_isfull() == 1)
			{
				//printf("�𾴵Ŀͻ����ã����������Ϣ���ڵĵ绰��ϣ���Ѿ����ˣ�����ϵ������Ա\n");
				//������ʾ
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "��ϵͳ�޴洢����", "��ʾ", MB_OKCANCEL);
				}
				AddEdit->clear();
				return;
			}
			else {
				tele_key = method_tele(tele_key);
				hash_tele[tele_key].address = address; //������Ӳ���
				hash_tele[tele_key].name = name;
				hash_tele[tele_key].telephone = telephone;
				hash_tele[tele_key].tele_key = tele_key;
				hash_tele[tele_key].flag = 1;  //��Ǹ�λ���Ѿ�����
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "��ӳɹ�", "��ʾ", MB_OKCANCEL);
				}
				AddEdit->clear();
				return;
			}
		}
		//ShowTable->InsertData(AddEdit->text());
		//AddEdit->clear();
	}
}

void UI_management::earse()
{
	const char* title = "������Ҫɾ������ϵ������";
	settextstyle(36, 0, "����");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "����");	//Ӧ����run������
	DeleteButton->show();
	DeleteEdit->show();
	//if (DeleteTable->rows != 0) {
	//	//DeleteTable->show();
	//	DeleteTable->DrawHeader();
	//	DeleteTable->DrawTableGrid();
	//	DeleteTable->DrawTableData(hash_name);
	//}
	

	//�ж���ϵ���Ƿ����
	auto& str = DeleteEdit->text();
	if (!str.empty()) {
		int ret = inquire_name(str);
		if (ret < 0) {
			if (DeleteButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "��ϵ�˲�����", "��ʾ", MB_OKCANCEL);
				DeleteEdit->clear();
				return;
			}
		}
		else {
			//hash_name[ret].flag = 0;			��֪Ϊ�η�����ͻ���ʾ��ϵ�˲�����
			if (DeleteButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "ɾ���ɹ�", "��ʾ", MB_OKCANCEL);
				hash_name[ret].flag = 0;
				hash_tele[ret].flag = 0;
				DeleteEdit->clear();
				return;
			}
		}
	}
}

void UI_management::modify()
{
	const char* title = "������Ҫ�޸ĵ���ϵ������";
	settextstyle(36, 0, "����");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "����");	//Ӧ����run������
	ModifyEdit->show();

	if (isFind) {
		for (auto& p : UserEdit) {
			p->show();
		}
	}

	//����������
	//�ж���ϵ���Ƿ����
	auto& str = ModifyEdit->text();
	if (ModifyEdit->TextChange()) {
		int ret = inquire_name(str);
		if (ret < 0) {
			location = -1;
			isFind = false;
		}
		else {
			UserEdit[0]->SetText(hash_name[ret].name);
			UserEdit[1]->SetText(hash_name[ret].telephone);
			UserEdit[2]->SetText(hash_name[ret].address);
			isFind = true;
			//ModifyIt = it;
			location = ret;
			/*if (ModifyButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "�޸ĳɹ�", "��ʾ", MB_OKCANCEL);
				hash_name[ret].flag = 0;
				ModifyEdit->clear();
				return;
			}*/
		}
	}

	if (isFind && location != -1) {
		for (int i = 0; i < UserEdit.size(); ++i) {
			if (UserEdit[i]->TextChange()) {
				switch (i)
				{
				case 0:	
					hash_name[location].name = UserEdit[i]->text();
					hash_tele[location].name = UserEdit[i]->text();
					//ChangeByName(location);		�����þ��޷��޸�
					break;
				case 1:	
					hash_name[location].telephone = UserEdit[i]->text();
					hash_tele[location].telephone = UserEdit[i]->text();
					//CHangeByTele(location);
					break;
				case 2:
					hash_name[location].address = UserEdit[i]->text();
					hash_tele[location].address = UserEdit[i]->text();
					break;
				default:
					break;
				}
				//UpdateShowTable();
			}
		}
	}
}

void UI_management::SearchByName()
{
	const char* title = "������Ҫ��ѯ����ϵ������";
	settextstyle(36, 0, "����");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "����");	//Ӧ����run������
	SearchNameButton->show();
	SearchNameEdit->show();

	//�ж���ϵ���Ƿ����
	auto& str = SearchNameEdit->text();
	if (!str.empty()) {
		int ret = inquire_name(str);
		if (ret < 0) {
			if (SearchNameButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "��ϵ�˲�����", "��ʾ", MB_OKCANCEL);
				SearchNameEdit->clear();
				return;
			}
		}
		else {
			int x;
			int y = 400;
			int rows = 1;
			int cols = 3;
			int GridWidth = 300;      //���ӿ��
			int GridHeight = 80;     //���Ӹ߶�
			int hh = 40;		//ͷ����Ϣ���߶�

			/*int tx = (UI_window::GetWidth() - ShowTable->GetWidth()) / 2;
			int ty = (UI_window::GetHeight() - ShowTable->GetHeight()) / 2;
			ShowTable->move(tx, ty);*/
			x = (UI_window::GetWidth() - 3 * GridWidth) / 2;

			setlinestyle(PS_SOLID, 2);
			::rectangle(x, y - hh, x + GridWidth*3, y);
			for (int i = 0; i < cols; ++i) {
				line(x + i * GridWidth + 1, y - hh, x + i * GridWidth + 1, y);
			}
			setlinestyle(PS_SOLID, 1);
			int SpaceH, SpaceV;
			int fix = 7;		//�ֶ�����
			SpaceH = (GridWidth - ::textwidth("����")) / 2;
			SpaceV = (hh - ::textheight("����")) / 2;
			outtextxy(x + 0 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "����");
			SpaceH = (GridWidth - ::textwidth("�绰����")) / 2;
			//SpaceV = (hh - ::textheight("�绰����")) / 2;
			outtextxy(x + 1 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "�绰����");
			SpaceH = (GridWidth - ::textwidth("��ַ")) / 2;
			//SpaceV = (hh - ::textheight("��ַ")) / 2;
			outtextxy(x + 2 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "��ַ");

			setlinecolor(BLACK);
			//������
			for (size_t i = 0; i < rows + 1; ++i) {
				line(x, y + i * GridHeight, x + cols * GridWidth, y + i * GridHeight);
			}
			//������
			for (size_t i = 0; i < cols + 1; ++i) {
				line(x + i * GridWidth, y, x + i * GridWidth, y + rows * GridHeight);
			}

			//����
			int tx = x + 0 * GridWidth + (GridWidth - ::textwidth(hash_name[ret].name.c_str())) / 2;
			int ty = y + (GridHeight - ::textheight(hash_name[ret].name.c_str())) / 2;
			outtextxy(tx, ty, hash_name[ret].name.c_str());
			//�绰����
			tx = x + 1 * GridWidth + (GridWidth - ::textwidth(hash_name[ret].telephone.c_str())) / 2;
			//ty = y + count * GridHeight + (GridHeight - ::textheight(hash_name[i].telephone.c_str())) / 2;
			outtextxy(tx, ty, hash_name[ret].telephone.c_str());
			//סַ
			tx = x + 2 * GridWidth + (GridWidth - ::textwidth(hash_name[ret].address.c_str())) / 2;
			//ty = y + count * GridHeight + (GridHeight - ::textheight(hash_name[i].address.c_str())) / 2;
			outtextxy(tx, ty, hash_name[ret].address.c_str());
		}
	}
}

void UI_management::SearchByTele()
{
	const char* title = "������Ҫ��ѯ����ϵ�˵绰����";
	settextstyle(36, 0, "����");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "����");	//Ӧ����run������
	SearchTeleButton->show();
	SearchTeleEdit->show();

	//�ж���ϵ���Ƿ����
	auto& str = SearchTeleEdit->text();
	if (!str.empty()) {
		int ret = inquire_tele(str);
		if (ret < 0) {
			if (SearchTeleButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "��ϵ�˲�����", "��ʾ", MB_OKCANCEL);
				SearchTeleEdit->clear();
				return;
			}
		}
		else {
			int x;
			int y = 400;
			int rows = 1;
			int cols = 3;
			int GridWidth = 300;      //���ӿ��
			int GridHeight = 80;     //���Ӹ߶�
			int hh = 40;		//ͷ����Ϣ���߶�

			/*int tx = (UI_window::GetWidth() - ShowTable->GetWidth()) / 2;
			int ty = (UI_window::GetHeight() - ShowTable->GetHeight()) / 2;
			ShowTable->move(tx, ty);*/
			x = (UI_window::GetWidth() - 3 * GridWidth) / 2;

			setlinestyle(PS_SOLID, 2);
			::rectangle(x, y - hh, x + GridWidth * 3, y);
			for (int i = 0; i < cols; ++i) {
				line(x + i * GridWidth + 1, y - hh, x + i * GridWidth + 1, y);
			}
			setlinestyle(PS_SOLID, 1);
			int SpaceH, SpaceV;
			int fix = 7;		//�ֶ�����
			SpaceH = (GridWidth - ::textwidth("����")) / 2;
			SpaceV = (hh - ::textheight("����")) / 2;
			outtextxy(x + 0 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "����");
			SpaceH = (GridWidth - ::textwidth("�绰����")) / 2;
			//SpaceV = (hh - ::textheight("�绰����")) / 2;
			outtextxy(x + 1 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "�绰����");
			SpaceH = (GridWidth - ::textwidth("��ַ")) / 2;
			//SpaceV = (hh - ::textheight("��ַ")) / 2;
			outtextxy(x + 2 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "��ַ");

			setlinecolor(BLACK);
			//������
			for (size_t i = 0; i < rows + 1; ++i) {
				line(x, y + i * GridHeight, x + cols * GridWidth, y + i * GridHeight);
			}
			//������
			for (size_t i = 0; i < cols + 1; ++i) {
				line(x + i * GridWidth, y, x + i * GridWidth, y + rows * GridHeight);
			}

			//����
			int tx = x + 0 * GridWidth + (GridWidth - ::textwidth(hash_tele[ret].name.c_str())) / 2;
			int ty = y + (GridHeight - ::textheight(hash_tele[ret].name.c_str())) / 2;
			outtextxy(tx, ty, hash_tele[ret].name.c_str());
			//�绰����
			tx = x + 1 * GridWidth + (GridWidth - ::textwidth(hash_tele[ret].telephone.c_str())) / 2;
			//ty = y + count * GridHeight + (GridHeight - ::textheight(hash_tele[i].telephone.c_str())) / 2;
			outtextxy(tx, ty, hash_tele[ret].telephone.c_str());
			//סַ
			tx = x + 2 * GridWidth + (GridWidth - ::textwidth(hash_tele[ret].address.c_str())) / 2;
			//ty = y + count * GridHeight + (GridHeight - ::textheight(hash_tele[i].address.c_str())) / 2;
			outtextxy(tx, ty, hash_tele[ret].address.c_str());
		}
	}
}

//display
void UI_management::traverse()
{
	//ShowTable->show();
	ShowTable->UpdatePage(hash_name);	//�����������extra?
	ShowTable->DrawHeader();
	ShowTable->DrawTableGrid();
	ShowTable->DrawTableData(hash_name);
}

void UI_management::surplus()
{
	ShowSurplusButton->show();
	if (ShowSurplusButton->IsClicked()) {
		int count = 0;
		for (int i = 0; i < MAX_H; ++i) {
			if (hash_name[i].flag == 1) {
				++count;
			}
		}
		string str = "��ǰϵͳ�洢��ϵ����Ϊ" + to_string(count);
		HWND hw = GetHWnd();
		MessageBox(hw, str.c_str(), "��ʾ", MB_OKCANCEL);
	}
}

void UI_management::clearall()
{
	ClearButton->show();
	if (ClearButton->IsClicked()) {
		char buf[128];
		InputBox(buf, 128, "���������Ա����", "Ȩ����֤");
		int len = strlen(buf);
		string code(buf, len);
		if (code == "666666") {
			for (int i = 0; i < MAX_H; i++)
			{
				hash_name[i].flag = 0;
				hash_tele[i].flag = 0;
			}
			HWND hw = GetHWnd();
			MessageBox(hw, "�����ɹ�", "��ʾ", MB_OKCANCEL);
		}
		else {
			HWND hw = GetHWnd();
			MessageBox(hw, "����Ա�����֤ʧ�ܣ���Ȩ������ļ�", "��ʾ", MB_OKCANCEL);
		}
	}
}

void UI_management::ChangeByName(int location)
{
	string name = hash_name[location].name;
	int key = key_name(name);  //�����������ֹ�ϣ���е�λ��
	if (hash_name[key].flag == 0)  //��ǰλ�ò���ͻ
	{
	}
	else {		//��������̽�취�����ͻ
		key = method_name(key);
	}
	hash_name[location].name_key = key;
	hash_name[key] = hash_name[location];
	hash_name[location].flag = 0;
	/*if (AddButton->IsClicked()) {
		HWND hw = GetHWnd();
		MessageBox(hw, "�޸ĳɹ�", "��ʾ", MB_OKCANCEL);
	}*/
}

void UI_management::CHangeByTele(int location)
{
	string telephone = hash_tele[location].telephone;
	int tele_key = key_tele(telephone);
	if (hash_tele[tele_key].flag == 0) //��ǰλ�ò���ͻ
	{
	}
	else {
		tele_key = method_tele(tele_key);
	}
	hash_tele[location].tele_key = tele_key;
	hash_tele[tele_key] = hash_name[location];
	hash_tele[location].flag = 0;
}

void UI_management::DrawBackground()
{
	::putimage(0, 0, &bk);
}

void UI_management::EventLoop()
{
	::settextstyle(20, 0, "����");
	//ShowTable->show();
	/*Table p;
	p.DrawTableGrid();
	p.DrawTableData(hash_name);*/
	ShowTable->event();

	AddButton->event();
	AddEdit->event();

	DeleteButton->event();
	DeleteEdit->event();
	//DeleteTable->event();

	ModifyEdit->event();
	for (auto& p : UserEdit) {
		p->event();
	}

	SearchNameButton->event();
	SearchNameEdit->event();

	SearchTeleButton->event();
	SearchTeleEdit->event();

	ShowSurplusButton->event();

	ClearButton->event();
}

void UI_management::init()
{
	for (int i = 0; i < MAX_H; i++)
	{
		hash_name[i].flag = 0;  //��ֵΪ0����ʾδ����
		hash_tele[i].flag = 0;
	}
}

//�п��෵��0����������1
bool UI_management::name_isfull()
{
	int flag = 1;
	for (int i = 0; i < MAX_H; i++)
		if (hash_name[i].flag == 0) return 0;  //�п���λ�ã�ֱ�ӷ���0
	return 1;
}

//�п��෵��0����������1
bool UI_management::tele_isfull()
{
	int flag = 1;
	for (int i = 0; i < MAX_H; i++)
		if (hash_tele[i].flag == 0) return 0;  //�п���λ�ã�ֱ�ӷ���0
	return 1;
}

int UI_management::key_name(string name)
{
	int len = name.size();
	int key = (name[0] + name[len - 1] - '\0') % DIV;

	return key;
}

int UI_management::key_tele(string telephone)
{
	int len = telephone.size();
	int key = (telephone[len - 4] - '0') + (telephone[len - 3] - '0') + (telephone[len - 2] - '0') + (telephone[len - 1] - '0');

	return key;
}

int UI_management::method_name(int key)
{
	int i;
	for (i = 1; (i + key) % MAX_H < MAX_H; i++)
		if (hash_name[(i + key) % MAX_H].flag == 0) return ((i + key) % MAX_H);
}

int UI_management::method_tele(int key)
{
	int i;
	for (i = 1; (i + key) % MAX_H < MAX_H; i++)
		if (hash_tele[(i + key) % MAX_H].flag == 0) return ((i + key) % MAX_H);
}

void UI_management::LoadFile(const string& filename)
{
	ifstream file(filename, ios::in);

	if (!file.is_open()) {
		return;
	}

	//����ͷ
	//char buf[1024] = { 0 };
	//file.getline(buf, 1024);
	//header_str = buf;

	string name, telephone, address;
	while (file >> name && file >> telephone && file >> address) {
		//������Ϊkey
		int key = key_name(name);		//�����������ֹ�ϣ���е�λ��
		if (hash_name[key].flag == 0)	//��ǰλ�ò���ͻ
		{
			hash_name[key].address = address; //������Ӳ���
			hash_name[key].name = name;
			hash_name[key].telephone = telephone;
			hash_name[key].name_key = key;
			hash_name[key].flag = 1;  //��Ǹ�λ���Ѿ�����
		}
		else  //��ǰλ�ó�ͻ
		{
			if (name_isfull() == 1)  //���ж��Ƿ����ֹ�ϣ���Ѿ�����
				//printf("�𾴵Ŀͻ����ã����������Ϣ���ڵ����ֹ�ϣ���Ѿ����ˣ�����ϵ������Ա\n");
				;
			else  //��������̽�취�����ͻ
			{
				key = method_name(key);
				hash_name[key].address = address; //������Ӳ���
				hash_name[key].name = name;
				hash_name[key].telephone = telephone;
				hash_name[key].name_key = key;
				hash_name[key].flag = 1;  //��Ǹ�λ���Ѿ�����
			}
		}

		//�Ժ���Ϊkey
		key = key_tele(telephone);  //����ڹ�ϣ���еĵ�ַ
		if (hash_tele[key].flag == 0) //��ǰλ�ò���ͻ
		{
			hash_tele[key].address = address; //������Ӳ���
			hash_tele[key].name = name;
			hash_tele[key].telephone = telephone;
			hash_tele[key].tele_key =key;
			hash_tele[key].flag = 1;  //��Ǹ�λ���Ѿ�����
		}
		else
		{
			if (tele_isfull() == 1)
				//printf("�𾴵Ŀͻ����ã����������Ϣ���ڵĵ绰��ϣ���Ѿ����ˣ�����ϵ������Ա\n");
				;
			else {
				key = method_tele(key);
				hash_tele[key].address = address; //������Ӳ���
				hash_tele[key].name = name;
				hash_tele[key].telephone = telephone;
				hash_tele[key].tele_key = key;
				hash_tele[key].flag = 1;  //��Ǹ�λ���Ѿ�����
			}
		}
	}

	file.close();
}

void UI_management::SaveFile(const string& filename)
{
	ofstream file(filename, ios::out | ios::trunc);

	if (!file.is_open()) {
		return;
	}

	//д��ͷ
	//header_str += "\n";
	//file.write(header_str.c_str(), header_str.size());

	//д����          
	for (int i = 0; i < MAX_H; i++)
	{
		if (hash_name[i].flag == 1) {
			file << hash_name[i].name << " " << hash_name[i].telephone << " " << hash_name[i].address << endl;
		}
	}

	file.close();
}

int UI_management::inquire_name(string name)
{
	int j = key_name(name);
	if (hash_name[j].name == name && hash_name[j].flag == 1) return j;   //�������ͻֱ�ӷ���

	for (int i = 0; i < MAX_H; i++)
	{
		if (hash_name[i].name == name && hash_name[i].flag == 1)
			return i;
	}

	return -1;  //û�ҵ����ش�����Ϣ
}

int UI_management::inquire_tele(string telephone)
{
	int j = key_tele(telephone);
	if (telephone == hash_tele[j].telephone && hash_tele[j].flag == 1) return j;

	for (int i = 0; i < MAX_H; i++)
	{
		if (telephone == hash_tele[i].telephone && hash_tele[i].flag == 1)
			return i;
	}

	return -1;  //����ʧ�ܷ��ش�����Ϣ
}

void UI_management::UpdateShowTable()
{
}

