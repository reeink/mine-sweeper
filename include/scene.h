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

class Block : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

protected:
    int row_;
    int col_;

signals:
    void click(const int row, const int col, const int signal);

public:
    Block(QGraphicsItem *parent = NULL);
    ~Block(){};
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void init(const int &row, const int &col);
};

class BlockPainter : public Block
{
    Q_OBJECT;
    friend class Scene;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    BlockPainter(QGraphicsItem *parent = NULL) : Block(parent){};
    ~BlockPainter(){};
    void set(int status);
};

class Scene : public QGraphicsScene
{
    Q_OBJECT;

private:
    vector<BlockPainter> *block_;
    Mine *mine_data_;
    GameModeInfo mode_info_;

public:
    Scene(const GameModeInfo &mode_info, QObject *parent = NULL);
    void initScene(const GameModeInfo &mode_info);
    void changeScene(const GameModeInfo &mode_info);
    ~Scene();

public slots:
    void updateBlockUi(const int row, const int col, const int status);
    void blockClick(const int row, const int col, const int signal);

signals:
    void mouseActions(const int row, const int col, const int signal);
};
