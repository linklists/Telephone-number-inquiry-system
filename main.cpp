#include "UI_management.h"
#include "UI_window.h"
#include "Table.h"

int main()
{
	//�� Esc�� ���ز˵�
	LOGFONT fon;
	fon.lfQuality = ANTIALIASED_QUALITY;
	UI_window w(1920 / 3 * 2, 1080 / 3 * 2, EX_SHOWCONSOLE);
	w.SetWindowTitle("�绰�����ѯϵͳ");
	
	UI_management test;
	test.run();

	return 0;
}