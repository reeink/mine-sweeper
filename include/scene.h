#pragma once
#include <QObject>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <vector>
using std::vector;

const int gl_block_size = 50;

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
    void mousePressEvent(QMouseEvent *event);
    void init(const int &row, const int &col);
};

class BlockPainter : public Block
{
    Q_OBJECT;
    friend class Scene;

private:
    QPainter *painter_;

public:
    BlockPainter();
    BlockPainter(QPainter *&painter);
    void paint(QPixmap *&pixmap);
};

class Scene : public QWidget
{
    Q_OBJECT;

private:
    int row_, col_;
    QPainter *painter_;
    QPixmap *pixmaps_;
    vector<BlockPainter> *block_;

public:
    Scene(QWidget *parent = NULL);
    Scene(const int &row, const int &col, QWidget *parent = NULL);
    ~Scene();

public slots:
    void paint(int &row, int &col);
};