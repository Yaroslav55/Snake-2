/*
 *      Snake v2.1
 *          https://github.com/Yaroslav55/Snake-2
 *                  Dev Yaroslav
 */
#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //QTimer::singleShot(1000, &w, SLOT(close()));
    return a.exec();
}
