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

#include "p_penguin.h"
#include "g_gameboard.h"
#include <QGraphicsRectItem>
#include <QPoint>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "surface/s_ice.h"
#include "g_object.h"

#include <QPropertyAnimation>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

P_Penguin::P_Penguin() : C_Player()
{
    int BlocsSizeX = G_Gameboard::getGameSquares()-2;
    int BlocsSizeY = G_Gameboard::getGameSquares()-2;

    leftCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    rightCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    bottomCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    topCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);

    leftCollideBox->setPen(Qt::NoPen);
    rightCollideBox->setPen(Qt::NoPen);
    bottomCollideBox->setPen(Qt::NoPen);
    topCollideBox->setPen(Qt::NoPen);

    lastMove = new QPoint(0,0);

    slideAble = true;

}
void P_Penguin::setPos(int x, int y)
{
    int xPos = x*G_Gameboard::getGameSquares()-G_Gameboard::getGameSquares();
    int yPos = y*G_Gameboard::getGameSquares()-G_Gameboard::getGameSquares();

    C_Player::setPos(xPos, yPos);

    leftCollideBox->setPos(xPos-G_Gameboard::getGameSquares()+1, yPos+1);
    rightCollideBox->setPos(xPos+G_Gameboard::getGameSquares()+1, yPos+1);
    bottomCollideBox->setPos(xPos+1, yPos+G_Gameboard::getGameSquares()+1);
    topCollideBox->setPos(xPos+1, yPos-G_Gameboard::getGameSquares()+1);
}

void P_Penguin::moveBy(int x, int y)
{


//    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
//    animation->setDuration(1000);
//    animation->setStartValue(QPoint(this->pos().x(), this->pos().y()));
//    animation->setEndValue(QPoint(this->pos().x() + x*gameSquare, this->pos().y() + y*gameSquare));

//    animation->start();

    C_Player::moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    leftCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    rightCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    bottomCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    topCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());

    lastMove->setX(x);
    lastMove->setY(y);
}

void P_Penguin::moveBack()
{
    moveBy(-lastMove->x(),-lastMove->y());
    lastMove->setX(0);
    lastMove->setY(0);

    qDebug() << "MoveBack" << x() << " " << y();
}

void P_Penguin::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(this);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}

bool P_Penguin::isSlide()
{
    QList<QGraphicsItem *> CollidingItems = this->CollidesCenter();
    bool slide = false;

    if(slideAble)
    {
        for(int i=0; i<CollidingItems.length(); i++)
        {
            if(typeid(*CollidingItems.at(i)).name() == typeid(S_Ice).name())
            {
                slide = true;
            }
        }
    }
    return slide;
}

void P_Penguin::setSlideAble(bool value)
{
    this->slideAble = value;
}

//Return lists of collisions
QList<QGraphicsItem *> P_Penguin::CollidesRight()
{
    return rightCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin::CollidesLeft()
{
    return leftCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin::CollidesTop()
{
    return topCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin::CollidesBottom()
{
    return bottomCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin::CollidesCenter()
{
    return C_Player::collidingItems();
}


//temp
QGraphicsRectItem* P_Penguin::getLeftCB(){
    return leftCollideBox;
}
QGraphicsRectItem* P_Penguin::getRightCB(){
     return rightCollideBox;
}
QGraphicsRectItem* P_Penguin::getTopCB(){
     return topCollideBox;
}
QGraphicsRectItem* P_Penguin::getBottomCB(){
     return bottomCollideBox;
}

C_Player* P_Penguin::getPlayer(){
     return this;
}

void P_Penguin::addObjectToBag(G_Object *object)
{
    if(object->getName()== G_Object::OBJECT_EGG)
    {
        nbLives++;
    }
    else
    {
        tempSacoche.append(object);
        sacoche.append(object);
    }

}

void P_Penguin::removeObjectFromSacoche(QString object)
{
    for (int i = 0; i < sacoche.size(); ++i)
    {
        if (sacoche.at(i)->getName() == object)
        {
            sacoche.removeAt(i);
            return;
        }
    }
}

void P_Penguin::printSacoche()
{
    qDebug() << "[PrintSacoche]";
    for (int i = 0; i < sacoche.size(); ++i) {
        qDebug() << sacoche.at(i)->getName();
    }
    qDebug() << " ";

    qDebug() << "[PrintSacocheTemp]";
    for (int i = 0; i < tempSacoche.size(); ++i) {
        qDebug() << tempSacoche.at(i)->getName();
    }
    qDebug() << " ";
}

QList<G_Object*> P_Penguin::getBag()
{
    return sacoche;
}

bool P_Penguin::checkObjectSacoche(QString object, int quantity)
{
    int total = 0;
    for (int i = 0; i < sacoche.size(); ++i)
    {
        if (sacoche.at(i)->getName() == object)
        {
            total++;
        }
    }

    if(total >= quantity)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void P_Penguin::emptyTempBag()
{
    tempSacoche.clear();
}

void P_Penguin::emptySacoche()
{
    sacoche.clear();
}

void P_Penguin::removeTempFromSacoche()
{
    for (int i = 0; i < tempSacoche.size(); ++i)
    {
        qDebug() << "Remove : " << tempSacoche.at(i)->getName();
        QString nom = tempSacoche.at(i)->getName();
        removeObjectFromSacoche(nom);
    }
    emptyTempBag();
}

QGraphicsRectItem* P_Penguin::getCollideBloc(char sensDepl)
{
    if(sensDepl == 'b')
    {
        return bottomCollideBox;
    }
    else if(sensDepl == 'l')
    {
        return leftCollideBox;
    }
    else if(sensDepl == 'r')
    {
        return rightCollideBox;
    }
    else if(sensDepl == 't')
    {
        return topCollideBox;
    }
    return NULL;
}
