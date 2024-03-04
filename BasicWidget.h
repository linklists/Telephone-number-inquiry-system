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

	//���ô��ڿ�ȡ��߶�
	void SetFixedSize(int width, int height);

	int GetX();

	int GetY();

	//�ƶ�����
	void move(int x, int y);
	
	bool IsIn();

	//�ж�����Ƿ����˰�ť
	bool IsClicked();

	//�����麯����Ҫ���壬������������д����
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

