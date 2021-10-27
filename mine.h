#ifndef MINE_H
#define MINE_H

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include<stack>
#include <vector>
using namespace std;

enum blockType
{
    //for data_map
    MINE = -1,
    EMPTY = 0,
    MINE1 = 1,
    MINE2 = 2,
    MINE3 = 3,
    MINE4 = 4,
    MINE5 = 5,
    MINE6 = 6,
    MINE7 = 7,
    MINE8 = 8,

    //for user_map
    UNKNOWN = 10,
    FLAG = 11,

    VISIBLE = 13,
    INVISIBLE = 14,
};

typedef short block;

class Matrix
{
public:
    Matrix(short row, short col, block blocktype);
    block& at(short x, short y);
    block& at(short iter);
    bool put(short x, short y, const block& data);

private:
    vector<block> *matrix;
    short row, col;
};

class Mine
{
private:
    Matrix *data_map; //存放地图中的原始数据
    Matrix *user_map; //存放用户操作数据
    short row, col, mine_num, flag_num, unknown_num;

public:
    Mine();
    Mine(const short row, const short col, const short mine_num, const short x, const short y);
    ~Mine();
    void print();
    block blockData(const short x, const short y)const; //返回某一坐标的地雷数据
    int operateMark(const short x, const short y);
    int click(const short x,const short y);
    block VisibleData(const short x, const short y)const; //判断某个区域对用户是否可见，（FLAG和UNKNOWN标记均为不可见）
    
};

typedef struct xy {
    short x;
    short y;
}xy;

#endif