#include "./include/res.h"

void ResPixmap::initBlock()
{
    blocks_.at(0).load(":/block/visible");
    blocks_.at(1).load(":/block/num1");
    blocks_.at(2).load(":/block/num2");
    blocks_.at(3).load(":/block/num3");
    blocks_.at(4).load(":/block/num4");
    blocks_.at(5).load(":/block/num5");
    blocks_.at(6).load(":/block/num6");
    blocks_.at(7).load(":/block/num7");
    blocks_.at(8).load(":/block/num8");
    blocks_.at(9).load(":/block/mine");
    blocks_.at(10).load(":/block/unknown");
    blocks_.at(11).load(":/block/flag");
    blocks_.at(12).load(":/block/invisible");
    blocks_.at(13).load(":/block/visible");
    blocks_.at(14).load(":/block/explode");

    for (int i = 0; i <= 14; i++)
    {
        blocks_.at(i) = blocks_.at(i).scaled(gl_block_size, gl_block_size);
    }
}
