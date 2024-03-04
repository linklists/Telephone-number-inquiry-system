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

    //��������
    void SetRowCount(int row);

    //��������
    void SetColCount(int col);

    //���ñ�ͷ
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
    int GridWidth;      //���ӿ��
    int GridHeight;     //���Ӹ߶�
    int TextWidth;      //���ֿ��
    int TextHeight;     //���ָ߶�
    string header;
    //vector<user> datas; //��������ϣ��˳�����е���Ч����
    
    //��ҳ����
    int CurPage;       //��ǰҳ
    int MaxPage;       //���ҳ��
    int ExtraData;     //������ҳ��ʣ������

    //��ť
    PushButton* PreButton;       //��һҳ
    PushButton* NextButton;      //��һҳ
    PushButton* FirstButton;     //��һҳ
    PushButton* LastButton;      //���һҳ
};

