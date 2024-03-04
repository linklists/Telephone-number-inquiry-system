#include "Table.h"
#include "user.h"

Table::Table(int row, int col)
	:BasicWidget(0, 0, 0, 0), rows(row), cols(col),
	CurPage(0), MaxPage(0), ExtraData(0)
{
	//Ĭ��
	GridWidth = ::textwidth("ֻ�����ֶ�����ÿ��Ŀ��");
	GridHeight = 50;

	PreButton = new PushButton("��һҳ");
	NextButton = new PushButton("��һҳ");
	FirstButton = new PushButton("��һҳ");
	LastButton = new PushButton("��βҳ");
}

Table::~Table()
{
	delete PreButton;
	delete NextButton;
	delete FirstButton;
	delete LastButton;
}

void Table::SetRowCount(int row)
{
	rows = row;
}

void Table::SetColCount(int col)
{
	cols = col;
}

void Table::SetHeader(const string& header)
{
	this->header = header;
	cols = 3;

	////�����ֵĿ�Ⱥ͸߶�
	//GridWidth = ::textwidth("ֻ�����ֶ�����ÿ��Ŀ��");
	////GridHeight = ::textheight(header.c_str());
	//GridHeight = 50;
	//ȷ������ж����С���

	TextWidth = ::textwidth("ֻ�����ֶ�����ÿ��Ŀ��");
	TextHeight = 40;
	//�ø��ӱ����ִ�һ�㣨��ʵ��Ĭ��д���ģ�
	GridWidth = TextWidth + 5;
	GridHeight = TextHeight + 5;
	width = GridWidth * cols;
	height = GridHeight * (rows + 1);
}

void Table::InsertData(const user& data)
{
	
}

void Table::show()
{
	//DrawTableGrid();
	//DrawTableData(user* hash_name);
}

void Table::DrawTableGrid()
{
	////ȷ������ж����С���
	setlinecolor(BLACK);
	//GridWidth = ::textwidth("ֻ�����ֶ�����ÿ��Ŀ��");
	//GridHeight = 50;

	//������
	for (size_t i = 0; i < rows + 1; ++i) {
		line(x, y + i * GridHeight, x + cols * GridWidth, y + i * GridHeight);
	}
	//������
	for (size_t i = 0; i < cols + 1; ++i) {
		line(x + i * GridWidth, y, x + i * GridWidth, y + rows * GridHeight);
	}

	if (MaxPage > 0) {
		DrawButton();
	}
}

void Table::DrawButton()
{
	static bool flag = false;
	if (!flag) {
		PreButton->move(x, height + 60);
		NextButton->move(PreButton->GetX() + PreButton->GetWidth(), PreButton->GetY());
		FirstButton->move(NextButton->GetX() + NextButton->GetWidth(), NextButton->GetY());
		LastButton->move(FirstButton->GetX() + FirstButton->GetWidth(), FirstButton->GetY());
		flag = true;
	}

	PreButton->show();
	NextButton->show();
	FirstButton->show();
	LastButton->show();

	char str[30];
	sprintf_s(str, "��%dҳ / ��%dҳ", CurPage + 1, MaxPage + 1);
	outtextxy(LastButton->GetX() + LastButton->GetWidth() + 100, LastButton->GetY(), str);
}

void Table::DrawTableData(user* hash_name)
{
	//ֱ�Ӷ�hash_name��flagΪ1��������
	vector<user> temp;
	for (int i = 0; i < MAX_H; ++i) {
		if (hash_name[i].flag == 1) {
			temp.push_back(hash_name[i]);
		}
	}

	if (temp.size() == 0) {
		return;
	}

	//��ֹԽ��
	if (rows > temp.size() && temp.size() != 0) {
		rows = temp.size();
	}

	int BeginPos = CurPage * rows;			//���ݿ�ʼ��λ��
	int EndPos = CurPage * rows + rows;		//���ݽ�����λ��

	//��������һҳ����ֻ����ʣ�µ�����
	if (CurPage == MaxPage) {
		EndPos = BeginPos + ExtraData;
	}

	int count = 0;		//��ϣ����ʵ����Ч���ݾ���������
	for (int i = BeginPos; i < EndPos; ++i) {
		//����
		int tx = x + 0 * GridWidth + (GridWidth - ::textwidth(temp[i].name.c_str())) / 2;
		int ty = y + count * GridHeight + (GridHeight - ::textheight(temp[i].name.c_str())) / 2;
		outtextxy(tx, ty, temp[i].name.c_str());
		//�绰����
		tx = x + 1 * GridWidth + (GridWidth - ::textwidth(temp[i].telephone.c_str())) / 2;
		//ty = y + count * GridHeight + (GridHeight - ::textheight(temp[i].telephone.c_str())) / 2;
		outtextxy(tx, ty, temp[i].telephone.c_str());
		//סַ
		tx = x + 2 * GridWidth + (GridWidth - ::textwidth(temp[i].address.c_str())) / 2;
		//ty = y + count * GridHeight + (GridHeight - ::textheight(temp[i].address.c_str())) / 2;
		outtextxy(tx, ty, temp[i].address.c_str());

		++count;
		//���ݴ���10ʱ��ҳ�ػ棬��һ���Ǳ�ͷ��if count>10......
		//��������������ִε��øĻ��ƺ������о������ʵ��
	}
}

void Table::DrawHeader()
{
	//ͷ����Ϣ���߶�
	int hh = 40;
	setlinestyle(PS_SOLID, 2);
	::rectangle(x, y - hh, x + width, y);
	for (int i = 0; i < cols; ++i) {
		line(x + i * GridWidth + 1, y - hh, x + i * GridWidth + 1, y);
	}

	setlinestyle(PS_SOLID, 1);
	int SpaceH, SpaceV;
	int fix = 3;		//�ֶ�����
	SpaceH = (GridWidth - ::textwidth("����")) / 2;
	SpaceV = (hh - ::textheight("����")) / 2;
	outtextxy(x + 0 * GridWidth + SpaceH, y - GridHeight + SpaceV + fix, "����");
	SpaceH = (GridWidth - ::textwidth("�绰����")) / 2;
	SpaceV = (hh - ::textheight("�绰����")) / 2;
	outtextxy(x + 1 * GridWidth + SpaceH, y - GridHeight + SpaceV + fix, "�绰����");
	SpaceH = (GridWidth - ::textwidth("��ַ")) / 2;
	SpaceV = (hh - ::textheight("��ַ")) / 2;
	outtextxy(x + 2 * GridWidth + SpaceH, y - GridHeight + SpaceV + fix, "��ַ");
}

void Table::UpdatePage(user* hash_name)
{
	//�ŷ������ϣ����������
	int size = 0;
	for (int i = 0; i < MAX_H; ++i) {
		if (hash_name[i].flag == 1) {
			++size;
		}
	}

	if (rows == 0 && size != 0) {
		rows = size;
	}

	if (rows >= size) {
		MaxPage = 0;
		ExtraData = size;
	}
	else {
		MaxPage = size / rows;
		ExtraData = size % rows;
	}
}

void Table::event()
{
	BasicWidget::event();

	PreButton->event();
	NextButton->event();
	FirstButton->event();
	LastButton->event();

	if (PreButton->IsClicked()) {
		if (CurPage != 0) {
			--CurPage;
		}
	}
	if (NextButton->IsClicked()) {
		if (CurPage != MaxPage) {
			++CurPage;
		}
	}
	if (FirstButton->IsClicked()) {
		CurPage = 0;
	}
	if (LastButton->IsClicked()) {
		CurPage = MaxPage;
	}
}
