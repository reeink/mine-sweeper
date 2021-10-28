#include "./include/res.h"

void ResPixmap::initBlock()
{
    blocks_.at(0).load(":/png/empty");
    blocks_.at(1).load(":/png/num1");
    blocks_.at(2).load(":/png/num2");
    blocks_.at(3).load(":/png/num3");
    blocks_.at(4).load(":/png/num4");
    blocks_.at(5).load(":/png/num5");
    blocks_.at(6).load(":/png/num6");
    blocks_.at(7).load(":/png/num7");
    blocks_.at(8).load(":/png/num8");
    blocks_.at(9).load(":/png/bomb");
    blocks_.at(10).load(":/png/unknown");
    blocks_.at(11).load(":/png/flag");
    blocks_.at(12).load(":/png/invisible");
    blocks_.at(13).load(":/png/visible");

    for (int i = 0; i < BLOCK_KINDS; i++)
    {
        blocks_.at(i)=blocks_.at(i).scaled(gl_block_size,gl_block_size);
    }
}
