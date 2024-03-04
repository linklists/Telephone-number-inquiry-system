#include "Table.h"
#include "user.h"

Table::Table(int row, int col)
	:BasicWidget(0, 0, 0, 0), rows(row), cols(col),
	CurPage(0), MaxPage(0), ExtraData(0)
{
	//默认
	GridWidth = ::textwidth("只是在手动调整每格的宽度");
	GridHeight = 50;

	PreButton = new PushButton("上一页");
	NextButton = new PushButton("下一页");
	FirstButton = new PushButton("第一页");
	LastButton = new PushButton("结尾页");
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

	////求文字的宽度和高度
	//GridWidth = ::textwidth("只是在手动调整每格的宽度");
	////GridHeight = ::textheight(header.c_str());
	//GridHeight = 50;
	//确定表格有多少行、列

	TextWidth = ::textwidth("只是在手动调整每格的宽度");
	TextHeight = 40;
	//让格子比文字大一点（其实是默认写死的）
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
	////确定表格有多少行、列
	setlinecolor(BLACK);
	//GridWidth = ::textwidth("只是在手动调整每格的宽度");
	//GridHeight = 50;

	//画横线
	for (size_t i = 0; i < rows + 1; ++i) {
		line(x, y + i * GridHeight, x + cols * GridWidth, y + i * GridHeight);
	}
	//画竖线
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
	sprintf_s(str, "第%d页 / 共%d页", CurPage + 1, MaxPage + 1);
	outtextxy(LastButton->GetX() + LastButton->GetWidth() + 100, LastButton->GetY(), str);
}

void Table::DrawTableData(user* hash_name)
{
	//直接读hash_name里flag为1的数据体
	vector<user> temp;
	for (int i = 0; i < MAX_H; ++i) {
		if (hash_name[i].flag == 1) {
			temp.push_back(hash_name[i]);
		}
	}

	if (temp.size() == 0) {
		return;
	}

	//防止越界
	if (rows > temp.size() && temp.size() != 0) {
		rows = temp.size();
	}

	int BeginPos = CurPage * rows;			//数据开始的位置
	int EndPos = CurPage * rows + rows;		//数据结束的位置

	//如果是最后一页，则只遍历剩下的数据
	if (CurPage == MaxPage) {
		EndPos = BeginPos + ExtraData;
	}

	int count = 0;		//哈希表中实际有效数据决定换行数
	for (int i = BeginPos; i < EndPos; ++i) {
		//姓名
		int tx = x + 0 * GridWidth + (GridWidth - ::textwidth(temp[i].name.c_str())) / 2;
		int ty = y + count * GridHeight + (GridHeight - ::textheight(temp[i].name.c_str())) / 2;
		outtextxy(tx, ty, temp[i].name.c_str());
		//电话号码
		tx = x + 1 * GridWidth + (GridWidth - ::textwidth(temp[i].telephone.c_str())) / 2;
		//ty = y + count * GridHeight + (GridHeight - ::textheight(temp[i].telephone.c_str())) / 2;
		outtextxy(tx, ty, temp[i].telephone.c_str());
		//住址
		tx = x + 2 * GridWidth + (GridWidth - ::textwidth(temp[i].address.c_str())) / 2;
		//ty = y + count * GridHeight + (GridHeight - ::textheight(temp[i].address.c_str())) / 2;
		outtextxy(tx, ty, temp[i].address.c_str());

		++count;
		//数据大于10时翻页重绘，第一行是表头，if count>10......
		//或者在主函数里分次调用改绘制函数，感觉这个更实用
	}
}

void Table::DrawHeader()
{
	//头部信息栏高度
	int hh = 40;
	setlinestyle(PS_SOLID, 2);
	::rectangle(x, y - hh, x + width, y);
	for (int i = 0; i < cols; ++i) {
		line(x + i * GridWidth + 1, y - hh, x + i * GridWidth + 1, y);
	}

	setlinestyle(PS_SOLID, 1);
	int SpaceH, SpaceV;
	int fix = 3;		//手动调整
	SpaceH = (GridWidth - ::textwidth("姓名")) / 2;
	SpaceV = (hh - ::textheight("姓名")) / 2;
	outtextxy(x + 0 * GridWidth + SpaceH, y - GridHeight + SpaceV + fix, "姓名");
	SpaceH = (GridWidth - ::textwidth("电话号码")) / 2;
	SpaceV = (hh - ::textheight("电话号码")) / 2;
	outtextxy(x + 1 * GridWidth + SpaceH, y - GridHeight + SpaceV + fix, "电话号码");
	SpaceH = (GridWidth - ::textwidth("地址")) / 2;
	SpaceV = (hh - ::textheight("地址")) / 2;
	outtextxy(x + 2 * GridWidth + SpaceH, y - GridHeight + SpaceV + fix, "地址");
}

void Table::UpdatePage(user* hash_name)
{
	//古法计算哈希表数据条数
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
