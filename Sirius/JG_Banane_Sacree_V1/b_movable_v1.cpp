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

#include <QBrush>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "b_wall_v1.h"
#include "b_movable_v1.h"
#include "b_water_v1.h"
#include "c_enemy_v1.h"
#include "e_fox_v1.h"
#include "e_wolf_v1.h"
#include "g_gameboard_v1.h"

#include "s_ice_v1.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

B_Movable_v1::B_Movable_v1(int xpos, int ypos, QGraphicsItem *parent) : G_Surface_v1(xpos, ypos, G_Gameboard_v1::getGameSquares()-2, G_Gameboard_v1::getGameSquares()-2, parent)
{
   setDesign(xpos, ypos);
   setZValue(1);
}

B_Movable_v1::B_Movable_v1(QGraphicsItem *parent) : G_Surface_v1(0, 0, G_Gameboard_v1::getGameSquares()-2, G_Gameboard_v1::getGameSquares()-2, parent) //obligé de donner une position fictive
{
    setDesign(0, 0);
    setZValue(1);
}

void B_Movable_v1::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*G_Gameboard_v1::getGameSquares()+1, y*G_Gameboard_v1::getGameSquares()+1);
}

void B_Movable_v1::setDesign(int xpos, int ypos)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor("gray");

    setBrush(brush);

    int size = G_Gameboard_v1::getGameSquares();

    setPos(xpos,ypos);
    leftCollideBox = new QGraphicsRectItem(size*xpos-size+1, size*ypos+1,size-2, size-2);
    rightCollideBox = new QGraphicsRectItem(size*xpos+size+1, size*ypos+1,size-2, size-2);
    bottomCollideBox = new QGraphicsRectItem(size*xpos+1, size*ypos+size+1, size-2, size-2);
    topCollideBox = new QGraphicsRectItem(size*xpos+1, size*ypos-size+1, size-2, size-2);

    leftCollideBox->setPen(Qt::NoPen);
    rightCollideBox->setPen(Qt::NoPen);
    bottomCollideBox->setPen(Qt::NoPen);
    topCollideBox->setPen(Qt::NoPen);
}

void B_Movable_v1::moveBy(int x, int y)
{
    int gameSquare = G_Gameboard_v1::getGameSquares();

    QGraphicsRectItem::moveBy(x*gameSquare,y*gameSquare);
    leftCollideBox->moveBy(x*gameSquare,y*gameSquare);
    rightCollideBox->moveBy(x*gameSquare,y*gameSquare);
    bottomCollideBox->moveBy(x*gameSquare,y*gameSquare);
    topCollideBox->moveBy(x*gameSquare,y*gameSquare);
}

void B_Movable_v1::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(this);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}

void B_Movable_v1::removeFromScene(QGraphicsScene* Scene)
{
    Scene->removeItem(this);
    Scene->removeItem(topCollideBox);
    Scene->removeItem(bottomCollideBox);
    Scene->removeItem(leftCollideBox);
    Scene->removeItem(rightCollideBox);
}

bool B_Movable_v1::IsMovable(QList<QGraphicsItem *> l)
{
    for(int i=0; i<l.length(); i++)
    {
        if(typeid(*l.at(i)).name() == typeid(B_Wall_v1).name() ||
           typeid(*l.at(i)).name() == typeid(B_Movable_v1).name() ||
           typeid(*l.at(i)).name() == typeid(E_Fox_v1).name() ||
           typeid(*l.at(i)).name() == typeid(E_Wolf_v1).name())
        {
            return false;
        }
    }
    return true;
}

bool B_Movable_v1::isSlide()
{
    QList<QGraphicsItem *> CollidingItems = this->CollidesCenter();

    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Ice_v1).name())
        {
            return true;
        }
    }
    return false;
}

bool B_Movable_v1::IsMovableToLeft(){
    return IsMovable(leftCollideBox->collidingItems());
}
bool B_Movable_v1::IsMovableToRight(){
    return IsMovable(rightCollideBox->collidingItems());
}
bool B_Movable_v1::IsMovableToBottom(){
    return IsMovable(bottomCollideBox->collidingItems());
}
bool B_Movable_v1::IsMovableToTop(){
    return IsMovable(topCollideBox->collidingItems());
}

QList<QGraphicsItem *> B_Movable_v1::CollidesCenter(){
     return collidingItems();
}

QGraphicsRectItem* B_Movable_v1::getCollideBlocPosition(char sens)
{
    QGraphicsRectItem* collide = new QGraphicsRectItem();
    if(sens == 'b')
    {
        collide->setX(this->x());
        collide->setY(this->y()+32);
        return collide;
    }
    else if(sens == 'l')
    {
        collide->setX(this->x()-32);
        collide->setY(this->y());
        return collide;
    }
    else if(sens == 'r')
    {
        collide->setX(this->x()+32);
        collide->setY(this->y());
        return collide;
    }
    else if(sens == 't')
    {
        collide->setX(this->x());
        collide->setY(this->y()-32);
        return collide;
    }
    return NULL;
}
