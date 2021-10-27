#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <QDialog>

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

class GameMode : public QDialog
{
    Q_OBJECT

public:
    explicit GameMode(QWidget *parent = nullptr);
    ~GameMode();

private slots:

    void on_EasyMode_clicked();

    void on_NormalMode_clicked();

    void on_HardMode_clicked();

    void on_CustomizeMode_clicked();

private:
    Ui::GameMode *ui;
};

#endif // GAMEMODE_H
