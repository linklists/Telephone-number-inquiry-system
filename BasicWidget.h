#pragma once
#include "configure.h"
#include "UI_window.h"

class BasicWidget
{
public:
	BasicWidget(int x, int y, int width, int height);

	virtual ~BasicWidget() { }

	int GetWidth();

	int GetHeight();

	//设置窗口宽度、高度
	void SetFixedSize(int width, int height);

	int GetX();

	int GetY();

	//移动坐标
	void move(int x, int y);
	
	bool IsIn();

	//判断鼠标是否点击了按钮
	bool IsClicked();

	//基类虚函不需要定义，在派生类中重写即可
	virtual void show() = 0;

	virtual void event();

	void SetBackgroundColor(COLORREF color);

	void SetHoverColor(COLORREF color);


protected:
	int x;
	int y;
	int width;
	int height;
	COLORREF current = RGB(232, 232, 236);
	COLORREF normal = RGB(232, 232, 236);
	COLORREF hover = RGB(137, 243, 241);
};

