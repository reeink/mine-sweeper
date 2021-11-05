#pragma once
#include <QObject>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <vector>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QStyle>
#include "./include/res.h"
#include "./include/mine.h"
#include "./include/gamemode.h"

using std::vector;

//图元类，用于实现每一个方格的点击操作
class Block : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

protected:
    int row_;
    int col_;

signals:
    void click(const int row, const int col, const int signal); //点击信息，signal 用于区分左键和右键信号

public:
    Block(QGraphicsItem *parent = NULL);
    ~Block(){};
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override; //重写QGraphicsPixmapItem中的鼠标点击操作
    void init(const int &row, const int &col);                      //初始化图元的位置信息，用于外部调用
};

//图元绘制，继承自图元类
class BlockPainter : public Block
{
    Q_OBJECT;
    friend class Scene;

public:
    BlockPainter(QGraphicsItem *parent = NULL) : Block(parent){};
    ~BlockPainter(){};
    void set(int status);
};

class Scene : public QGraphicsScene
{
    Q_OBJECT

private:
    vector<BlockPainter> *block_;
    Mine *mine_data_;
    GameModeInfo mode_info_;

public:
    Scene(const GameModeInfo &mode_info, QObject *parent = NULL);
    ~Scene();
    void initScene(const GameModeInfo &mode_info); //初始化场景
    int getFlagNum() { return mine_data_->getFlagNum(); };
    int getUnknownNum() { return mine_data_->getUnknownNum(); };
    Mine *getMineDataPtr() { return mine_data_; }; //获取地雷数据指针

public slots:
    void updateBlockUi(const int row, const int col, const int status); //更新方格的图像界面
    void blockClick(const int row, const int col, const int signal);    //方格点击操作（将来自方格的信号封装成场景的信号，便于管理）

signals:
    void clickScene(const int row, const int col); //点击场景信号
    void markScene(const int row, const int col);  //标记场景信号
    void markChange();                             //标记改变信号，用于改变主界面的计数器
    void checkScene();                             //检查场景，检查游戏是否胜利
};
