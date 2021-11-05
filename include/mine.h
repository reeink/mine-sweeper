#ifndef MINE_H
#define MINE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <vector>
#include <QObject>
using namespace std;

enum blockType
{
    //for data_map
    EMPTY,
    MINE1,
    MINE2,
    MINE3,
    MINE4,
    MINE5,
    MINE6,
    MINE7,
    MINE8,
    MINE,

    //for user_map
    UNKNOWN,
    FLAG,
    INVISIBLE,
    VISIBLE,
    EXPLODE_MINE,
};

typedef int block;

class Matrix
{
public:
    Matrix(int row, int col, block blocktype);
    block &at(const int x, const int y);
    block &at(const int iter);
    bool put(const int x, const int y, const block &data);

private:
    vector<block> *matrix;
    int row, col;
};

class Mine : public QObject
{
    Q_OBJECT

private:
    Matrix *data_map; //存放地图中的原始数据
    Matrix *user_map; //存放用户操作数据
    int row, col, mine_num, flag_num, unknown_num, invisible_num;
    bool has_mine;

public:
    Mine();
    Mine(const int row, const int col, const int mine_num);
    ~Mine();
    void print();
    block blockData(const int x, const int y) const;   //返回某一坐标的地雷数据
    block visibleData(const int x, const int y) const; //判断某个区域对用户是否可见，（FLAG和UNKNOWN标记均为不可见）
    block show(const int x, const int y);              //返回用户可见的方块信息
    int getFlagNum() { return flag_num; };
    int getUnknownNum() { return unknown_num; };

private:
    int create_mine(const int x, const int y);
    void gameLose(const int x, const int y);
    void gameWin();

public slots:
    int click(const int x, const int y); //点击方格
    int mark(const int x, const int y);  //标记方格
    void checkWin();                     //检查是否获胜

signals:
    void updateUserMap(const int x, const int y, const int status);
    void loseSignal();
    void winSignal();
    void markchange(const int flag, const int unknown);
};

typedef struct xy
{
    int x;
    int y;
} xy;

#endif