/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#include "../surface/s_door.h"

#include <QGraphicsItem>
#include <QBrush>

#include <QDebug>


S_Door::S_Door(int xpos, int ypos, QGraphicsItem *parent) : G_Surface(xpos, ypos, parent)
{
    this->direction = 'x';
    setDesign('x');
    levelEnd = false;
    nextLevel = 0;
    neededItem = new QString("");
    needItem = false;
    this->setZValue(3);
}

//S_Door::S_Door(QGraphicsItem *parent) : G_Surface(0, 0, parent)
//{
//    setDesign();
//    levelEnd = false;
//    nextLevel = 0;
//    neededItem = new QString("");
//    needItem = false;
//}

void S_Door::setDirection(QChar direction)
{
    this->direction = direction;
    setDesign(direction);
}

void S_Door::setDesign(QChar direction)
{
    QBrush brush;
    if(direction == 't')
    {
        qDebug() << "TOP";
        QPixmap pixmap(":/surfaces/surfaces/door-t.png");
        brush.setTexture(pixmap);
    }
    else if(direction == 'b')
    {
        QPixmap pixmap(":/surfaces/surfaces/door-b.png");
        brush.setTexture(pixmap);
    }
    else if(direction == 'l')
    {
        QPixmap pixmap(":/surfaces/surfaces/door-l.png");
        brush.setTexture(pixmap);
    }
    else if(direction == 'r')
    {
        QPixmap pixmap(":/surfaces/surfaces/door-r.png");
        brush.setTexture(pixmap);
    }
    setBrush(brush);
}

void S_Door::setBackground(bool state)
{
    //True = OPEN, False = CLOSED
    if(state)
    {
        setDesign(this->direction);
    }
    else
    {
        QBrush brush;
        QPixmap pixmap(":/surfaces/surfaces/door.png");
        brush.setTexture(pixmap);
        setBrush(brush);
    }
}

bool S_Door::isEndLevel()
{
    return this->levelEnd;
}

void S_Door::setLevelEnd(bool value)
{
    setBackground(!value);
    this->levelEnd = value;
}

void S_Door::setNeededItem(QString value)
{
    this->needItem = true;
    this->neededItem = new QString(value);
}

QString S_Door::getNeededItem()
{
    return *this->neededItem;
}

bool S_Door::isNeedingItem()
{
    return this->needItem;
}

void S_Door::setNbItem(int nb)
{
    this->nbItem = nb;
}

int S_Door::getNbItem()
{
    return this->nbItem;
}

void S_Door::setNextLevel(int nb)
{
    this->nextLevel = nb;
}

int S_Door::getNextLevel()
{
    return this->nextLevel;
}
