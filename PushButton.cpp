#include "PushButton.h"

PushButton::PushButton(const string& text, int x, int y, int width, int height)
	:BasicWidget(x, y, width, height), text(text)
{

}

void PushButton::show()
{
	setfillcolor(current);
	::fillroundrect(x, y, x + width, y + height, 10, 10);

	//Œƒ◊÷æ”÷–œ‘ æ
	settextcolor(BLACK);
	int tx = x + (width - textwidth(text.c_str())) / 2;
	int ty = y + (height - textheight(text.c_str())) / 2;

	::outtextxy(tx, ty, text.c_str());
}

