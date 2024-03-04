#include "UI_window.h"

UI_window::UI_window(int weight, int height, int flag)
{
	handle = ::initgraph(weight, height, flag);
	::setbkmode(TRANSPARENT);
}

void UI_window::SetWindowTitle(const string& title)
{
	::SetWindowText(handle, title.c_str());
}

int UI_window::exec()
{
	return getchar();
}

int UI_window::GetWidth()
{
	return ::getwidth();
}

int UI_window::GetHeight()
{
	return ::getheight();
}

void UI_window::clear()
{
	::cleardevice();
}

void UI_window::BeginDraw()
{
	::BeginBatchDraw();
}

void UI_window::FlushDraw()
{
	::FlushBatchDraw();
}

void UI_window::EndDraw()
{
	::EndBatchDraw();
}

