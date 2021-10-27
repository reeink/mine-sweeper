#include "./include/scene.h"

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
void BlockPainter::paint(QPixmap *&pixmap)
{
    //painter_->drawImage(row_ * gl_block_size, col_ * gl_block_size, (row_ + 1) * gl_block_size, (col_ + 1) * gl_block_size, pixmap);
}

BlockPainter::BlockPainter(QPainter *&painter) : painter_(painter)
{
}

BlockPainter::BlockPainter() : painter_(NULL)
{
}

// class Scene
Scene::Scene(const int &row, const int &col) : row_(row), col_(col)
{
    painter_ = new QPainter(this);
    block_ = new vector<BlockPainter>(row * col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            block_->at(i * col + j).painter_ = painter_;
            block_->at(i * col + j).init(i, j);
            // TODO: connect!
        }
    }

    pixmaps_ = new QPixmap[5];
}

Scene::~Scene()
{
    delete[] painter_;
    delete[] block_;
}

void Scene::paint(int &row, int &col)
{
    //block_->at(row * col_ + col).paint();
    
}
