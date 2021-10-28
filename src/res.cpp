#include "./include/res.h"

void ResPixmap::initBlock()
{
    blocks_.at(0).load("");
    blocks_.at(1).load("");
    blocks_.at(2).load("");
    blocks_.at(3).load("");
    blocks_.at(4).load("");
    blocks_.at(5).load("");
    blocks_.at(6).load("");
    blocks_.at(7).load("");
    blocks_.at(8).load("");
    blocks_.at(9).load("");
    blocks_.at(10).load("");
    blocks_.at(11).load("");
    blocks_.at(12).load("");

    for (int i = 0; i < BLOCK_KINDS; i++)
    {
        blocks_.at(i).scaled(gl_block_size, gl_block_size);
    }
}