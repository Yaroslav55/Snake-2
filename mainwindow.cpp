/*
 *      Snake v2.1
 *          https://github.com/Yaroslav55/Snake-2
 *                  Dev Yaroslav
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <iostream>
#include <math.h>
#define PERCENT_OF_SCREEN (25 / 100)

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tmr(new QTimer(this))
{
    /* Window resize */
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    if( screenGeometry.width() > 800 ){
        window()->setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                window()->size(),
                qApp->desktop()->availableGeometry()
            )
        );
    }
    else{
        window()->setGeometry(0, 0, 30, 30);
    }

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

    //qDebug()<<"rr "<<x;
    snkClass.snakeBotMove(snkClass.foodCoord);
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
}
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    mousePos.rx() = round(event->pos().x() / 20) * 20;
    mousePos.ry() = round(event->pos().y() / 20) * 20;
    if (mousePos.x() % 20)
        mousePos.rx() += 10;
    if (mousePos.y() % 20)
        mousePos.ry() += 10;
}
