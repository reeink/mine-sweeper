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
using std::vector;

const int gl_block_size = 24;

namespace Ui
{
    class Scene;
}

class Block : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

protected:
    int row_;
    int col_;

signals:
    void click(const int &row, const int &col);
    void mark(const int &row, const int &col);
    void check();

public:
    Block(QGraphicsItem *parent = NULL);
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void init(const int &row, const int &col);
};

class BlockPainter : public Block
{
    Q_OBJECT;
    friend class Scene;

private:
    QPainter *painter_;

public:
    BlockPainter(QGraphicsItem *parent = NULL);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class Scene : public QGraphicsScene
{
    Q_OBJECT;

private:
    int row_, col_;
    QPainter *painter_;
    QPixmap *pixmaps_;
    vector<BlockPainter> *block_;

public:
    Scene(QObject *parent = NULL);
    Scene(const int &row, const int &col, QObject *parent = NULL);
    ~Scene();

public slots:
    void paint(int &row, int &col);
};
