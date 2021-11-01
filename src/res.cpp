#include "./include/res.h"

void ResPixmap::initBlock()
{
    blocks_.at(0).load(":/visible");
    blocks_.at(1).load(":/num1");
    blocks_.at(2).load(":/num2");
    blocks_.at(3).load(":/num3");
    blocks_.at(4).load(":/num4");
    blocks_.at(5).load(":/num5");
    blocks_.at(6).load(":/num6");
    blocks_.at(7).load(":/num7");
    blocks_.at(8).load(":/num8");
    blocks_.at(9).load(":/mine");
    blocks_.at(10).load(":/unknown");
    blocks_.at(11).load(":/flag");
    blocks_.at(12).load(":/invisible");
    blocks_.at(13).load(":/visible");

    for (int i = 0; i < BLOCK_KINDS; i++)
    {
        blocks_.at(i) = blocks_.at(i).scaled(gl_block_size, gl_block_size);
    }
}
