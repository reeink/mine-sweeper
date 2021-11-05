# MineSweeper 

This is the First Project [@Zenossss](https://github.com/Zenossss) and I make with Qt and C++ while learning them. There are many mistakes and shortages. But don't care about it, it is just for fun… and the C++ experiment.

## Environment

- `Qt 6.2`
- `Visual Studio 2019`

## Usage

Before compiling this project, make sure you have configured the environment.

- if you use `Qt Creater`, you can clone this repository, open `CMakeLists.txt` and compile.

- You can also use command line to compile this project

  ```shell
  git clone https://github.com/sperjar/MineSweeper.git
  cd MineSweeper
  mkdir build
  cd build
  cmake ..
  make
  ```

  For Advanced tutorials, you can visit [Qt](https://www.qt.io/), [CMake](https://cmake.org/) and [Make](https://www.gnu.org/software/make/).

PS: If you want to enable `qDebug` output, please comment out this line `add_definitions(-DQT_NO_WARNING_OUTPUT -DQT_NO_DEBUG_OUTPUT)` in `CMakeLists.txt`.

------

## Reference

1. https://blog.csdn.net/livingsu/article/details/104774193
2. https://blog.csdn.net/u012234115/article/details/51858544
3. http://c.biancheng.net/qt/
4. https://www.devbean.net/2012/08/qt-study-road-2-catelog/
5. [xiaoxi666/mines_sweeper: 开源项目：扫雷（Qt开发） (github.com)](https://github.com/xiaoxi666/mines_sweeper)
6. [livingsu/Qt-minesweeper (github.com)](https://github.com/livingsu/Qt-minesweeper)

