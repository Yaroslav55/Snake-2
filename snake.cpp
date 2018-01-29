/*
 *      Snake v2.1
 *          https://github.com/Yaroslav55/Snake-2
 *                  Dev Yaroslav
 */
#include "snake.h"
#include <QDebug>
#include <QMainWindow>
#include <iostream>
#include <cmath>
snake::snake()
{
    loadLevel();
    for (int i = 0; i < 1; i++)
        snakeBotCoord.append(QPoint(540 - i * 20, 140));
}

snake::~snake()
{
    for (int y = 0; y < lvlSize.height(); y++) {
        delete[] LevelData[y];
    }
    delete[] LevelData;
}
void snake::loadLevel()
{
    LevelData = new char*[lvlSize.height()];
    for (int y = 0; y < lvlSize.height(); y++) {
        LevelData[y] = new char[lvlSize.width()];
        for (int x = 0; x < lvlSize.width(); x++) {
            LevelData[y][x] = 'o';
        }
        //LevelData[y][20] = 'o';
    }
    //LevelData[5][20] = 'q';
    qDebug() << LevelData[5][20] - '0';
}
void snake::updateLevelRoutes()
{
    LevelRoutes = new char*[lvlSize.height()];
    for (int y = 0; y < lvlSize.height(); y++) {
        LevelRoutes[y] = new char[lvlSize.width()];
        for (int x = 0; x < lvlSize.width(); x++) {
            LevelRoutes[y][x] = LevelData[y][x];
        }
    }
}
int snake::updateLevelData(QPoint point)
{
    updateLevelRoutes();
    /*   coords snake in level scale       */
    int loc_Y, loc_X;
    /*              PAINT SNAKE             */
    for (int i = 0; i < getSnakeBotSize(); i++) {
        loc_Y = getSnakeBotCoords(i).y() / 20;
        loc_X = getSnakeBotCoords(i).x() / 20;
        if (i == 0)
            LevelRoutes[loc_Y][loc_X] = '1';
        else if (i == getSnakeBotSize() - 1)
            LevelRoutes[loc_Y][loc_X] = 'o';
        else
            LevelRoutes[loc_Y][loc_X] = 'w';
        //qDebug() << getSnakeBotCoords(i).x() / 20;
    }
    /*             create Moving Map        */
    loc_Y = round(point.y() / 20);
    loc_X = round(point.x() / 20);
    qint8 weightBlock = 1;
    while (LevelRoutes[loc_Y][loc_X] == 'o') {
        weightBlock = createMovingMap(weightBlock);
    }

    /*             search Route             */
    route.clear();
    route.append(point); //Append target coords
    if (searchRoute(QPoint(loc_X, loc_Y)).x() != 1) {
        route.clear();
        route.append(point); //Append target coords
        return 1;
    }
    LevelRoutes[foodCoord.y() / 20][foodCoord.x() / 20] = 'M';
    //printMapMovement();
    return 1;
}
qint8 snake::createMovingMap(qint8 weightBlock)
{
    for (int y = 0; y < lvlSize.height() - 1; y++) {
        for (int x = 0; x < lvlSize.width() - 1; x++) {
            if (LevelRoutes[y][x] == weightBlock + '0') {
                if ((y + 1 < lvlSize.height()) && (LevelRoutes[y + 1][x] == 'o'))
                    LevelRoutes[y + 1][x] = (weightBlock + 1) + '0';

                if ((y - 1 > 0) && (LevelRoutes[y - 1][x] == 'o'))
                    LevelRoutes[y - 1][x] = (weightBlock + 1) + '0';

                if ((x + 1 < lvlSize.width()) && (LevelRoutes[y][x + 1] == 'o'))
                    LevelRoutes[y][x + 1] = (weightBlock + 1) + '0';

                if ((x - 1 > 0) && (LevelRoutes[y][x - 1] == 'o'))
                    LevelRoutes[y][x - 1] = (weightBlock + 1) + '0';
            }
        }
    }
    return weightBlock += 1;
}
QPoint snake::searchRoute(QPoint pos)
{
    /*
         *      72  - 'x'
         *      71  - 'w'
    */
    int min = 505;
    int nextStep = 0;
    int neighboringBlocks[4];
    neighboringBlocks[0] = getLevelElem(pos.x() + 1, pos.y());
    neighboringBlocks[1] = getLevelElem(pos.x() - 1, pos.y());
    neighboringBlocks[2] = getLevelElem(pos.x(), pos.y() + 1);
    neighboringBlocks[3] = getLevelElem(pos.x(), pos.y() - 1);
    for (int i = 0; i < 4; i++) {
        if ((neighboringBlocks[i] < min)) {
            min = neighboringBlocks[i];
            nextStep = i;
        }
        if (min == 1)
            return QPoint(1, 1);
    }
    switch (nextStep) {
    case 0:
        pos = QPoint(pos.x() + 1, pos.y());
        break;
    case 1:
        pos = QPoint(pos.x() - 1, pos.y());
        break;
    case 2:
        pos = QPoint(pos.x(), pos.y() + 1);
        break;
    case 3:
        pos = QPoint(pos.x(), pos.y() - 1);
        break;
    default:
        qDebug() << "-303";
        break;
    }
    if (route.length() > 500) {
        //        LevelRoutes[foodCoord.y()/20][foodCoord.x()/20] = 'F';
        //        printMapMovement();
        qDebug() << "-404";
        return QPoint(-1, -1);
    }
    LevelRoutes[pos.y()][pos.x()] = 'x';
    route.append(pos * 20); // Add Point
    return searchRoute(pos);
}

QSize snake::getLevelSize()
{
    return QSize(lvlSize.width(), lvlSize.height());
}
int snake::getLevelElem(int X, int Y)
{
    if (((X < getLevelSize().width() - 1) && (Y < getLevelSize().height() - 1)) && ((X > 0) && (Y > 0)))
        return (LevelRoutes[Y][X] - '0');
    else
        return 707;
}
int snake::getRoutePoints(QPoint point)
{
    routePoint.clear(); //Clear old route
    for (int i = route.length() - 2; i > 0; i--) {
        vectorDirection = QPoint(route[i].x(), route[i].y()) - point;

        if ((vectorDirection.x() != 0) && (vectorDirection.y() != 0)) {
            routePoint.append(QPoint(route[i + 1].x(), route[i + 1].y()));
            //LevelRoutes[int(round(route[i + 1].y()/15))][int(round(route[i + 1].x()/15))] = 'P';
            point = routePoint.back();
            i++;
            //qDebug() << route[i - 1].y()<< " d "<<route[i - 1].x();
        }
    }
    routePoint.append(QPoint(route[0].x(), route[0].y())); //Append target coords to points
    LevelRoutes[int(round(route[0].y() / 20))][int(round(route[0].x() / 20))] = 'P';
    return 1;
}
int snake::getNormVectorDirection()
{
    if (routePoint.empty()) {
        qDebug() << "Route points array is empty!";
        return -1;
    }
    vectorDirection = routePoint[0] - snakeBotCoord[0];
    if (vectorDirection.isNull()) {
        normVectorDirection.rx() = 0;
        normVectorDirection.ry() = 0;
        return -2;
    }
    direction = round(sqrt(pow(vectorDirection.x(), 2) + pow(vectorDirection.y(), 2)));
    //qDebug() << direction;
    if (direction <= 10) {
        routePoint.erase(routePoint.begin());
        if (routePoint.empty()) {
            qDebug() << "Route points array is empty!";
            return -1;
        }
    }
    normVectorDirection.rx() = vectorDirection.x() / direction;
    normVectorDirection.ry() = vectorDirection.y() / direction;
    return 1;
}
void snake::eatingBody(){
    for(int i = 2;i < snakeBotCoord.length(); i++){
        /* snakeBotCoord[0] - snake head */
        if( snakeBotCoord[0] == snakeBotCoord[i] ){
            snakeBotCoord.erase(snakeBotCoord.begin() + i, snakeBotCoord.end()-1);
            i = 100;
            break;
        }
    }
}
void snake::createFood(){
    QPoint vectorDir;
    int dir;
    foodCoord = QPoint(1 + rand() % 34, 1 + rand() % 19) *= 20;
    for(int i = 0; i < snakeBotCoord.length();i++){
        vectorDir = foodCoord - snakeBotCoord[i];
        dir = round(sqrt(pow(vectorDir.x(), 2) + pow(vectorDir.y(), 2)));
        if( dir < 30 ){
           foodCoord = QPoint(1 + rand() % 34, 1 + rand() % 19) *= 20;
           i = 0;
        }
    }
}
int snake::snakeBotMove(QPoint point)
{
    int status = updateLevelData(point);
    vectorDirection = point - snakeBotCoord[0];
    direction = round(sqrt(pow(vectorDirection.x(), 2) + pow(vectorDirection.y(), 2)));
    if (status != 1) {
        qDebug() << "Error " << status;
        return -1;
    } else if( direction > 4  ){
        getRoutePoints(snakeBotCoord[0]);
        /*     Snake move     */
        if (getNormVectorDirection()) {
            for (int i = getSnakeBotSize() - 1; i > 0; i--)
                snakeBotCoord[i] = snakeBotCoord[i - 1];
            if (std::abs(normVectorDirection.y()) < std::abs(normVectorDirection.x()))
                snakeBotCoord[0].rx() += round(normVectorDirection.x()) * speed;
            else
                snakeBotCoord[0].ry() += round(normVectorDirection.y()) * speed;
        }
    }
    eatingBody();
    EatingFood();
    return 0;
}
bool snake::EatingFood()
{
    QPoint vectorDir = foodCoord - snakeBotCoord[0];
    int dir = round(sqrt(pow(vectorDir.x(), 2) + pow(vectorDir.y(), 2)));
    if (dir <= 10) {
        route.clear(); //Clear old route
        createFood();
        //std::cin >> foodCoord.rx();
        //std::cin >> foodCoord.ry();
        snakeBotCoord.append(snakeBotCoord.back());//Snake length+1
        return 1;
    }
    return 0;
}
QPoint snake::getFoodCoord()
{
    return foodCoord;
}

QPoint snake::getSnakeBotCoords(qint8 elem)
{
    return snakeBotCoord[elem];
}
qint8 snake::getSnakeBotSize()
{
    return snakeBotCoord.size();
}
void snake::printMapMovement()
{
    std::cout << "--------------------Move map------------------" << std::endl;
    for (int y = 0; y < lvlSize.height(); y++) {
        std::cout << "|";
        for (int x = 0; x < lvlSize.width(); x++) {
            std::cout << "" << LevelRoutes[y][x];
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "-----------------------------------------------" << std::endl;
}
