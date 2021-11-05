#ifndef GAMEMODE_H
#define GAMEMODE_H

//游戏难度信息
struct GameModeInfo
{
    int row;
    int col;
    int mine_num;
};

const GameModeInfo gl_easy_mode_info = {10, 10, 10};
const GameModeInfo gl_normal_mode_info = {20, 20, 80};
const GameModeInfo gl_hard_mode_info = {50, 50, 500};

#endif // GAMEMODE_H
