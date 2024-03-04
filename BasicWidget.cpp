#include "BasicWidget.h"

BasicWidget::BasicWidget(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int BasicWidget::GetWidth()
{
    return width;
}

int BasicWidget::GetHeight()
{
    return height;
}

void BasicWidget::SetFixedSize(int width, int height) {
    this->width = width;
    this->height = height;
}

int BasicWidget::GetX()
{
    return x;
}

int BasicWidget::GetY()
{
    return y;
}

void BasicWidget::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

bool BasicWidget::IsIn()
{
    auto& msg = UI_window::GetMsg();
    if (msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height) {
        return true;
    }

    return false;
}

bool BasicWidget::IsClicked()
{
    if (IsIn()) {
        auto& msg = UI_window::GetMsg();
        if (msg.message == WM_LBUTTONDOWN) {
            return true;
        }
    }

    return false;
}

//按键颜色变化控制
void BasicWidget::event()
{
    if (!IsIn()) {
        current = normal;
    }
    else {
        current = hover;
    }
}

void BasicWidget::SetBackgroundColor(COLORREF color)
{
    normal = color;
}

void BasicWidget::SetHoverColor(COLORREF color)
{
    hover = color;
}
