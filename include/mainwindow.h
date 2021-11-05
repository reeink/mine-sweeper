#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <QGraphicsView>
#include <sstream>
#include <QString>
#include <string>
#include <iomanip>
#include "./include/gamemode.h"
#include "./include/about.h"
#include "./include/scene.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    GameModeInfo &getModeInfo();
    void initScene();//初始化场景

private slots:
    void on_newGameHard_triggered();//点击困难模式选项
    void on_newGameNormal_triggered();//点击普通模式选项
    void on_newGameEasy_triggered();//点击简单模式选项
    void on_about_triggered();//点击关于页面
    void on_exitGame_triggered();//点击退出按钮
    void updateTime();//更新计时器时间
    void on_startButton_clicked();//点击开始按钮
    void winAction();//游戏胜利操作
    void loseAction();//游戏失败操作
    void updateScore();//更新 地雷|旗帜|未知 计数器

private:
    Ui::MainWindow *ui;
    QTime time;//游戏时间
    QTimer timer;//计时器
    bool is_start;//游戏开始|暂停标识
    bool is_over;//游戏开始|结束标识
    GameModeInfo mode_info_;//游戏难度信息
    Scene *scene_;//游戏场景信息
    QPalette time_keeper_palette_[2];//计时器样式
};
#endif // MAINWINDOW_H
