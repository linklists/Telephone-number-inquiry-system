#pragma once
#include "BasicWidget.h"

class LineEdit : public BasicWidget
{
public:
	LineEdit(int x = 0, int y = 0, int w = 150, int h = 30);

	void show() override;

	inline void SetText(const string& text) { m_text = text; }

	inline void SetTitle(const string& titles) { title = titles; }

	inline void SetHitText(const string& texts) { HitText = texts; }

	inline const string& text() const { return m_text; }

	void clear() { m_text.clear(); }

	bool TextChange();

private:
	string pretext;
	string m_text;		//确认操作前输入框里的字
	string title;		//inputbox窗口标题
	string HitText;		//inputbox提示内容
};

