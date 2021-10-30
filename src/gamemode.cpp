#include "./include/gamemode.h"
#include "ui_gamemode.h"

GameMode::GameMode(GameModeInfo &mode_info, QWidget *parent) : QDialog(parent),
                                                               ui(new Ui::GameMode),
                                                               mode_info_(mode_info)
{
    ui->setupUi(this);
}

GameMode::~GameMode()
{
    delete ui;
}

void GameMode::on_EasyMode_clicked()
{
    mode_info_.col = 10;
    mode_info_.row = 10;
    mode_info_.mine_num = 10;
    qDebug() << "设置游戏为简单模式";
    accept();
}

void GameMode::on_NormalMode_clicked()
{
    mode_info_.col = 25;
    mode_info_.row = 25;
    mode_info_.mine_num = 50;
    qDebug() << "设置游戏为普通模式";
    accept();
}

void GameMode::on_HardMode_clicked()
{
    mode_info_.col = 50;
    mode_info_.row = 50;
    mode_info_.mine_num = 100;
    qDebug() << "设置游戏为困难模式";
    accept();
}
