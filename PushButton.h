#pragma once
#include "configure.h"
#include "BasicWidget.h"
#include "UI_window.h"

class PushButton : public BasicWidget
{
public:
    PushButton(const string& text = "Button", int x = 0, int y = 0, int width = 100, int height = 30);

    void show() override;

private:
    //x,y,width,height´Ó»ùÀà¼Ì³Ð

    string text;
};

