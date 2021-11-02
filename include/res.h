#pragma once
#include <QPixmap>
#include <vector>
using std::vector;

const int gl_block_size = 24;

class ResPixmap
{
private:
    vector<QPixmap> blocks_;
    void initBlock();

public:
    ResPixmap()
    {
        blocks_ = vector<QPixmap>(15);
        initBlock();
    };
    QPixmap &getBlock(const int &status) { return blocks_.at(status); }
};
