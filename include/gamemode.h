#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <QDialog>
#include <QDebug>

namespace Ui
{
    class GameMode;
}

//游戏难度信息
struct GameModeInfo
{
    int row;
    int col;
    int mine_num;
};

const GameModeInfo gl_easy_mode_info = {10, 10, 10};
const GameModeInfo gl_normal_mode_info = {20, 20, 200};
const GameModeInfo gl_hard_mode_info = {50, 50, 1000};

class GameMode : public QDialog
{
    Q_OBJECT

public:
    explicit GameMode(GameModeInfo &mode_info, QWidget *parent = nullptr);
    ~GameMode();

private slots:
    void on_EasyMode_clicked();
    void on_NormalMode_clicked();
    void on_HardMode_clicked();

private:
    Ui::GameMode *ui;
    GameModeInfo &mode_info_;
};

#endif // GAMEMODE_H
