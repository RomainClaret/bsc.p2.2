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

#include "b_wall.h"
#include "b_movable.h"
#include "b_water.h"
#include "ennemi.h"
#include "e_renard.h"
#include "e_loup.h"
#include "gameboard.h"

#include "s_ice.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

/**
 * @details Uses setDesign(xpos, ypos) to create the cross of box around self to check collisions.
 * Sets the position on the Z-axis to 1 to be on top of the scene which is at 0.
 */
B_Movable::B_Movable(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2, parent)
{
   setDesign(xpos, ypos);
   setZValue(1);
}

/**
 * @details The use FICTIVE positions x and y to create the cross of box around self to check collisions.
 * Sets the position on the Z-axis to 1 to be on top of the scene which is at 0.
 */
B_Movable::B_Movable(QGraphicsItem *parent) : Surface(0, 0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2, parent) //obligé de donner une position fictive
{
    setDesign(0, 0);
    setZValue(1);
}

void B_Movable::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*Gameboard::getGameSquares()+1, y*Gameboard::getGameSquares()+1);
}

/**
 * @details Creates a brush for self.
 * Build the cross of boxes around self with QGraphicsRectItem of getGameSquares-2.
 * Set the position of the boxes around self (left, right, bottom, top).
 * Turn of the visilibility of the boxes around self.
 */
void B_Movable::setDesign(int xpos, int ypos)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor("gray");

    setBrush(brush);

    int size = Gameboard::getGameSquares();

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

/**
 * @details Move self and the cross for colliding detectection.
 */
void B_Movable::moveBy(int x, int y)
{
    int gameSquare = Gameboard::getGameSquares();

    QGraphicsRectItem::moveBy(x*gameSquare,y*gameSquare);
    leftCollideBox->moveBy(x*gameSquare,y*gameSquare);
    rightCollideBox->moveBy(x*gameSquare,y*gameSquare);
    bottomCollideBox->moveBy(x*gameSquare,y*gameSquare);
    topCollideBox->moveBy(x*gameSquare,y*gameSquare);
}

/**
 * @details Add self and the cross for colliding detectection.
 */
void B_Movable::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(this);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}

/**
 * @details Remove self and the cross for colliding detectection.
 */
void B_Movable::removeFromScene(QGraphicsScene* Scene)
{
    Scene->removeItem(this);
    Scene->removeItem(topCollideBox);
    Scene->removeItem(bottomCollideBox);
    Scene->removeItem(leftCollideBox);
    Scene->removeItem(rightCollideBox);
}

/**
 * @details Check if the cross of detection collides with B_Wall, B_Movable, E_Renard, E_Loup.
 */
bool B_Movable::IsMovable(QList<QGraphicsItem *> l)
{
    for(int i=0; i<l.length(); i++)
    {
        if(typeid(*l.at(i)).name() == typeid(B_Wall).name() ||
           typeid(*l.at(i)).name() == typeid(B_Movable).name() ||
           typeid(*l.at(i)).name() == typeid(E_Renard).name() ||
           typeid(*l.at(i)).name() == typeid(E_Loup).name())
        {
            return false;
        }
    }
    return true;
}

/**
 * @details Check if the cross of detection collides with S_Ice.
 */
bool B_Movable::isSlide()
{
    QList<QGraphicsItem *> CollidingItems = this->CollidesCenter();

    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Ice).name())
        {
            return true;
        }
    }
    return false;
}

bool B_Movable::IsMovableToLeft(){
    return IsMovable(leftCollideBox->collidingItems());
}

bool B_Movable::IsMovableToRight(){
    return IsMovable(rightCollideBox->collidingItems());
}

bool B_Movable::IsMovableToBottom(){
    return IsMovable(bottomCollideBox->collidingItems());
}

bool B_Movable::IsMovableToTop(){
    return IsMovable(topCollideBox->collidingItems());
}

QList<QGraphicsItem *> B_Movable::CollidesCenter(){
     return collidingItems();
}

/**
 * @details Check the direction as parameter ("b":bottom,"l":left,"r":right,"t":top).
 * Return NULL if no colliding item is found.
 */
QGraphicsRectItem* B_Movable::getCollideBlocPosition(char sens)
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
