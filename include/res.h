#pragma once
#include <QPixmap>
#include <vector>
using std::vector;

const int gl_block_size = 24;//每个方格的大小

class ResPixmap//用于一次性初始化所有资源文件，不用每次调用都要生成
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
