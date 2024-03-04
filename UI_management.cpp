#include "UI_management.h"
#include "UI_window.h"
#include "user.h"

UI_management::UI_management()
{
	init();
	LoadFile("./文件保存测试.txt");
	header_str = "姓名 电话号码 住址";
	::loadimage(&bk, "./绿.jpg", UI_window::GetWidth(), UI_window::GetHeight());
	::settextstyle(20, 0, "楷体");

	//主界面初始化
	menu_buttons.emplace_back(new PushButton("添加"));
	menu_buttons.emplace_back(new PushButton("删除"));
	menu_buttons.emplace_back(new PushButton("修改"));
	menu_buttons.emplace_back(new PushButton("按姓名查找"));
	menu_buttons.emplace_back(new PushButton("按电话号码查找"));
	menu_buttons.emplace_back(new PushButton("查看所有信息"));
	menu_buttons.emplace_back(new PushButton("显示当前容量"));
	menu_buttons.emplace_back(new PushButton("清空所有信息"));
	menu_buttons.emplace_back(new PushButton("退出系统"));
	for (int i = 0; i < menu_buttons.size(); ++i) {
		menu_buttons[i]->SetFixedSize(250, 50);
		int bx = (UI_window::GetWidth() - menu_buttons[i]->GetWidth()) / 2;
		int by = (UI_window::GetHeight() - menu_buttons.size() * menu_buttons[i]->GetHeight()) / 2 + i * menu_buttons[i]->GetHeight();
		menu_buttons[i]->move(bx, by);
	}

	//初始化查看用户的表格
	ShowTable.reset(new Table);
	ShowTable->SetRowCount(11);
	ShowTable->SetHeader(header_str);
	//表格居中
	//int tx = (UI_window::GetWidth() - ShowTable->cols * ShowTable->GridWidth) / 2;
	//int ty = (UI_window::GetHeight() - ShowTable->rows * ShowTable->GridHeight) / 2;
	int tx = (UI_window::GetWidth() - ShowTable->GetWidth()) / 2;
	int ty = (UI_window::GetHeight() - ShowTable->GetHeight()) / 2;
	ShowTable->move(tx, ty);

	//可能得移到DrawTableData里
	//for (int i = 0; i < MAX_H; ++i) {
	//	if (hash_name[i].flag == 1) {
	//		//一个用户即为一行数据
	//		ShowTable->InsertData(hash_name[i]);
	//	}
	//}

	//添加联系人
	AddButton.reset(new PushButton("添加", 1000, 260, 80, 40));
	AddEdit.reset(new LineEdit(400, 260, 500, 40));
	AddEdit->SetTitle("请输入联系人信息");
	AddEdit->SetHitText("请按照<姓名 电话号码 地址>格式输入信息");

	//删除联系人
	DeleteButton.reset(new PushButton("删除", 1000, 260, 80, 40));
	DeleteEdit.reset(new LineEdit(400, 260, 500, 40));
	DeleteEdit->SetTitle("提示");
	DeleteEdit->SetHitText("请输入要删除的联系人姓名");
	//DeleteTable.reset(new Table);
	//DeleteTable->SetHeader(header_str);
	//DeleteTable->move(DeleteEdit->GetX(), DeleteEdit->GetY() + 120);
	//DeleteTable->SetRowCount(1);

	//修改联系人信息
	ModifyEdit.reset(new LineEdit(400, 260, 500, 40));
	ModifyEdit->move((UI_window::GetWidth() - ModifyEdit->GetWidth()) / 2, 260);
	int x = (UI_window::GetWidth() - 200 * 3) / 2;
	for (int i = 0; i < 3; ++i) {
		UserEdit.emplace_back(new LineEdit);
		UserEdit[i]->SetFixedSize(200, 40);
		UserEdit[i]->move(x + i * UserEdit[i]->GetWidth(), ModifyEdit->GetY() + 50);
	}
	location = -1;

	//按姓名查询联系人
	SearchNameButton.reset(new PushButton("查询", 1000, 260, 80, 40));
	SearchNameEdit.reset(new LineEdit(400, 260, 500, 40));
	SearchNameEdit->SetTitle("提示");
	SearchNameEdit->SetHitText("请输入要查询的联系人姓名");

	//按姓名查询联系人
	SearchTeleButton.reset(new PushButton("查询", 1000, 260, 80, 40));
	SearchTeleEdit.reset(new LineEdit(400, 260, 500, 40));
	SearchTeleEdit->SetTitle("提示");
	SearchTeleEdit->SetHitText("请输入要查询的联系人电话号码");

	//显示余量
	int bx = (UI_window::GetWidth() - 80) / 2;
	ShowSurplusButton.reset(new PushButton("显示", bx, 260, 80, 40));

	//清空
	int bbx = (UI_window::GetWidth() - 80) / 2;
	ClearButton.reset(new PushButton("清空", bbx, 260, 80, 40));
}

void UI_management::run()
{
	//::settextstyle(20, 0, "楷体");
	//获取菜单返回值
	int op = 66;
	UI_window::BeginDraw();
	while (true) {
		UI_window::clear();
		DrawBackground();
		
		if (UI_window::HasMsg()) {
			switch (UI_window::GetMsg().message)
			{
			case WM_KEYDOWN:	//按下按键
				//按ESC键退出操作，返回主界面
				if (UI_window::GetMsg().vkcode == VK_ESCAPE) {
					cout << "escape" << endl;
					op = 66;
				}
				break;
			default:			//鼠标操作
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
			SaveFile("./文件保存测试.txt");
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

//根据计算key值的函数，姓名、电话号码字符串太短会报错；
void UI_management::add()
{
	const char* title = "请输入联系人信息<姓名 电话号码 地址>";
	settextstyle(36, 0, "楷体");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "楷体");	//应该在run里设置
	AddButton->show();
	AddEdit->show();

	string str = AddEdit->text();
	//if(AddButton->IsClicked()){ }
	if (AddButton->IsClicked() && !str.empty() && name_isfull() != 1) {
		//FromString
		string name, telephone, address;
		stringstream ss(str);
		ss >> name >> telephone >> address;

		//弹窗提示：信息重复（已存在）
		for (int i = 0; i < MAX_H; i++) {
			if (hash_name[i].name == name && hash_name[i].flag == 1)
			{
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "信息重复，联系人已存在", "提示", MB_OKCANCEL);
				}
				AddEdit->clear();
				return;
			}
		}
			
		int key = key_name(name);  //计算其在名字哈希表中的位置
		if (hash_name[key].flag == 0)  //当前位置不冲突
		{
			hash_name[key].address = address; //进行添加操作
			hash_name[key].name = name;
			hash_name[key].telephone = telephone;
			hash_name[key].name_key = key;
			hash_name[key].flag = 1;  //标记该位置已经有数
			if (AddButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "添加成功", "提示", MB_OKCANCEL);
			}
			AddEdit->clear();
			return;
		}
		else  //当前位置冲突
		{
			if (name_isfull() == 1)  //先判断是否名字哈希表已经满了
			{
				//printf("尊敬的客户您好，您输入的信息所在的名字哈希表已经满了，请联系工作人员\n");
				//弹窗提示
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "该系统无存储余量", "提示", MB_OKCANCEL);
				}
				AddEdit->clear();
				return;
			}
			else  //利用线性探察法解决冲突
			{
				key = method_name(key);
				hash_name[key].address = address; //进行添加操作
				hash_name[key].name = name;
				hash_name[key].telephone = telephone;
				hash_name[key].name_key = key;
				hash_name[key].flag = 1;  //标记该位置已经有数
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "添加成功", "提示", MB_OKCANCEL);
				}
				AddEdit->clear();
				return;
			}
		}
		
		int tele_key = key_tele(telephone);
		if (hash_tele[tele_key].flag == 0) //当前位置不冲突
		{
			hash_tele[tele_key].address = address; //进行添加操作
			hash_tele[tele_key].name = name;
			hash_tele[tele_key].telephone = telephone;
			hash_tele[tele_key].tele_key = tele_key;
			hash_tele[tele_key].flag = 1;  //标记该位置已经有数
			if (AddButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "添加成功", "提示", MB_OKCANCEL);
			}
			AddEdit->clear();
			return;
		}
		else
		{
			if (tele_isfull() == 1)
			{
				//printf("尊敬的客户您好，您输入的信息所在的电话哈希表已经满了，请联系工作人员\n");
				//弹窗提示
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "该系统无存储余量", "提示", MB_OKCANCEL);
				}
				AddEdit->clear();
				return;
			}
			else {
				tele_key = method_tele(tele_key);
				hash_tele[tele_key].address = address; //进行添加操作
				hash_tele[tele_key].name = name;
				hash_tele[tele_key].telephone = telephone;
				hash_tele[tele_key].tele_key = tele_key;
				hash_tele[tele_key].flag = 1;  //标记该位置已经有数
				if (AddButton->IsClicked()) {
					HWND hw = GetHWnd();
					MessageBox(hw, "添加成功", "提示", MB_OKCANCEL);
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
	const char* title = "请输入要删除的联系人姓名";
	settextstyle(36, 0, "楷体");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "楷体");	//应该在run里设置
	DeleteButton->show();
	DeleteEdit->show();
	//if (DeleteTable->rows != 0) {
	//	//DeleteTable->show();
	//	DeleteTable->DrawHeader();
	//	DeleteTable->DrawTableGrid();
	//	DeleteTable->DrawTableData(hash_name);
	//}
	

	//判断联系人是否存在
	auto& str = DeleteEdit->text();
	if (!str.empty()) {
		int ret = inquire_name(str);
		if (ret < 0) {
			if (DeleteButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "联系人不存在", "提示", MB_OKCANCEL);
				DeleteEdit->clear();
				return;
			}
		}
		else {
			//hash_name[ret].flag = 0;			不知为何放这里就会提示联系人不存在
			if (DeleteButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "删除成功", "提示", MB_OKCANCEL);
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
	const char* title = "请输入要修改的联系人姓名";
	settextstyle(36, 0, "楷体");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "楷体");	//应该在run里设置
	ModifyEdit->show();

	if (isFind) {
		for (auto& p : UserEdit) {
			p->show();
		}
	}

	//按姓名查找
	//判断联系人是否存在
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
				MessageBox(hw, "修改成功", "提示", MB_OKCANCEL);
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
					//ChangeByName(location);		？调用就无法修改
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
	const char* title = "请输入要查询的联系人姓名";
	settextstyle(36, 0, "楷体");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "楷体");	//应该在run里设置
	SearchNameButton->show();
	SearchNameEdit->show();

	//判断联系人是否存在
	auto& str = SearchNameEdit->text();
	if (!str.empty()) {
		int ret = inquire_name(str);
		if (ret < 0) {
			if (SearchNameButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "联系人不存在", "提示", MB_OKCANCEL);
				SearchNameEdit->clear();
				return;
			}
		}
		else {
			int x;
			int y = 400;
			int rows = 1;
			int cols = 3;
			int GridWidth = 300;      //格子宽度
			int GridHeight = 80;     //格子高度
			int hh = 40;		//头部信息栏高度

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
			int fix = 7;		//手动调整
			SpaceH = (GridWidth - ::textwidth("姓名")) / 2;
			SpaceV = (hh - ::textheight("姓名")) / 2;
			outtextxy(x + 0 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "姓名");
			SpaceH = (GridWidth - ::textwidth("电话号码")) / 2;
			//SpaceV = (hh - ::textheight("电话号码")) / 2;
			outtextxy(x + 1 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "电话号码");
			SpaceH = (GridWidth - ::textwidth("地址")) / 2;
			//SpaceV = (hh - ::textheight("地址")) / 2;
			outtextxy(x + 2 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "地址");

			setlinecolor(BLACK);
			//画横线
			for (size_t i = 0; i < rows + 1; ++i) {
				line(x, y + i * GridHeight, x + cols * GridWidth, y + i * GridHeight);
			}
			//画竖线
			for (size_t i = 0; i < cols + 1; ++i) {
				line(x + i * GridWidth, y, x + i * GridWidth, y + rows * GridHeight);
			}

			//姓名
			int tx = x + 0 * GridWidth + (GridWidth - ::textwidth(hash_name[ret].name.c_str())) / 2;
			int ty = y + (GridHeight - ::textheight(hash_name[ret].name.c_str())) / 2;
			outtextxy(tx, ty, hash_name[ret].name.c_str());
			//电话号码
			tx = x + 1 * GridWidth + (GridWidth - ::textwidth(hash_name[ret].telephone.c_str())) / 2;
			//ty = y + count * GridHeight + (GridHeight - ::textheight(hash_name[i].telephone.c_str())) / 2;
			outtextxy(tx, ty, hash_name[ret].telephone.c_str());
			//住址
			tx = x + 2 * GridWidth + (GridWidth - ::textwidth(hash_name[ret].address.c_str())) / 2;
			//ty = y + count * GridHeight + (GridHeight - ::textheight(hash_name[i].address.c_str())) / 2;
			outtextxy(tx, ty, hash_name[ret].address.c_str());
		}
	}
}

void UI_management::SearchByTele()
{
	const char* title = "请输入要查询的联系人电话号码";
	settextstyle(36, 0, "楷体");
	outtextxy((UI_window::GetWidth() - textwidth(title)) / 2, 150, title);
	::settextstyle(20, 0, "楷体");	//应该在run里设置
	SearchTeleButton->show();
	SearchTeleEdit->show();

	//判断联系人是否存在
	auto& str = SearchTeleEdit->text();
	if (!str.empty()) {
		int ret = inquire_tele(str);
		if (ret < 0) {
			if (SearchTeleButton->IsClicked()) {
				HWND hw = GetHWnd();
				MessageBox(hw, "联系人不存在", "提示", MB_OKCANCEL);
				SearchTeleEdit->clear();
				return;
			}
		}
		else {
			int x;
			int y = 400;
			int rows = 1;
			int cols = 3;
			int GridWidth = 300;      //格子宽度
			int GridHeight = 80;     //格子高度
			int hh = 40;		//头部信息栏高度

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
			int fix = 7;		//手动调整
			SpaceH = (GridWidth - ::textwidth("姓名")) / 2;
			SpaceV = (hh - ::textheight("姓名")) / 2;
			outtextxy(x + 0 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "姓名");
			SpaceH = (GridWidth - ::textwidth("电话号码")) / 2;
			//SpaceV = (hh - ::textheight("电话号码")) / 2;
			outtextxy(x + 1 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "电话号码");
			SpaceH = (GridWidth - ::textwidth("地址")) / 2;
			//SpaceV = (hh - ::textheight("地址")) / 2;
			outtextxy(x + 2 * GridWidth + SpaceH, y - GridHeight / 2 + fix, "地址");

			setlinecolor(BLACK);
			//画横线
			for (size_t i = 0; i < rows + 1; ++i) {
				line(x, y + i * GridHeight, x + cols * GridWidth, y + i * GridHeight);
			}
			//画竖线
			for (size_t i = 0; i < cols + 1; ++i) {
				line(x + i * GridWidth, y, x + i * GridWidth, y + rows * GridHeight);
			}

			//姓名
			int tx = x + 0 * GridWidth + (GridWidth - ::textwidth(hash_tele[ret].name.c_str())) / 2;
			int ty = y + (GridHeight - ::textheight(hash_tele[ret].name.c_str())) / 2;
			outtextxy(tx, ty, hash_tele[ret].name.c_str());
			//电话号码
			tx = x + 1 * GridWidth + (GridWidth - ::textwidth(hash_tele[ret].telephone.c_str())) / 2;
			//ty = y + count * GridHeight + (GridHeight - ::textheight(hash_tele[i].telephone.c_str())) / 2;
			outtextxy(tx, ty, hash_tele[ret].telephone.c_str());
			//住址
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
	ShowTable->UpdatePage(hash_name);	//调用这个更新extra?
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
		string str = "当前系统存储联系人数为" + to_string(count);
		HWND hw = GetHWnd();
		MessageBox(hw, str.c_str(), "提示", MB_OKCANCEL);
	}
}

void UI_management::clearall()
{
	ClearButton->show();
	if (ClearButton->IsClicked()) {
		char buf[128];
		InputBox(buf, 128, "请输入管理员密码", "权限验证");
		int len = strlen(buf);
		string code(buf, len);
		if (code == "666666") {
			for (int i = 0; i < MAX_H; i++)
			{
				hash_name[i].flag = 0;
				hash_tele[i].flag = 0;
			}
			HWND hw = GetHWnd();
			MessageBox(hw, "操作成功", "提示", MB_OKCANCEL);
		}
		else {
			HWND hw = GetHWnd();
			MessageBox(hw, "管理员身份验证失败，无权限清空文件", "提示", MB_OKCANCEL);
		}
	}
}

void UI_management::ChangeByName(int location)
{
	string name = hash_name[location].name;
	int key = key_name(name);  //计算其在名字哈希表中的位置
	if (hash_name[key].flag == 0)  //当前位置不冲突
	{
	}
	else {		//利用线性探察法解决冲突
		key = method_name(key);
	}
	hash_name[location].name_key = key;
	hash_name[key] = hash_name[location];
	hash_name[location].flag = 0;
	/*if (AddButton->IsClicked()) {
		HWND hw = GetHWnd();
		MessageBox(hw, "修改成功", "提示", MB_OKCANCEL);
	}*/
}

void UI_management::CHangeByTele(int location)
{
	string telephone = hash_tele[location].telephone;
	int tele_key = key_tele(telephone);
	if (hash_tele[tele_key].flag == 0) //当前位置不冲突
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
	::settextstyle(20, 0, "楷体");
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
		hash_name[i].flag = 0;  //赋值为0，表示未放数
		hash_tele[i].flag = 0;
	}
}

//有空余返回0，表满返回1
bool UI_management::name_isfull()
{
	int flag = 1;
	for (int i = 0; i < MAX_H; i++)
		if (hash_name[i].flag == 0) return 0;  //有空余位置，直接返回0
	return 1;
}

//有空余返回0，表满返回1
bool UI_management::tele_isfull()
{
	int flag = 1;
	for (int i = 0; i < MAX_H; i++)
		if (hash_tele[i].flag == 0) return 0;  //有空余位置，直接返回0
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

	//读表头
	//char buf[1024] = { 0 };
	//file.getline(buf, 1024);
	//header_str = buf;

	string name, telephone, address;
	while (file >> name && file >> telephone && file >> address) {
		//以姓名为key
		int key = key_name(name);		//计算其在名字哈希表中的位置
		if (hash_name[key].flag == 0)	//当前位置不冲突
		{
			hash_name[key].address = address; //进行添加操作
			hash_name[key].name = name;
			hash_name[key].telephone = telephone;
			hash_name[key].name_key = key;
			hash_name[key].flag = 1;  //标记该位置已经有数
		}
		else  //当前位置冲突
		{
			if (name_isfull() == 1)  //先判断是否名字哈希表已经满了
				//printf("尊敬的客户您好，您输入的信息所在的名字哈希表已经满了，请联系工作人员\n");
				;
			else  //利用线性探察法解决冲突
			{
				key = method_name(key);
				hash_name[key].address = address; //进行添加操作
				hash_name[key].name = name;
				hash_name[key].telephone = telephone;
				hash_name[key].name_key = key;
				hash_name[key].flag = 1;  //标记该位置已经有数
			}
		}

		//以号码为key
		key = key_tele(telephone);  //算出在哈希表中的地址
		if (hash_tele[key].flag == 0) //当前位置不冲突
		{
			hash_tele[key].address = address; //进行添加操作
			hash_tele[key].name = name;
			hash_tele[key].telephone = telephone;
			hash_tele[key].tele_key =key;
			hash_tele[key].flag = 1;  //标记该位置已经有数
		}
		else
		{
			if (tele_isfull() == 1)
				//printf("尊敬的客户您好，您输入的信息所在的电话哈希表已经满了，请联系工作人员\n");
				;
			else {
				key = method_tele(key);
				hash_tele[key].address = address; //进行添加操作
				hash_tele[key].name = name;
				hash_tele[key].telephone = telephone;
				hash_tele[key].tele_key = key;
				hash_tele[key].flag = 1;  //标记该位置已经有数
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

	//写表头
	//header_str += "\n";
	//file.write(header_str.c_str(), header_str.size());

	//写数据          
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
	if (hash_name[j].name == name && hash_name[j].flag == 1) return j;   //如果不冲突直接返回

	for (int i = 0; i < MAX_H; i++)
	{
		if (hash_name[i].name == name && hash_name[i].flag == 1)
			return i;
	}

	return -1;  //没找到返回错误信息
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

	return -1;  //查找失败返回错误信息
}

void UI_management::UpdateShowTable()
{
}

