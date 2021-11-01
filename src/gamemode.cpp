#include "./include/gamemode.h"
#include "ui_gamemode.h"

GameMode::GameMode(GameModeInfo &mode_info, QWidget *parent) : QDialog(parent),
                                                               ui(new Ui::GameMode),
                                                               mode_info_(mode_info)
{
    ui->setupUi(this);
    mode_info_ = gl_easy_mode_info;
}

GameMode::~GameMode()
{
    delete ui;
}

void GameMode::on_EasyMode_clicked()
{
    mode_info_ = gl_easy_mode_info;
    qDebug() << "设置游戏为简单模式";
    accept();
}

void GameMode::on_NormalMode_clicked()
{
    mode_info_ = gl_normal_mode_info;
    qDebug() << "设置游戏为普通模式";
    accept();
}

void GameMode::on_HardMode_clicked()
{
    mode_info_ = gl_hard_mode_info;
    qDebug() << "设置游戏为困难模式";
    accept();
}
