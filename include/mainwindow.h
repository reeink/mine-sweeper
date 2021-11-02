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
    void initScene();

private slots:
    void on_newGameHard_triggered();
    void on_newGameNormal_triggered();
    void on_newGameEasy_triggered();
    void on_about_triggered();
    void on_exitGame_triggered();

public slots:
    void updateTime();
    void on_startButton_clicked();
    void winAction();
    void loseAction();
    void updateScore();

private:
    Ui::MainWindow *ui;
    QTime time;
    QTimer timer;
    bool is_start;
    bool is_over;
    GameModeInfo mode_info_;
    Scene *scene_;
    QPalette time_keeper_palette_[2];
};
#endif // MAINWINDOW_H
