#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <iostream>
#include <math.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tmr(new QTimer(this))
{
    ui->setupUi(this);

    tmr->setInterval(snkClass.delay);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime())); // Подключаем сигнал таймера к нашему слоту
    tmr->start();

    snkClass.getNormVectorDirection();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tmr;
}
void MainWindow::updateTime()
{
    snkClass.snakeBotMove(snkClass.getFoodCoord());
    repaint();
}
void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));

    /*Food*/
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(snkClass.getFoodCoord(), 10, 10);
    /*SnakeBot*/
    for (int i = 0; i < snkClass.getSnakeBotSize(); i++) {
        QColor color{ (80 + rand() % 160), 0, 0, 255 };
        painter.setBrush(QBrush(color, Qt::SolidPattern));
        painter.drawEllipse(snkClass.getSnakeBotCoords(i), 10, 10);
    }
//    for (int i = 0; i < snkClass.routePoint.length() - 1; i++) {
//        QColor color{ 0, 0, 10 + i * 100, 255 };
//        painter.setBrush(QBrush(color, Qt::SolidPattern));
//        painter.drawEllipse(snkClass.routePoint[i], 10, 10);
//    }
}
