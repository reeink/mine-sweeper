#include "./include/mainwindow.h"
#include "ui_mainwindow.h"
#include "./include/about.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow),
                                          time(0, 0, 0),
                                          timer(this),
                                          is_start(false),
                                          is_over(false),
                                          mode_info_(gl_easy_mode_info)
{
    ui->setupUi(this);
    setMinimumSize(mode_info_.row * gl_block_size + 60, mode_info_.row * gl_block_size + 140);
    ui->startButton->setFixedHeight(40);
    ui->startButton->setFixedWidth(40);
    ui->startButton->setIcon(QIcon(":/ico/meh"));
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
    if (!is_over) //游戏未结束
    {
        is_start = !is_start;
        if (is_start)
        {
            ui->timeKeeper->setPalette(time_keeper_palette_[1]);
            ui->startButton->setIcon(QIcon(":/ico/smile"));
            timer.start(1000);
        }
        else
        {
            ui->timeKeeper->setPalette(time_keeper_palette_[0]);
            ui->startButton->setIcon(QIcon(":/ico/meh"));
            timer.stop();
        }
        scene_->blockSignals(!is_start);
    }
    else //游戏结束
    {
        ui->startButton->setIcon(QIcon(":/ico/meh"));
        delete (scene_);
        initScene();
        is_over = false;
        on_startButton_clicked(); //若不加此句用户在获胜后点击开始按钮即返回未开始状态，需要再次点击方可开始游戏
    }
}

void MainWindow::initScene()
{
    scene_ = new Scene(mode_info_);
    ui->sceneView->setScene(scene_);
    time = QTime(0, 0, 0);
    ui->timeKeeper->display(time.toString("hh:mm:ss"));
    is_start = false;
    ui->timeKeeper->setPalette(time_keeper_palette_[0]);
    connect(scene_->getMineDataPtr(), SIGNAL(loseSignal()), this, SLOT(loseAction()));
    connect(scene_->getMineDataPtr(), SIGNAL(winSignal()), this, SLOT(winAction()));
    connect(scene_, SIGNAL(markChange()), this, SLOT(updateScore()));
    scene_->blockSignals(!is_start);
    updateScore();
    ui->startButton->setIcon(QIcon(":/ico/meh"));
}

void MainWindow::on_newGameEasy_triggered()
{

    delete (scene_);
    mode_info_ = gl_easy_mode_info;
    resize(mode_info_.row * gl_block_size + 60, mode_info_.row * gl_block_size + 140);
    initScene();
}

void MainWindow::on_newGameNormal_triggered()
{
    delete (scene_);
    mode_info_ = gl_normal_mode_info;
    resize(mode_info_.row * gl_block_size + 60, mode_info_.row * gl_block_size + 140);
    initScene();
}

void MainWindow::on_newGameHard_triggered()
{
    delete (scene_);
    mode_info_ = gl_hard_mode_info;
    resize(mode_info_.row * gl_block_size + 60, mode_info_.row * gl_block_size + 140);
    initScene();
}

void MainWindow::updateScore()
{
    QString score_str;
    stringstream score_stream;
    score_stream << setfill('0') << setw(2) << mode_info_.mine_num << ":"
                 << setfill('0') << setw(2) << scene_->getUnknownNum() << ":"
                 << setfill('0') << setw(2) << scene_->getFlagNum();
    score_str = QString::fromStdString(score_stream.str());
    if (score_str.length() != ui->score->digitCount() && score_str.length() > 8)
    {
        ui->score->setDigitCount(score_str.length());
    }
    ui->score->display(score_str);
}

void MainWindow::winAction()
{
    is_start = false;
    ui->startButton->setIcon(QIcon(":/ico/laugh"));
    scene_->blockSignals(!is_start);
    is_over = true;
}
void MainWindow::loseAction()
{
    is_start = false;
    ui->startButton->setIcon(QIcon(":/ico/dizzy"));
    scene_->blockSignals(!is_start);
    is_over = true;
}
