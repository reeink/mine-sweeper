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
using std::vector;

class Block : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

protected:
    int row_;
    int col_;

signals:
    void click(const int row, const int col,const int signal);

public:
    Block(QGraphicsItem *parent = NULL);
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
    void set(int status);
};

class Scene : public QGraphicsScene
{
    Q_OBJECT;

private:
    int row_, col_;
    QPainter *painter_;
    QPixmap *pixmaps_;
    vector<BlockPainter> *block_;
    Mine *mine_data_;

public:
    Scene(QObject *parent = NULL);
    Scene(const int &row, const int &col, QObject *parent = NULL);
    ~Scene();

public slots:
    void updateBlockUi(const int row, const int col, const int status);
    void blockClick(const int row, const int col, const int signal);

signals:
    void mouseActions(const int row, const int col, const int signal);
};
