#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include "snake.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent * event);
private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    snake snkClass;
    QPoint mousePos{320, 240};

private slots:
    void updateTime();
};


#endif // MAINWINDOW_H
