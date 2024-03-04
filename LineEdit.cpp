#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h)
{
	//m_text = "����";
}

void LineEdit::show()
{
	setfillcolor(current);
	::fillroundrect(x, y, x + width, y + height, 10, 10);

	//���־�����ʾ
	settextcolor(BLACK);
	settextstyle(26, 0, "����");
	//int tx = x + (width - textwidth(text.c_str())) / 2;
	int ty = y + (height - textheight(m_text.c_str())) / 2;

	::outtextxy(x + 5, ty, m_text.c_str());

	//��������Ի���
	if (IsClicked()) {
		char buf[128];
		InputBox(buf, 128, HitText.data(), title.data());
		if (buf[0] != '\0') {
			m_text = buf;
		}
	}
}

bool LineEdit::TextChange()
{
	if (m_text.empty()) {
		return false;
	}

	if (pretext == m_text) {
		return false;
	}

	pretext = m_text;

	return true;
}
