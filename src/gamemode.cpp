#include "./include/gamemode.h"
#include "ui_gamemode.h"

GameMode::GameMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameMode)
{
    ui->setupUi(this);
}

GameMode::~GameMode()
{
    delete ui;
}

void GameMode::on_EasyMode_clicked()
{

}


void GameMode::on_NormalMode_clicked()
{

}


void GameMode::on_HardMode_clicked()
{

}


void GameMode::on_CustomizeMode_clicked()
{

}

