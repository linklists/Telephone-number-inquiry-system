#pragma once
#include "configure.h"

class UI_window
{
public:
	UI_window(int width, int height, int flag);
	
	void SetWindowTitle(const string& title);

	int exec();

	static int GetWidth();

	static int GetHeight();

	static void clear();

	static void BeginDraw();

	static void FlushDraw();

	static void EndDraw();

	//按键、鼠标操作
	//判断是否有消息
	inline static bool HasMsg() { return ::peekmessage(&msg); }

	inline static ExMessage& GetMsg() { return msg; }

private:
	HWND handle;	//窗口句柄
	inline static ExMessage msg;	//消息
};

