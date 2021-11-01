#include "./include/mainwindow.h"
#include "ui_mainwindow.h"
#include "./include/about.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow),
                                          time(0, 0, 0),
                                          timer(this),
                                          is_start(false)
{
    ui->setupUi(this);
    //setFixedSize(300, 500);
    ui->startButton->setIcon(QIcon(":/png/smile0.png"));
    ui->startButton->setIconSize(ui->startButton->size() / 4 * 3);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    ui->timeKeeper->display(time.toString("hh:mm:ss"));
    time_keeper_palette_[0].setColor(QPalette::Normal, QPalette::WindowText, Qt::black);
    time_keeper_palette_[1].setColor(QPalette::Normal, QPalette::WindowText, Qt::red);
}

MainWindow::~MainWindow()
{
    delete ui;
}

GameModeInfo &MainWindow::getModeInfo()
{
    return mode_info_;
}

void MainWindow::on_about_triggered()
{
    About *about_window = new About;
    about_window->show();
}

void MainWindow::on_exitGame_triggered()
{
    this->close();
}

void MainWindow::updateTime()
{
    if (is_start)
    {
        time = time.addSecs(1);
        ui->timeKeeper->display(time.toString("hh:mm:ss"));
    }
}

void MainWindow::on_startButton_clicked()
{
    is_start = !is_start;
    if (is_start)
    {
        ui->timeKeeper->setPalette(time_keeper_palette_[1]);
        ui->startButton->setIcon(QIcon(":/png/smile1.png"));
        timer.start(1000);
    }
    else
    {
        ui->timeKeeper->setPalette(time_keeper_palette_[0]);
        ui->startButton->setIcon(QIcon(":/png/smile0.png"));
        timer.stop();
    }
    ui->startButton->setIconSize(ui->startButton->size() / 4 * 3);
}

void MainWindow::initScene()
{
    scene_ = new Scene(mode_info_);
    ui->sceneView->setScene(scene_);
    time = QTime(0, 0, 0);
    ui->timeKeeper->display(time.toString("hh:mm:ss"));
    is_start = false;
    ui->timeKeeper->setPalette(time_keeper_palette_[0]);
}

void MainWindow::on_newGameEasy_triggered()
{
    delete (scene_);
    mode_info_ = gl_easy_mode_info;
    initScene();
}

void MainWindow::on_newGameNormal_triggered()
{
    delete (scene_);
    mode_info_ = gl_normal_mode_info;
    initScene();
}

void MainWindow::on_newGameHard_triggered()
{
    delete (scene_);
    mode_info_ = gl_hard_mode_info;
    initScene();
}
