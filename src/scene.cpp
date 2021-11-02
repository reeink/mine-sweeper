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
        emit click(row_, col_, 1); //点击方块信号
    }
    else if (event->button() == Qt::RightButton)
    {
        qDebug() << "鼠标右键点击 (" << row_ << ", " << col_ << ") .";
        emit click(row_, col_, 2); //标记方块信号
    }
    qDebug() << "鼠标点击 (" << row_ << ", " << col_ << ") .";
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

void BlockPainter::set(int status)
{
    static ResPixmap pixmaps;
    if (status >= EMPTY && status <= EXPLODE_MINE)
    {
        this->setPixmap(pixmaps.getBlock(status));
    }
}

// class Scene

Scene::Scene(const GameModeInfo &mode_info, QObject *parent) : QGraphicsScene(parent),
                                                               mode_info_(mode_info)
{
    block_ = new vector<BlockPainter>(mode_info_.row * mode_info_.col);
    initScene(mode_info_);
}

Scene::~Scene()
{
    delete (block_);
    delete (mine_data_);
}

void Scene::initScene(const GameModeInfo &mode_info)
{
    mine_data_ = new Mine(mode_info_.row, mode_info_.col, mode_info_.mine_num);
    qDebug() << "连接鼠标点击动作：" << connect(this, SIGNAL(clickScene(const int, const int)), mine_data_, SLOT(click(const int, const int)));
    qDebug() << "连接鼠标标记动作：" << connect(this, SIGNAL(markScene(const int, const int)), mine_data_, SLOT(mark(const int, const int)));
    qDebug() << "连接游戏获胜检查动作：" << connect(this, SIGNAL(checkScene()), mine_data_, SLOT(checkWin()));
    qDebug() << "初始化场景中...";
    int pos;
    for (int i = 0; i < mode_info_.row; i++)
    {
        for (int j = 0; j < mode_info_.col; j++)
        {
            pos = i * mode_info_.col + j;
            block_->at(pos).init(i, j);

            block_->at(pos).setPos(j * gl_block_size, i * gl_block_size);
            addItem(&(block_->at(pos)));
            updateBlockUi(i, j, mine_data_->show(i, j));
            connect(&(block_->at(pos)), SIGNAL(click(const int, const int, const int)), this, SLOT(blockClick(const int, const int, const int)));
            connect(mine_data_, SIGNAL(updateUserMap(const int, const int, const int)), this, SLOT(updateBlockUi(const int, const int, const int)));
        }
    }
    qDebug() << "block大小：" << block_->at(0).boundingRect().width();
}

void Scene::changeScene(const GameModeInfo &mode_info)
{
    mode_info_ = mode_info;
    delete (mine_data_);
    delete (block_);
    block_ = new vector<BlockPainter>(mode_info_.row * mode_info_.col);
    initScene(mode_info_);
}

void Scene::updateBlockUi(const int row, const int col, const int status)
{
    block_->at(row * mode_info_.col + col).set(status);
}

void Scene::blockClick(const int row, const int col, const int signal)
{
    switch (signal)
    {
    case 1:
        emit clickScene(row, col);
        break;

    case 2:
        emit markScene(row, col);
        emit markChange();
        break;
    }
    emit checkScene();
}
