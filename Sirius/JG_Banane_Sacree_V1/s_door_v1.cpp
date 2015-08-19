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

#include "s_door_v1.h"

#include <QGraphicsItem>
#include <QBrush>

S_Door_v1::S_Door_v1(int xpos, int ypos, QGraphicsItem *parent) : G_Surface_v1(xpos, ypos, parent)
{
    setDesign();
    levelEnd = false;
    nextLevel = 0;
    neededItem = new QString("");
    needItem = false;
}
S_Door_v1::S_Door_v1(QGraphicsItem *parent) : G_Surface_v1(0, 0, parent)
{
    setDesign();
    levelEnd = false;
    nextLevel = 0;
    neededItem = new QString("");
    needItem = false;
}

void S_Door_v1::setDesign()
{
//    QBrush brush;
//    brush.setStyle(Qt::Dense7Pattern);
//    brush.setColor(Qt::blue);
//    setBrush(brush);
}

bool S_Door_v1::isEndLevel()
{
    return this->levelEnd;
}

void S_Door_v1::setLevelEnd(bool value)
{
    this->levelEnd = value;
}

void S_Door_v1::setNeededItem(QString value)
{
    this->needItem = true;
    this->neededItem = new QString(value);
}

QString S_Door_v1::getNeededItem()
{
    return *this->neededItem;
}

bool S_Door_v1::isNeedingItem()
{
    return this->needItem;
}

void S_Door_v1::setNbItem(int nb)
{
    this->nbItem = nb;
}

int S_Door_v1::getNbItem()
{
    return this->nbItem;
}

void S_Door_v1::setNextLevel(int nb)
{
    this->nextLevel = nb;
}

int S_Door_v1::getNextLevel()
{
    return this->nextLevel;
}
