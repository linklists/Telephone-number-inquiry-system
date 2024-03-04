#include "UI_management.h"
#include "UI_window.h"
#include "Table.h"

int main()
{
	//按 Esc键 返回菜单
	LOGFONT fon;
	fon.lfQuality = ANTIALIASED_QUALITY;
	UI_window w(1920 / 3 * 2, 1080 / 3 * 2, EX_SHOWCONSOLE);
	w.SetWindowTitle("电话号码查询系统");
	
	UI_management test;
	test.run();

	return 0;
}