#include "./include/scene.h"

// class Block

Block::Block(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "鼠标左键点击 (" << row_ << ", " << col_ << ") .";
        emit click(row_, col_); //点击方块信号
    }
    else if (event->button() == Qt::RightButton)
    {
        qDebug() << "鼠标右键点击 (" << row_ << ", " << col_ << ") .";
        emit mark(row_, col_); //标记方块信号
    }
    qDebug() << "鼠标点击 (" << row_ << ", " << col_ << ") .";
    emit check(); //检查是否做完
}

void Block::init(const int &row, const int &col)
{
    row_ = row;
    col_ = col;
}

// class BlockPainter
void BlockPainter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QStyleOptionGraphicsItem op;
    op.initFrom(widget);
    op.state = QStyle::State_None;

    return QGraphicsPixmapItem::paint(painter, &op, widget);
}

BlockPainter::BlockPainter(QGraphicsItem *parent) : Block(parent)
{
}

// class Scene
Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    delete[] block_;
}
Scene::Scene(const int &row, const int &col, QObject *parent) : QGraphicsScene(parent),
                                                                row_(row),
                                                                col_(col)
{
    //painter_ = new QPainter(this);
    block_ = new vector<BlockPainter>(row * col);
    qDebug() << "初始化场景中...";
    int pos;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            pos = i * col + j;
            block_->at(pos).painter_ = painter_;
            block_->at(pos).init(i, j);

            block_->at(pos).setPos(i * gl_block_size, j * gl_block_size);
            addItem(&(block_->at(pos)));
            QPixmap block(":/png/block");
            block = block.scaled(gl_block_size, gl_block_size);

            block_->at(pos).setPixmap(block);
            // TODO: connect!
        }
    }
    qDebug()<<"block大小："<<block_->at(0).boundingRect().width();
    //pixmaps_ = new QPixmap[5];

    // QLine line(0, 0, 200, 200);
    // this->painter_->drawLine(line);
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
