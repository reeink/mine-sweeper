#include "./include/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "MineSweeper_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();

    //游戏模式选择
    GameModeInfo mode_info;
    GameMode mode_page(mode_info);
    mode_page.exec();
    qDebug() << "游戏难度信息：\n"
             << "行：" << mode_info.row << "，列：" << mode_info.col << "，地雷数：" << mode_info.mine_num;

    w.changeModeInfo(mode_info);
    return a.exec();
}
