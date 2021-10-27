#include "./include/mainwindow.h"
#include "ui_mainwindow.h"
#include "./include/about.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), time(0, 0, 0), timer(this), is_start(false)
{
    ui->setupUi(this);
    setFixedSize(300, 500);
    ui->startButton->setIcon(QIcon(":/png/smile0.png"));
    ui->startButton->setIconSize(ui->startButton->size() / 4 * 3);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeModeInfo(GameModeInfo &mode_info)
{
    mode_info_ = mode_info;
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
        ui->startButton->setIcon(QIcon(":/png/smile1.png"));
        timer.start(1000);
    }
    else
    {
        ui->startButton->setIcon(QIcon(":/png/smile0.png"));
        timer.stop();
    }
    ui->startButton->setIconSize(ui->startButton->size() / 4 * 3);
}
