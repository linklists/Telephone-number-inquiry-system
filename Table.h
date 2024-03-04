#pragma once
#include "BasicWidget.h"
#include "configure.h"
#include "user.h"
#include "PushButton.h"

class Table :
    public BasicWidget
{
public:
    Table(int row = 10, int col = 3);

    ~Table();

    //设置行数
    void SetRowCount(int row);

    //设置列数
    void SetColCount(int col);

    //设置表头
    void SetHeader(const string& header);

    void InsertData(const user& data);

    void show() override;

    void DrawTableGrid();

    void DrawButton();

    void DrawTableData(user* hash_name);

    void DrawHeader();

    void UpdatePage(user* hash_name);

    void event() override;

public:
    int rows;
    int cols;
    int GridWidth;      //格子宽度
    int GridHeight;     //格子高度
    int TextWidth;      //文字宽度
    int TextHeight;     //文字高度
    string header;
    //vector<user> datas; //以姓名哈希表顺序排列的有效数据
    
    //分页处理
    int CurPage;       //当前页
    int MaxPage;       //最大页数
    int ExtraData;     //不足整页的剩余数据

    //按钮
    PushButton* PreButton;       //上一页
    PushButton* NextButton;      //下一页
    PushButton* FirstButton;     //第一页
    PushButton* LastButton;      //最后一页
};

