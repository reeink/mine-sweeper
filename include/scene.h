#pragma once
#include <QObject>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QWidget>

class Block : public QObject
{
    Q_OBJECT;

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

public slots:
    void paint();

public:
    BlockPainter(QPainter *&painter);
};

class Scene : public QWidget
{
    Q_OBJECT;

private:
    QPainter *painter_;
    BlockPainter *block_;

public:
    Scene(const int &row, const int &col);
    ~Scene();
};