#include "../include/scene.h"

// class Block
void Block::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit click(row_, col_); //点击方块信号
    }
    else if (event->button() == Qt::RightButton)
    {
        emit mark(row_, col_); //标记方块信号
    }

    emit check(); //检查是否做完
}

void Block::init(const int &row, const int &col)
{
    row_ = row;
    col_ = col;
}

// class BlockPainter
void BlockPainter::paint()
{
}

BlockPainter::BlockPainter(QPainter *&painter) : painter_(painter)
{
}

// class Scene
Scene ::Scene(const int &row, const int &col)
{
    painter_ = new QPainter(this);
    block_ = new BlockPainter[row * col](painter_);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            block_[i * col + j].init(i, j);
            // TODO: connect!
        }
    }
}

Scene::~Scene()
{
    delete[] painter_;
    delete[] block_;
}