/*
 *      Snake v2.1
 *          https://github.com/Yaroslav55/Snake-2
 *                  Dev Yaroslav
 */
#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>

class snake {
public:
    int delay = 40;

    snake();
    ~snake();
    int getRoutePoints(QPoint point);
    int getNormVectorDirection();
    int snakeBotMove(QPoint point = QPoint(640, 380));

    QPoint getFoodCoord();
    QPoint getSnakeBotCoords(qint8 elem);
    qint8 getSnakeBotSize();
    QSize getLevelSize();
    int getLevelElem(int X, int Y);
    void printMapMovement();
    int updateLevelData(QPoint point);
    QPoint foodCoord{ 80, 120 };
    QVector<QPoint> routePoint;

private:
    int speed = 20;
    QPoint vectorDirection;
    QPointF normVectorDirection{ 0.0, 0.0 };
    QVector<QPoint> snakeBotCoord;
    QVector<QPoint> route;
    float direction; // Direction inter snake and food
    char** LevelData;
    char** LevelRoutes;
    QSize lvlSize{ 36, 20 }; //X, Y

    bool EatingFood();
    void loadLevel();
    void updateLevelRoutes();
    qint8 createMovingMap(qint8 weightBlock);
    QPoint searchRoute(QPoint pos);
    void eatingBody();
    void createFood();
};

#endif // SNAKE_H
